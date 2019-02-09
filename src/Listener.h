#pragma once
#include "Class.h"
//#include "Event.h"

class Event;

class Listener : public Class
{
	//void *__vfptr;//Class vfptr is used instead
public:
	void /*class con_map<const_str, ContainerClass<SafePtr<Listener> > >*/ *m_NotifyList;//FIXME
	void /*class con_map<const_str, ContainerClass<SafePtr<Listener> > >*/ *m_WaitForList;
protected:
	void /*class ScriptVariableList*/ *vars;//FIXME
public:
	Listener();
	~Listener();
	static void Init();
	static void(__thiscall * ExecuteScript_ptr) (Listener *_this, Event *ev);
	void ExecuteScript(Event *ev);
};

