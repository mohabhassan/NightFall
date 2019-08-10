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


void Listener::Init()
{
	ExecuteScript_ptr = reinterpret_cast<void(__thiscall*)(Listener *, Event *)>(EXECUTESCRIPT_ADDR);
	ExecuteReturnScript_ptr = reinterpret_cast<void(__thiscall*)(Listener *, Event *)>(EXECUTERETURNSCRIPT_ADDR);
}

void Listener::ExecuteScript(Event *ev)
{
	ExecuteScript_ptr(this, ev);
}

//ev has original arguments + return value.
//return value is last one inside event.
void Listener::ExecuteReturnScript(Event *ev)
{
	ExecuteReturnScript_ptr(this, ev);
}