#include "ScriptThread.h"
//#include <string>
//#include <regex>

#include "g_misc.h"

Event *EV_ScriptThread_Test;


ResponseDef<ScriptThread> *ScriptThread::Responses;

CustomEventResponseSet<ScriptThread> ScriptThread::cerSet;

ScriptThread::ScriptThread()
{
}


ScriptThread::~ScriptThread()
{
}

void ScriptThread::Test(Event*ev)
{
	ScriptVariable& sv = ev->GetValue(0);

	str & strTat = sv.stringValue();

	ScriptVariable& sv1 = ev->GetValue(1);

	str & strTat1 = sv1.stringValue();

	ScriptVariable& sv2 = ev->GetValue(2);

	str & strTat2 = sv2.stringValue();

	ScriptVariable& sv3 = ev->GetValue(3);

	str & strTat3 = sv3.stringValue();

	ScriptVariable& sv4 = ev->GetValue(4);

	str & strTat4 = sv4.stringValue();

	gentity_t *gent = G_GetEntityByClient(0);
	gi.centerprintf(gent, "ScriptThread Test success");
}


void ScriptThread::Init()
{
	cerSet.AddEventResponse(new Event(
		"stest",
		EV_DEFAULT,
		"IFSB",
		"test_int test_float test_string test_bool",
		"SCRIPTTHREAD TEST COMMAND"
	),
		&ScriptThread::Test);

	MiscInit();
	iHudDrawInit();
	FileSystemInit();
	MathsInit();
	ScriptedEventsInit();

	int rscount = cerSet.size() + 1;
	size_t sz = sizeof(ResponseDef<ScriptThread>) * rscount;
	//Responses = reinterpret_cast<ResponseDef<ScriptThread>*>(gi.Malloc(sz));
	Responses = new ResponseDef<ScriptThread>[rscount];
	memset(Responses, 0, sz);

	//Could be added as a member func of cerSet.
	for (size_t i = 0; i < rscount - 1; i++)
	{
		Responses[i].event = cerSet.GetEventAt(i);
		Responses[i].response = *cerSet.GetResponseFuncAt(i).target<void(ScriptThread::*)(Event*)>();
	}
}

void ScriptThread::Shutdown()
{
	for (size_t i = 0; i < cerSet.size(); i++)
	{
		Event* ev = cerSet.GetEventAt(i);
		if (ev)
		{
			delete ev;
		}
	}
	//gi.Free(Responses);
	delete[] Responses;

	cerSet.Clear();
}
