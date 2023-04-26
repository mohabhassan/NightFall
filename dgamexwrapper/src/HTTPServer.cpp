#include "HTTPServer.h"
#include "CustomCvar.h"
#include "Director.h"
#include "Event.h"

#include <chrono>
#include <thread>

CivetServer *HTTPServer::server;
vector<APIRoute> HTTPServer::routes;
list<QueuedRequest> HTTPServer::requests;
mutex HTTPServer::requests_mutex;
atomic<unsigned int> HTTPServer::lastRequestNumber;
list<QueuedResponse> HTTPServer::responses;
mutex HTTPServer::responses_mutex;
condition_variable HTTPServer::responses_cv;

list<PendingScript> HTTPServer::pending_scripts;

bool HTTPServer::shouldShutdown = false;

class RouteHandler : public CivetHandler
{
private:
	bool
		handleAll(string method,
			json &j_req_params,
			CivetServer* server,
			struct mg_connection* conn)
	{
		const struct mg_request_info* req_info = mg_get_request_info(conn);

		unsigned int requestID = HTTPServer::EnqueueRequest(string(req_info->local_uri), method, j_req_params);


		QueuedResponse res;
		HTTPServer::DequeueResponse(requestID, res);

		switch (res.getType())
		{
		case QueuedResponse::RESP_SUCCESS:
		{
			json j;
			j["status"] = "success";
			GameVarToJson(res.getValue(), j["message"]);
			std::string s = j.dump();
			mg_send_http_ok(conn, "application/json", s.size());
			mg_write(conn, s.c_str(), s.size());
		}
		break;
		case QueuedResponse::RESP_NOTFOUND:
		{
			//mg_send_http_error(conn, 404, R"t({"message" : "Not found."})t");
			constexpr int status = 404;
			constexpr char msg[] = R"t({"status":"error_not_found", "message" : "Not found."})t";
			char date[64];
			time_t curtime = time(NULL);
			const char* status_text = mg_get_response_code_text(conn, status);
			strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&curtime));

			mg_printf(conn, "HTTP/1.1 %d %s\r\n", status, status_text);
			mg_printf(conn, "Content-Type: application/json; charset=utf-8\r\n");
			mg_printf(conn, "Date: %s\r\n", date);
			mg_printf(conn, "Connection: close\r\n\r\n");
			mg_write(conn, msg, strlen(msg));
			//mg_printf(conn, "\r\n");
		}
		break;
		case QueuedResponse::RESP_ERROR:
		default:
		{
			//mg_send_http_error(conn, 404, R"t({"message" : "Not found."})t");
			constexpr int status = 500;
			constexpr char msg[] = R"t({"status":"error_internal", "message" : "Internal server error."})t";
			char date[64];
			time_t curtime = time(NULL);
			const char* status_text = mg_get_response_code_text(conn, status);
			strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&curtime));

			mg_printf(conn, "HTTP/1.1 %d %s\r\n", status, status_text);
			mg_printf(conn, "Content-Type: application/json; charset=utf-8\r\n");
			mg_printf(conn, "Date: %s\r\n", date);
			mg_printf(conn, "Connection: close\r\n\r\n");
			mg_write(conn, msg, strlen(msg));
			//mg_printf(conn, "\r\n");
		}
		break;
		}
		/*
		int index = HTTPServer::FindRoute(req_info->local_uri, "get");
		if (index == defaultRouteIndex)
		{
			//todo: add custom landing page if uri is "/"
			return false;
		}
		*/
		return true;
	}
