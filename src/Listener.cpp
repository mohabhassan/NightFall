#include "Listener.h"

constexpr auto EXECUTESCRIPT_ADDR = 0x3113EE80;


void(__thiscall*Listener::ExecuteScript_ptr) (Listener *_this, Event*ev);

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
}

void Listener::ExecuteScript(Event *ev)
{
	ExecuteScript_ptr(this, ev);
}