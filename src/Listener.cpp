#include "Listener.h"


void(__thiscall*Listener::ExecuteScript_ptr) (Listener *_this, Event*ev);
void(__thiscall*Listener::ExecuteReturnScript_ptr) (Listener *_this, Event*ev);

Listener::Listener()
{
	sizeof(Listener);
}


Listener::~Listener()
{
}

/*
 * Listener::Init()
 * Initialize important function pointers.
 **/
void Listener::Init()
{
	ExecuteScript_ptr = reinterpret_cast<void(__thiscall*)(Listener *, Event *)>((int)EXECUTESCRIPT_ADDR);
	ExecuteReturnScript_ptr = reinterpret_cast<void(__thiscall*)(Listener *, Event *)>((int)EXECUTERETURNSCRIPT_ADDR);
}

/*
 * Listener::ExecuteScript()
 * Executes given game script inside ev.
 * ev should have first argument as the script
 * later arguments are passed to script itself
 **/
void Listener::ExecuteScript(Event *ev)
{
	ExecuteScript_ptr(this, ev);
}

/*
 * Listener::ExecuteReturnScript()
 * Executes given game script inside ev.
 * ev should have first argument as the script
 * later arguments are passed to script itself
 * return value is add to ev after function executes, it is the last argument inside ev.
 * if script has any wait or waitframe inside, return value is delayed, it will have a type of VARIABLE_POINTER
 * otherwise, it will have proper return type.
 **/
//ev has original arguments + return value.
//return value is last one inside event.
void Listener::ExecuteReturnScript(Event *ev)
{
	ExecuteReturnScript_ptr(this, ev);
}