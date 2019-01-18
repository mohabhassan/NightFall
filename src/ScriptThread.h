#pragma once
#include "Event.h"
#include "ClassDef.h"
#include "Class.h"
#include "CustomEventResponseSet.h"
class ScriptThread : public Class
{
public:
	ScriptThread();
	~ScriptThread();
	static ResponseDef<ScriptThread>	*Responses;
	static CustomEventResponseSet<ScriptThread> cerSet;

	void		Test(Event*ev);
	static void Init();
	static void Shutdown();
};

