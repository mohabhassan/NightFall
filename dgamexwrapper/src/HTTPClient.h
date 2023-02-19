#pragma once
#include <vector>
#include <string>
#include <condition_variable>
#include <thread>
#include <atomic>
#include "ScriptVariable.h"
using namespace std;

enum CAPIReturnType
{
	CAPIR_SUCCESS,
	CAPIR_INVALID,
	CAPIR_NOTRUNNING,
	CAPIR_ERROR,
};

class QueuedClientRequest
{
	string url;
	string method;
	ScriptVariable script;
	ScriptVariable user_data;
public:
	QueuedClientRequest(string sURL, string mt, ScriptVariable& sc, ScriptVariable &ud)
		: url(sURL), method(mt), script(sc), user_data(ud)
	{

	}

	QueuedClientRequest()
	{

	}
	~QueuedClientRequest()
	{

	}

	string getURL() const
	{
		return url;
	}
	string getMethod() const
	{
		return method;
	}
	ScriptVariable &getScript()
	{
		return script;
	}
	ScriptVariable &getUserData()
	{
		return user_data;
	}
};

class QueuedClientResponse
{
	string resp_str;
	long http_code;
	ScriptVariable script;
	ScriptVariable user_data;
public:
	QueuedClientResponse(string s, long c, ScriptVariable& sc, ScriptVariable &ud)
		: resp_str(s), http_code(c), script(sc), user_data(ud)
	{

	}

	QueuedClientResponse()
	{

	}
	~QueuedClientResponse()
	{

	}

	string getResponseStr() const
	{
		return resp_str;
	}
	long getHttpCode() const
	{
		return http_code;
	}
	ScriptVariable &getScript()
	{
		return script;
	}
	ScriptVariable &getUserData()
	{
		return user_data;
	}
};

class HTTPClient
{
	enum Status
	{
		CST_IDLE,
		CST_NEWREQ,
		CST_STOP,
	};

	static condition_variable cv;
	static mutex cv_mutex;//mutex for cv

	static atomic<Status> status;

	static list<QueuedClientRequest> requests;
	static mutex requests_mutex;//mutex for requests

	static list<QueuedClientResponse> responses;
	static mutex responses_mutex;//mutex for responses

	static void HandleRequests();
	static void CreateRequest(QueuedClientRequest &req);
	static void EnqueueResponse(QueuedClientRequest &req, string respStr, long http_code);
	static bool DequeueResponse(QueuedClientResponse &resp);
public:

	static void Init();
	static void Shutdown();
	static bool IsRunning();
	static void CreateAPIRequest(string url, string method, ScriptVariable & script, ScriptVariable & user_data);
	static void HandleNextAPIResponse();
};

