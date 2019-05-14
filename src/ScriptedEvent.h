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
	static ScriptVariable *eventScripts[SEV_MAX];
	static bool eventRegistered[SEV_MAX];

	ScriptedEventType m_Type;
public:

	ScriptedEvent(ScriptedEventType type);
	~ScriptedEvent();

	static ScriptedEventType ParseType(str type);
	static void Shutdown();

	void Trigger(std::vector<ScriptedEventArgument> args);
	bool Register(ScriptVariable script);
	bool UnRegister();
	bool isRegistered();
};


class ScriptException
{
public:
	str		string;
	int		bAbort;
	int		bIsForAnim;

private:
	//void CreateException(const char *data);

public:
	//ScriptException(str text);
	//ScriptException(const char *format, ...);
	//ScriptException(char *text);

	static int next_abort;
	static int next_bIsForAnim;
};
