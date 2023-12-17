#pragma once

#include "dgamex86.h"
#define NO_FILES
#define NO_FILESYSTEMS
#define NO_CGI
#define NO_SSL
#include "CivetServer.h"
#include "ScriptVariable.h"
#include "g_json.h"
#include <list>
#include <mutex>
#include <atomic>
#include <vector>
#include <string>
#include <utility>

using std::string, std::list, std::mutex, std::atomic, std::condition_variable, std::vector;
constexpr int defaultRouteIndex = -1;

class APIRoute
{
	string uri;
	string method;
	ScriptVariable script;
public:
	APIRoute(string sURI, string sMethod, ScriptVariable &svScript)
		: uri(sURI), method(sMethod), script(svScript)
	{

	}
	~APIRoute()
	{
	}

	string GetURI() const
	{
		return uri;
	}
	string GetMethod() const
	{
		return method;
	}
	const ScriptVariable & GetScript() const
	{
		return script;
	}
};
/////////////////////////////////////////////////////////////////////////////

class QueuedRequest
{
	string route;
	string method;
	json req_params;	//for get: it's query string without starting '?'
						//for post: it's parsed body as json
	unsigned int id;
public:
	QueuedRequest(string rt, string mt, json rqp, unsigned int iid)
	: route(rt), method(mt), req_params(rqp), id(iid)
	{

	}

	QueuedRequest()
	{

	}
	~QueuedRequest()
	{

	}

	unsigned int getID() const
	{
		return id;
	}
	string getRoute() const
	{
		return route;
	}
	string getMethod() const
	{
		return method;
	}
	json & getRequestParameters()
	{
		return req_params;
	}
private:

};
/////////////////////////////////////////////////////////////////////////////

class PendingScript
{
	ScriptVariable returnValue;
	unsigned int requestID;
public:
	PendingScript(int id, ScriptVariable & rtValue)
		: requestID(id), returnValue(rtValue)
	{

	}
	
	~PendingScript()
	{
	}

	ScriptVariable & getReturnValue()
	{
		return returnValue;
	}

	unsigned int getID() const
	{
		return requestID;
	}
private:

};
/////////////////////////////////////////////////////////////////////////////

class QueuedResponse
{
public:

	enum ResponseType
	{
		RESP_SUCCESS,
		RESP_ERROR,
		RESP_NOTFOUND,
	};

	QueuedResponse(int id, ScriptVariable &rVal)
		: requestID(id), returnValue(rVal), type(RESP_SUCCESS)
	{
	}
	QueuedResponse(int id, ResponseType tp)
		: requestID(id), type(tp)
	{
	}
	QueuedResponse()
	{
	}
	~QueuedResponse()
	{
	}

	unsigned int getID() const
	{
		return requestID;
	}
	ResponseType getType() const
	{
		return type;
	}
	ScriptVariable & getValue()
	{
		return returnValue;
	}


private:
	unsigned int requestID;
	ScriptVariable returnValue;
	ResponseType type;

};

/////////////////////////////////////////////////////////////////////////////

class HTTPServer
{
	//has to be a pointer since listenning happens on CivetServer constructor.
	static CivetServer *server;
	static vector<APIRoute> routes;

	static list<QueuedRequest> requests;
	static mutex requests_mutex;


	static atomic<unsigned int> lastRequestNumber;

	static list<PendingScript> pending_scripts;

	static list<QueuedResponse> responses;
	static mutex responses_mutex;
	static condition_variable responses_cv;

	static bool shouldShutdown;
public:
	HTTPServer();
	~HTTPServer();

	static void Init();
	static void Shutdown();
	static bool IsRunning();
	static bool RouteExists(string uri, string method);
	static size_t FindRoute(string uri, string method);
	static bool RegisterRoute(string uri, string method, ScriptVariable &script);
	static bool UnregisterRoute(string uri, string method);
	static void HandleNextAPIRequest();
	static void HandleNextAPIResponse();

	//thread safe funcs:
	static int EnqueueRequest(string &route, string method, json &req_params);
	static bool DequeueRequest(QueuedRequest &req);

	static void EnqueueResponse(int id, ScriptVariable &rVal);
	static void EnqueueResponse(int id, QueuedResponse::ResponseType tp);
	static void DequeueResponse(int id, QueuedResponse &res);
};

