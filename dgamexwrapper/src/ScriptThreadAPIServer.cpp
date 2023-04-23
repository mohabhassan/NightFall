#include "ScriptThread.h"
#include "HTTPServer.h"

enum APIRouteReturnType
{
	APIR_SUCCESS,
	APIR_ALREADEXISTS,
	APIR_INVALID,
	APIR_NOTRUNNING,
	APIR_ERROR,
};


void ScriptThread::APIServerInit()
{
	cerSet.AddEventResponse(new Event(
		"register_api_route",
		EV_DEFAULT,
		"sss",
		"uri method scriptname",
		"Registers script callback handler for uri/method type triggered by api server.",
		EV_RETURN
	),
		&ScriptThread::RegisterAPIRouteEvent);

	cerSet.AddEventResponse(new Event(
		"unregister_api_route",
		EV_DEFAULT,
		"ss",
		"uri method",
		"Unregisters script callback handler for for uri/method type from api server.",
		EV_RETURN
	),
		&ScriptThread::UnregisterAPIRouteEvent);
}


void ScriptThread::RegisterAPIRouteEvent(Event * ev)
{
	if (!HTTPServer::IsRunning())
	{
		ev->AddInteger(APIR_NOTRUNNING);
		return;
	}
	int argnum = ev->NumArgs();
	if (argnum != 3)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for register_api_route!\n");
		return;
	}
	str uri = ev->GetString(1);
	uri.tolower();
	if (uri.length() == 0)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: empty uri passed to register_api_route!\n");
		ev->AddInteger(APIR_INVALID);
		return;
	}

	str method = ev->GetString(2);
	method.tolower();

	if (method.length() == 0 || (method != "get" && method != "post"))
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: invalid method \"%s\" passed to register_api_route!\n", method.c_str());
		ev->AddInteger(APIR_INVALID);
		return;
	}

	if (HTTPServer::RouteExists(uri.c_str(), method.c_str()))
	{
		ev->AddInteger(APIR_ALREADEXISTS);
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
		gi.Printf(PATCH_NAME " SCRIPT ERROR: register_api_route: invalid script %s of type %s for uri/method %s / %s!\n", script.stringValue(), script.GetTypeName(), uri.c_str(), method.c_str());
		ev->AddInteger(APIR_INVALID);
		return;
	}

	if (script.GetType() == VARIABLE_STRING && script.stringValue().length() == 0)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: register_api_route: empty script %s of type %s for uri/method %s / %s!\n", script.stringValue(), script.GetTypeName(), uri.c_str(), method.c_str());
		ev->AddInteger(APIR_INVALID);
		return;
	}

	if (!HTTPServer::RegisterRoute(uri.c_str(), method.c_str(), script))
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: register_api_route: error while registering script %s of type %s for uri/method %s / %s : api server not running or route already exists!", script.stringValue(), script.GetTypeName(), uri.c_str(), method.c_str());
		ev->AddInteger(APIR_ERROR);
		return;
	}

	ev->AddInteger(APIR_SUCCESS);
}

void ScriptThread::UnregisterAPIRouteEvent(Event * ev)
{
	if (!HTTPServer::IsRunning())
	{
		ev->AddInteger(APIR_NOTRUNNING);
		return;
	}

	int argnum = ev->NumArgs();
	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for unregister_api_route!\n");
		return;
	}

	str uri = ev->GetString(1);
	uri.tolower();
	if (uri.length() == 0)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: empty uri passed to unregister_api_route!\n");
		ev->AddInteger(APIR_INVALID);
		return;
	}

	str method = ev->GetString(2);
	method.tolower();

	if (method.length() == 0 || (method != "get"  && method != "post"))
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: invalid method \"%s\" passed to unregister_api_route!\n", method.c_str());
		ev->AddInteger(APIR_INVALID);
		return;
	}

	if (!HTTPServer::RouteExists(uri.c_str(), method.c_str()))
	{
		ev->AddInteger(APIR_ALREADEXISTS);
		return;
	}

	if (!HTTPServer::UnregisterRoute(uri.c_str(), method.c_str()))
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: unregister_api_route: error while registering route for uri/method %s / %s : api server not running or route does not exist!", uri.c_str(), method.c_str());
		ev->AddInteger(APIR_ERROR);
		return;
	}
	ev->AddInteger(APIR_SUCCESS);
}