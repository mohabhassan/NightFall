#include "HTTPClient.h"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include "CustomCvar.h"
#include "Director.h"
#include "Event.h"
#include "g_json.h"
condition_variable HTTPClient::cv;
mutex HTTPClient::cv_mutex;//mutex for cv

atomic<HTTPClient::Status> HTTPClient::status;

list<QueuedClientRequest> HTTPClient::requests;
//mutex HTTPClient::requests_mutex;//mutex for requests

list<QueuedClientResponse> HTTPClient::responses;
mutex HTTPClient::responses_mutex;//mutex for responses

using namespace std;

extern DirectorClass *Director;
void HTTPClient::HandleRequests()
{
	unique_lock<mutex> lk(cv_mutex);
	while (status != CST_STOP)
	{
		if (status == CST_IDLE)
		{
			cv.wait(lk); // acquires the lock before returning
		}

		if (status == CST_NEWREQ)
		{
			QueuedClientRequest req;
			{
				//lock_guard<mutex> lock(requests_mutex);
				req = requests.front();
				requests.pop_front();
				if (!requests.size())
				{
					status = CST_IDLE;
				}
			}
			lk.unlock();
			CreateRequest(req);
			lk.lock();
		}
	}
}

static size_t write_callback(string &respStr, char* ptr, size_t size, size_t nmemb)
{
	respStr.append(ptr, size*nmemb);
	return size * nmemb;
}

void HTTPClient::CreateRequest(QueuedClientRequest & req)
{
	string respStr;//empty string
	long httpCode = -1;
	try
	{
		curlpp::Easy request;

		request.setOpt(new curlpp::options::Url(req.getURL()));
		request.setOpt(new curlpp::options::Verbose(false));

		list<string> headers;
		if (req.getMethod() == "post")
		{
			//set post
			request.setOpt(new curlpp::options::Post(true));
			//set headers
			headers.emplace_back("Accept: application/json");
			headers.emplace_back("Content-Type: application/json");
			headers.emplace_back("charset: utf-8");
			request.setOpt(new curlpp::options::HttpHeader(headers));
			//add user data to request body
			json j_user_data;
			GameVarToJson(req.getUserData(), j_user_data);
			request.setOpt(new curlpp::options::PostFields(j_user_data.dump()));
		}

		//fail on error
		request.setOpt(new curlpp::options::FailOnError(true));

		//follow redirs
		request.setOpt(new curlpp::options::FollowLocation(true));

		//no progress func
		request.setOpt(new curlpp::options::NoProgress(true));

		//dont verify peer
		//verify peer requires ca cert bundle, shipped with exe. not needed.
		//not used anyways, we're not linking libcurl/pp to wolfssl
		//request.setOpt(new curlpp::options::SslVerifyPeer(false));
		
		//specifiy ca bundle location
		fs::path ca_path = fs::current_path() / MAIN_PATH / NF_LIBCURL_CABUNDLENAME;
		request.setOpt(new curlpp::options::CaInfo(ca_path.string()));

		//set timeout to 20 seconds (includes connection phase)
		request.setOpt(new curlpp::options::Timeout(20L));

		//set connection phase timeoute to 10 seconds
		request.setOpt(new curlpp::options::ConnectTimeout(10L));


		using namespace std::placeholders;

		//register write callback to get full response
		request.setOpt(new curlpp::options::WriteFunction(std::bind(&write_callback, std::ref(respStr), _1, _2, _3)));

		// perform request
		request.perform();

		//check http code:
		httpCode = curlpp::infos::ResponseCode::get(request);

		EnqueueResponse(req, respStr, httpCode);
	}
	catch (const std::exception&e)
	{
		respStr = e.what();
		//gi->Printf(PATCH_NAME " api client exception occured: %s\n", e.what());
		EnqueueResponse(req, respStr, httpCode);
	}
}

void HTTPClient::EnqueueResponse(QueuedClientRequest & req, string respStr, long http_code)
{
	lock_guard<mutex> lock(responses_mutex);
	if (status != CST_STOP)
		responses.emplace_back(respStr, http_code, req.getScript(), req.getUserData());
}


bool HTTPClient::DequeueResponse(QueuedClientResponse & resp)
{
	lock_guard<mutex> lock(responses_mutex);
	if (responses.size())
	{
		resp = responses.front();
		responses.pop_front();
		return true;
	}
	else
	{
		return false;
	}
}


void HTTPClient::Init()
{
	//init curlpp
	curlpp::initialize();

	status = CST_IDLE;
	//FIXME: wine stuff
	//try
	//{
		std::thread(HandleRequests).detach();
	//}
	//catch (const std::exception& e)
	//{
	//	gi->Printf("HTTPClient::Init error: %s\n", e.what());
	//	gi->cvar_set2("sv_api_client", "1", true);
	//}
}

void HTTPClient::Shutdown()
{
	//shutdown curlpp
	curlpp::terminate();
	status = CST_STOP;
	{
		lock_guard<mutex> lock1(cv_mutex);
	}
	cv.notify_all();

	lock_guard<mutex> lock2(cv_mutex);
	requests.clear();
	lock_guard<mutex> lock3(responses_mutex);
	responses.clear();
}

bool HTTPClient::IsRunning()
{
	CustomCvar sv_api_client("sv_api_client", "0", CVAR_ARCHIVE);
	return sv_api_client.GetIntValue();
}

void HTTPClient::CreateAPIRequest(string url, string method, ScriptVariable & script, ScriptVariable & user_data)
{
	{
		lock_guard<mutex> lock2(cv_mutex);
		requests.emplace_back(url, method, script, user_data);
	}

	//auto start = chrono::high_resolution_clock::now();
	{
		//lock_guard<mutex> lock1(cv_mutex);
		status = CST_NEWREQ;
	}
	cv.notify_all();
	//auto stop = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	//gi->Printf("!!!!!!!!!!!! time = %lld\n", duration.count());
}

void HTTPClient::HandleNextAPIResponse()
{
	QueuedClientResponse res;
	if (DequeueResponse(res))
	{
		Event ev;
		ev.AddValue(res.getScript());
		ev.AddInteger(res.getHttpCode());
		ev.AddString(res.getResponseStr().c_str());
		ev.AddValue(res.getUserData());
		try
		{
			Director->ExecuteScript(&ev);
		}
		catch (const ScriptException&e)
		{
			gi->Printf(PATCH_NAME " HTTP Client API response error: %s\n", e.string.c_str());
		}
	}
}