public:
	bool
		handleGet(CivetServer *server, struct mg_connection *conn)
	{
		const struct mg_request_info* req_info = mg_get_request_info(conn);
		//req_info->local_uri : contains uri always has slash and doesn't contain query sting
		string query_string = req_info->query_string ? req_info->query_string : "";
		json j_querystrings = json::array();
		if (!query_string.empty() && query_string.length() >= 3)//minimum length is 3 "a=b" 
		{
			for (size_t i = query_string.find('&', 0), curr = 0; ; curr = i, i = query_string.find('&', i + 1))
			{
				string query_value_string;
				if (i == string::npos)
				{
					query_value_string = query_string.substr(curr);
				}
				else
				{
					i++;
					query_value_string = query_string.substr(curr, i - curr - 1);
				}
				size_t equ = query_value_string.find('=');
				if (equ == string::npos)
				{
					break;
				}
				string key = query_value_string.substr(0, equ), key_dec = key;
				string value = query_value_string.substr(equ + 1), value_dec = value;
				CivetServer::urlDecode(key, key_dec, false);
				CivetServer::urlDecode(value, value_dec, false);
				json entry = { {"key", key_dec}, {"value", value_dec} };
				j_querystrings.emplace_back(entry);
				if (i == string::npos)
					break;
			}
		}
		return handleAll("get", j_querystrings, server, conn);
	}

	bool
		handlePost(CivetServer *server, struct mg_connection *conn)
	{
		const struct mg_request_info* req_info = mg_get_request_info(conn);
		long long rlen;
		long long tlen = req_info->content_length;
		char buf[1024];
		string body_str;

		while ((rlen = mg_read(conn, buf, sizeof(buf))) > 0) {
			tlen += rlen;
			body_str.append(buf, rlen);
		}

		json j_req_body;
		try
		{
			j_req_body = json::parse(body_str);
		}
		catch (json::parse_error& e)
		{
			j_req_body = nullptr;
		}
		return handleAll("post", j_req_body, server, conn);
	}
};

static RouteHandler handler;

HTTPServer::HTTPServer()
{
}


HTTPServer::~HTTPServer()
{
}

void HTTPServer::Init()
{
	server = NULL;
	lastRequestNumber = 0;
	CustomCvar sv_api("sv_api", "0", CVAR_ARCHIVE);
	if (sv_api.GetIntValue() == 1)
	{
		mg_init_library(MG_FEATURES_DEFAULT);
		//number of worker threads
		CustomCvar sv_api_numthreads("sv_api_numthreads", "1", CVAR_ARCHIVE);
		//listening ports. comma separated list.
		//if ssl will ever be used, port must have 's' at the end, eg 8080,443s
		CustomCvar sv_api_ports("sv_api_ports", "8080", CVAR_ARCHIVE);
		//access controll list filters,'-' means block, '+' means allow, subnets can be used too
		CustomCvar sv_api_acl("sv_api_acl", "-0.0.0.0/0,+192.168.1.1/16,+127.0.0.1", CVAR_ARCHIVE);

		vector<string> options = {
			//"document_root", ".",
			"listening_ports", sv_api_ports.GetStringValue(),
			"num_threads" , sv_api_numthreads.GetStringValue(),
			"access_control_list", sv_api_acl.GetStringValue()
		};
		
		try
		{
			server = new CivetServer(options);
			gi.Printf(PATCH_NAME " api server started successfully.\n");
			server->addHandler("**", &handler);
		}
		catch (CivetException& e)
		{
			gi.Printf(PATCH_NAME " api server error: failed to start, could be port binding issue.\n");
		}
	}
}

void HTTPServer::Shutdown()
{
	if (server)
	{
		shouldShutdown = true;

		routes.clear();
		{
			lock_guard<mutex> lock1(requests_mutex);
			requests.clear();
		}
		{
			unique_lock<mutex> lock2(responses_mutex);
			responses.clear();
			lock2.unlock();
			responses_cv.notify_all();
		}
		pending_scripts.clear();
		mg_exit_library();
		delete server;
	}
}

bool HTTPServer::IsRunning()
{
	return server && server->getContext();
}

size_t HTTPServer::FindRoute(string uri, string method)
{
	for (size_t i = 0; i < routes.size(); i++)
	{
		if (routes[i].GetURI() == uri && routes[i].GetMethod() == method)
		{
			return i;
		}
	}
	return defaultRouteIndex;
}

bool HTTPServer::RouteExists(string uri, string method)
{
	return FindRoute(uri, method) != defaultRouteIndex;
}

bool HTTPServer::RegisterRoute(string uri, string method, ScriptVariable & script)
{
	if (!IsRunning())
	{
		return false;
	}
	else if (RouteExists(uri, method))
	{
		return false;
	}
	else
	{
		routes.emplace_back(uri, method, script);
		return true;
	}
}

