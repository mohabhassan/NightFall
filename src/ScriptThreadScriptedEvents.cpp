#include "ScriptThread.h"
#include "Director.h"
#include "ScriptedEvent.h"
extern DirectorClass *Director;

enum SevReturnType
{
	SEVR_SUCCESS,
	SEVR_ALREADEXISTS,
	SEVR_MALLOC,//not used
	SEVR_INVALID
};

void ScriptThread::ScriptedEventsInit()
{
	cerSet.AddEventResponse(new Event(
		"registerev",
		EV_DEFAULT,
		"ss",
		"eventname scriptname",
		"Registers script callback handler for given event type.",
		EV_RETURN
	),
		&ScriptThread::RegisterevEvent);

	cerSet.AddEventResponse(new Event(
		"unregisterev",
		EV_DEFAULT,
		"s",
		"eventname",
		"Unregisters script callback handler for given event type.",
		EV_RETURN
	),
		&ScriptThread::UnregisterevEvent);
}

void ScriptThread::RegisterevEvent(Event*ev)
{
	int argnum = ev->NumArgs();
	str eventname;
	ScriptVariable script;
	ScriptVariable *file, *label;
	str fileStr, labelStr;
	ScriptedEventType type;
	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for registerev!\n");
		return;
	}

	eventname = ev->GetString(1);
	if (eventname == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL eventname passed to registerev!\n");
		return;
	}

	script = ev->GetValue(2);

	type = ScriptedEvent::ParseType(eventname);
	if (type == SEV_UNK)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: invalid eventname passed to registerev: %s !\n", eventname.c_str());
		return;
	}

	ScriptedEvent sev(type);

	if (script.GetType() == VARIABLE_CONSTARRAY)
	{
		file = script[1];
		label = script[2];
		file->CastString();
		label->CastString();
	}
	else if (script.GetType() == VARIABLE_CONSTSTRING)
	{
		script.CastString();
	}
	else if(script.GetType() != VARIABLE_STRING)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: registerev: invalid script %s of type  for event %s: of!\n", script.stringValue(), script.GetTypeName(), eventname.c_str());
		ev->AddInteger(SEVR_INVALID);
		return;
	}

	bool exists = !sev.Register(script);

	if (exists)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: registerev: event %s is already registered !\n", eventname.c_str());
		ev->AddInteger(SEVR_ALREADEXISTS);
		return;
	}

	ev->AddInteger(SEVR_SUCCESS);
}


void ScriptThread::UnregisterevEvent(Event*ev)
{
	int argnum = ev->NumArgs();
	str eventname;
	ScriptedEventType type;
	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for unregisterev!\n");
		return;
	}

	eventname = ev->GetString(1);
	if (eventname == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL eventname passed to unregisterev!\n");
		return;
	}

	type = ScriptedEvent::ParseType(eventname);
	if (type == SEV_UNK)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: invalid eventname passed to unregisterev: %s !\n", eventname.c_str());
		return;
	}

	ScriptedEvent sev(type);

	bool exists = !sev.UnRegister();

	if (exists)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: unregisterev: event %s is already unregistered!\n", eventname.c_str());
		ev->AddInteger(SEVR_ALREADEXISTS);
		return;
	}

	ev->AddInteger(SEVR_SUCCESS);
}