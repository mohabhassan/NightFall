#include "ScriptedEvent.h"
#include "Director.h"
#include "Event.h"
ScriptVariable *ScriptedEvent::eventScripts[SEV_MAX] = { NULL };
bool ScriptedEvent::eventRegistered[SEV_MAX] = { false };

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

//used to solve ScriptVariable deallocated after dgamex86mohbt is unloaded
void ScriptedEvent::Shutdown()
{
	for (int i = SEV_CONNECTED; i < SEV_MAX; i++)
	{
		if (eventScripts[i])
		{
			delete eventScripts[i];
		}
	}
}

void ScriptedEvent::Trigger(std::vector<ScriptedEventArgument> args)
{
	Event ev;
	ScriptVariable thread;
	ScriptVariable *file, *label;
	str fileStr, labelStr;
	
	//check ommited, happens before trigger is called instead (for efficiency by not passing args)
	//if (!eventRegistered[m_Type]) // don't execute an unregistered event
	//{
	//return;
	//}

	thread = *eventScripts[m_Type];

	ev.AddValue(thread);

	for (ScriptedEventArgument &arg : args)
	{
		ev.AddValue(arg.getValue());
	}

	if (thread.GetType() == VARIABLE_CONSTARRAY)
	{
		file = thread[1];
		label = thread[2];
		fileStr = file->stringValue();
		labelStr = label->stringValue();
		//fileStr2 = Director->GetString(file->constStringValue());
		//labelStr2 = Director->GetString(label->constStringValue());
	}

	try
	{
		Director->ExecuteScript(&ev);
	}
	catch (const ScriptException& e)
	{
		str wht = e.string;
		throw;//shouldn't interfere with mohbt
	}
}

bool ScriptedEvent::Register(ScriptVariable script)
{
	if (isRegistered())
	{
		return false;
	}
	else
	{
		eventRegistered[m_Type] = true;
		eventScripts[m_Type] = new ScriptVariable(script);
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
		eventRegistered[m_Type] = false;
		delete eventScripts[m_Type];
		eventScripts[m_Type] = NULL;
		return true;
	}
}


bool ScriptedEvent::isRegistered()
{
	return eventRegistered[m_Type];
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
