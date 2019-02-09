#include "ScriptedEvent.h"
#include "Director.h"
#include "Event.h"
std::string ScriptedEvent::eventScripts[SEV_MAX];
bool ScriptedEvent::eventSet[SEV_MAX] = { false };

extern DirectorClass *Director;

ScriptedEvent::ScriptedEvent(ScriptedEventType type)
	: m_Type (type)
{
}

ScriptedEvent::~ScriptedEvent()
{
}

ScriptedEventType ScriptedEvent::ParseType(str type)
{
	if (type == "connected")
	{
		return SEV_CONNECTED;
	}
	else if (type == "disconnected")
	{
		return SEV_DISCONNECTED;
	}
	else if (type == "spawn")
	{
		return SEV_SPAWN;
	}
	else if (type == "damage")
	{
		return SEV_DAMAGE;
	}
	else if (type == "kill")
	{
		return SEV_KILL;
	}
	else if (type == "keypress")
	{
		return SEV_KEYPRESS;
	}
	else if (type == "servercommand")
	{
		return SEV_SERVERCOMMAND;
	}
	else if (type == "intermission")
	{
		return SEV_INTERMISSION;
	}
	else
	{
		return SEV_UNK;
	}
}

void ScriptedEvent::Trigger(std::vector<ScriptedEventArgument> args)
{
	Event ev;
	ScriptVariable thread;
	
	//check ommited, happens before trigger is called instead (for efficiency)
	//if (!eventSet[m_Type]) // don't execute an unregistered event
	//{
	//return;
	//}

	thread.setStringValue(eventScripts[m_Type].c_str());

	ev.AddValue(thread);

	for (ScriptedEventArgument &arg : args)
	{
		ev.AddValue(arg.getValue());
	}

	Director->ExecuteScript(&ev);
}

bool ScriptedEvent::Register(std::string script)
{
	if (isRegistered())
	{
		return false;
	}
	else
	{
		eventSet[m_Type] = true;
		eventScripts[m_Type] = script;
		return true;
	}

}

bool ScriptedEvent::UnRegister()
{
	if (!isRegistered())
	{
		return false;
	}
	else
	{
		eventSet[m_Type] = false;
		eventScripts[m_Type].clear();
		return true;
	}
}

str ScriptedEvent::GetScript()
{
	return eventScripts[m_Type].c_str();
}

bool ScriptedEvent::isRegistered()
{
	return eventSet[m_Type];
}


ScriptedEventArgument::ScriptedEventArgument(Entity * e)
{
	var.setListenerValue(e);
}

ScriptedEventArgument::ScriptedEventArgument(Vector v)
{
	var.setVectorValue(v);
}

ScriptedEventArgument::ScriptedEventArgument(str s)
{
	var.setStringValue(s);
}

ScriptedEventArgument::ScriptedEventArgument(int i)
{
	var.setIntValue(i);
}

ScriptedEventArgument::ScriptedEventArgument(float f)
{
	var.setFloatValue(f);
}

ScriptVariable & ScriptedEventArgument::getValue()
{
	return var;
}
