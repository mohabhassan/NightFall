#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "ScriptVariable.h"
constexpr int defaultReturnValueIndex = -1;
using namespace std;
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
	SEV_DMMESSAGE,
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
	ScriptedEventArgument(vector<string> &arr);

	ScriptVariable& getValue();
};

class ScriptedEvent
{
	static ScriptVariable *eventScripts[SEV_MAX];
	static bool eventRegistered[SEV_MAX];
	static vector<string> ScriptedEventTypeStr;

	ScriptedEventType m_Type;
public:

	ScriptedEvent(ScriptedEventType type);
	~ScriptedEvent();

	static ScriptedEventType ParseType(str type);
	static string GetTypeStr(ScriptedEventType type);
	static void Shutdown();

	void Trigger(std::vector<ScriptedEventArgument> args, ScriptVariable * returnValue = NULL);
	bool Register(ScriptVariable script);
	bool UnRegister();
	bool isRegistered();
};
