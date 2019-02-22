#include "ScriptThread.h"
#include "Director.h"
#include "ScriptedEvent.h"
extern DirectorClass *Director;

enum SevReturnType
{
	SEVR_SUCCESS,
	SEVR_ALREADEXISTS,
	SEVR_MALLOC//not used
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
	str eventname, scriptname;
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

	scriptname = ev->GetString(2);
	if (scriptname == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL scriptname passed to registerev!\n");
		return;
	}
	type = ScriptedEvent::ParseType(eventname);
	if (type == SEV_UNK)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: invalid eventname passed to registerev: %s !\n", eventname.c_str());
		return;
	}

	ScriptedEvent sev(type);

	bool exists = !sev.Register(scriptname.c_str());

	if (exists)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: registerev: event %s is already registered with script: %s !\n", eventname.c_str(), sev.GetScript().c_str());
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