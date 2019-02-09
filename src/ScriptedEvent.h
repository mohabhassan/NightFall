#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "ScriptVariable.h"

enum ScriptedEventType
{
	SEV_UNK = -1,
	SEV_CONNECTED,
	SEV_DISCONNECTED,
	SEV_SPAWN,
	SEV_DAMAGE,
	SEV_KILL,
	SEV_KEYPRESS,
	SEV_INTERMISSION,
	SEV_SERVERCOMMAND,
	SEV_MAX
};

class ScriptedEventArgument
{
	ScriptVariable var;
public:
	ScriptedEventArgument(Entity *e);
	ScriptedEventArgument(Vector v);
	ScriptedEventArgument(str s);
	ScriptedEventArgument(int i);
	ScriptedEventArgument(float f);
	ScriptVariable& getValue();
};

class ScriptedEvent
{
	static std::string eventScripts[SEV_MAX];
	static bool eventSet[SEV_MAX];

	ScriptedEventType m_Type;
public:

	ScriptedEvent(ScriptedEventType type);
	~ScriptedEvent();

	static ScriptedEventType ParseType(str type);
	void Trigger(std::vector<ScriptedEventArgument> args);
	bool Register(std::string script);
	bool UnRegister();

	str GetScript();
	bool isRegistered();
};

