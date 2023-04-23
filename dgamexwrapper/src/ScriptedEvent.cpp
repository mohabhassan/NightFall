#include "ScriptedEvent.h"
#include "Director.h"
#include "Event.h"
#include "ScriptException.h"

ScriptVariable *ScriptedEvent::eventScripts[SEV_MAX] = { NULL };
bool ScriptedEvent::eventRegistered[SEV_MAX] = { false };


extern DirectorClass *Director;

vector<string> ScriptedEvent::ScriptedEventTypeStr =
{
	"connected",
	"disconnected",
	"spawn",
	"damage",
	"kill",
	"keypress",
	"intermission",
	"servercommand",
	"dmmessage"
};

ScriptedEvent::ScriptedEvent(ScriptedEventType type)
	: m_Type (type)
{
}

ScriptedEvent::~ScriptedEvent()
{
}

ScriptedEventType ScriptedEvent::ParseType(str type)
{
	auto it = find(ScriptedEventTypeStr.begin(), ScriptedEventTypeStr.end(), type.c_str());
	if (it == ScriptedEventTypeStr.end())
	{
		return SEV_UNK;
	}
	else
	{
		return ScriptedEventType(it - ScriptedEventTypeStr.begin());
	}
}
string ScriptedEvent::GetTypeStr(ScriptedEventType type)
{
	if (type == SEV_UNK || type == SEV_MAX)
	{
		return "unknown";
	}
	else
	{
		return ScriptedEventTypeStr[type];
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

//returns return value index in returnValues, should remove it manaually by calling func.
//returns defaultReturnValueIndex if no return value.
void ScriptedEvent::Trigger(std::vector<ScriptedEventArgument> args, ScriptVariable * returnValue)
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
		if (returnValue)
		{
			Director->ExecuteReturnScript(&ev);
			*returnValue = ev.GetValue(ev.NumArgs());
		}
		else
		{
			Director->ExecuteScript(&ev);
		}
	}
	catch (const ScriptException& e)
	{
		gi.Printf(PATCH_NAME " Scripted event error for event %s: %s\n", GetTypeStr(m_Type).c_str(), e.string.c_str());
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

ScriptedEventArgument::ScriptedEventArgument(vector<string> &arr)
{
	ScriptVariable index, value;
	for (size_t i = 0; i < arr.size(); i++)
	{
		index.setIntValue(i);
		value.setStringValue(arr[i].c_str());
		var.setArrayAtRef(index, value);
	}
}

ScriptVariable & ScriptedEventArgument::getValue()
{
	return var;
}
