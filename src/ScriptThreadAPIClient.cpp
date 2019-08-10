#include "ScriptThread.h"
#include "HTTPClient.h"
#include <chrono> 

void ScriptThread::APIClientInit()
{
	cerSet.AddEventResponse(new Event(
		"create_api_request",
		EV_DEFAULT,
		"sss",
		"url method scriptname userdata",
		"Creates api request and calls handler with return data and custom user data.",
		EV_RETURN
	),
		&ScriptThread::CreateAPIRequest);
}

void ScriptThread::CreateAPIRequest(Event * ev)
{

	if (!HTTPClient::IsRunning())
	{
		ev->AddInteger(CAPIR_NOTRUNNING);
		return;
	}
	int argnum = ev->NumArgs();
	if (argnum < 3 || argnum > 4)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for create_api_request!\n");
		return;
	}


	str url = ev->GetString(1);
	url.tolower();
	if (url.length() == 0)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: empty url passed to create_api_request!\n");
		ev->AddInteger(CAPIR_INVALID);
		return;
	}

	str method = ev->GetString(2);
	method.tolower();

	if (method.length() == 0 || method != "get")
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: invalid method \"%s\" passed to create_api_request!\n", method.c_str());
		ev->AddInteger(CAPIR_INVALID);
		return;
	}


	ScriptVariable script = ev->GetValue(3);

	if (script.GetType() == VARIABLE_CONSTARRAY)
	{
		ScriptVariable *file = script[1];
		ScriptVariable *label = script[2];
		file->CastString();
		label->CastString();
	}
	else if (script.GetType() == VARIABLE_CONSTSTRING)
	{
		script.CastString();
	}
	else if (script.GetType() != VARIABLE_STRING)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: create_api_request: invalid script %s of type %s for url/method %s / %s!\n", script.stringValue(), script.GetTypeName(), url.c_str(), method.c_str());
		ev->AddInteger(CAPIR_INVALID);
		return;
	}

	if (script.GetType() == VARIABLE_STRING && script.stringValue().length() == 0)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: create_api_request: empty script %s of type %s for url/method %s / %s!\n", script.stringValue(), script.GetTypeName(), url.c_str(), method.c_str());
		ev->AddInteger(CAPIR_INVALID);
		return;
	}
	ScriptVariable user_data;
	if (argnum == 4)
	{
		user_data = ev->GetValue(4);
	}

	HTTPClient::CreateAPIRequest(url.c_str(), method.c_str(), script, user_data);

	/*
	if (!HTTPClient::CreateAPIRequest(url.c_str(), method.c_str(), script))
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: create_api_request: error while creating request with script %s of type %s for url/method %s / %s!", script.stringValue(), script.GetTypeName(), url.c_str(), method.c_str());
		ev->AddInteger(CAPIR_ERROR);
		return;
	}
	*/

	ev->AddInteger(CAPIR_SUCCESS);

}