bool HTTPServer::UnregisterRoute(string uri, string method)
{
	if (!IsRunning())
	{
		return false;
	}
	else
	{
		size_t index = FindRoute(uri, method);
		if (index != defaultRouteIndex)
		{
			routes.erase(routes.begin() + index);
			return true;
		}
		else
		{
			return false;
		}
	}
}


extern DirectorClass *Director;

void HTTPServer::HandleNextAPIRequest()
{

	QueuedRequest req;

	if (HTTPServer::DequeueRequest(req))
	{
		int index = FindRoute(req.getRoute(), req.getMethod());
		if (index != defaultRouteIndex)
		{
			APIRoute & route = routes[index];
			Event ev;
			try
			{
				ev.AddValue(route.GetScript());
			
				json & j_req_params = req.getRequestParameters();

				//array shape:
				/*
				 route?test=t&voodo=vx&dsfgsg=adfd
				 query_strings_param: [
					0: [ "key": "test", "value": "t"],
					1: [ "key": "voodo", "value": "vx"],
					2: [ "key": "dsfgsg", "value": "adfd"],
					.
					.
					.
				 ]

				 */
				//
				//
				ScriptVariable var;
				JsonToGameVar(j_req_params, var);
				ev.AddValue(var);

				try
				{
					Director->ExecuteReturnScript(&ev);
				}
				catch (const ScriptException&e)
				{
					gi.Printf(PATCH_NAME " HTTP Server API request error: %s\n", e.string.c_str());
					throw;
				}

				int numArgs = ev.NumArgs();//numargs is return value index.
				// if it's type is not script pointer, that means it's done executing.
				ScriptVariable &returnValue = ev.GetValue(numArgs);
				if (returnValue.GetType() == VARIABLE_POINTER)
				{
					pending_scripts.emplace_back(req.getID(), returnValue);
				}
				else
				{
					EnqueueResponse(req.getID(), returnValue);
				}
			}
			catch (...)
			{
				EnqueueResponse(req.getID(), QueuedResponse::RESP_ERROR);
				return;
			}
		}
		else
		{
			EnqueueResponse(req.getID(), QueuedResponse::RESP_NOTFOUND);
		}
	}
}

void HTTPServer::HandleNextAPIResponse()
{

	if (!pending_scripts.empty())
	{
		for (auto it = pending_scripts.begin(); it != pending_scripts.end(); it++)
		{
			ScriptVariable & scr = it->getReturnValue();
			if (scr.GetType() != VARIABLE_POINTER)
			{

				EnqueueResponse(it->getID(), scr);
				pending_scripts.erase(it);
				break;
			}
		}
	}
}


//THREAD SAFE FUNCS:

//returns request id.
//later requests have greater ids.
int HTTPServer::EnqueueRequest(string &route, string method, json& req_params)
{
	lock_guard<mutex> lock(requests_mutex);
	requests.emplace_back(route, method, req_params, lastRequestNumber);
	return lastRequestNumber++;
}

bool HTTPServer::DequeueRequest(QueuedRequest &req)
{
	lock_guard<mutex> lock(requests_mutex);
	if (requests.empty())
		return false;

	req = requests.front();
	requests.pop_front();
	return true;
}

void HTTPServer::EnqueueResponse(int id, ScriptVariable & rVal)
{
	unique_lock<mutex> lock(responses_mutex);
	responses.emplace_back(id, rVal);
	lock.unlock();
	responses_cv.notify_all();
}

void HTTPServer::EnqueueResponse(int id, QueuedResponse::ResponseType tp)
{
	unique_lock<mutex> lock(responses_mutex);
	responses.emplace_back(id, tp);
	lock.unlock();
	responses_cv.notify_all();
}

//blocks untill responseID is found
void HTTPServer::DequeueResponse(int id, QueuedResponse & res)
{
	unique_lock<mutex> lock(responses_mutex);
	while (!shouldShutdown)
	{
		for (auto it = responses.begin(); it != responses.end(); it++)
		{
			if (it->getID() == id)
			{
				res = *it;
				responses.erase(it);
				return;
			}
		}
		responses_cv.wait(lock);
	}
}
