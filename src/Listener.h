#pragma once
#include "Class.h"
//#include "Event.h"
#include "GameVersion.h" //for EXECUTESCRIPT_ADDR

class Event;

/*
 * Class Listener
 * Used as an important utility class for the patch.
 **/
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
	static void(__thiscall * ExecuteReturnScript_ptr) (Listener *_this, Event *ev);
	void ExecuteScript(Event *ev);
	void ExecuteReturnScript(Event *ev);
};

