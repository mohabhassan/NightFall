#include "ScriptThread.h"
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
	gentity_t *gent = G_GetEntityByClient(0);
	gi.centerprintf(gent,"ScriptThread Test success");
}


void ScriptThread::Init()
{
	cerSet.AddEventResponse(new Event(
		"stest",
		EV_DEFAULT,
		NULL,
		NULL,
		"SCRIPTTHREAD TEST COMMAND"
	),
		&ScriptThread::Test);


	int rscount = cerSet.size() + 1;
	size_t sz = sizeof(ResponseDef<ScriptThread>) * rscount;
	//Responses = reinterpret_cast<ResponseDef<ScriptThread>*>(gi.Malloc(sz));
	Responses = new ResponseDef<ScriptThread>[rscount];
	memset(Responses, 0, sz);

	//Could be added as a member func of cerSet.
	for (size_t i = 0; i < rscount - 1; i++)
	{
		const std::string str = cerSet.GetResponseFuncAt(i).target_type().name();
		const std::string str2 = typeid(ResponseDef<ScriptThread>::response).name();
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
	delete Responses;
}
