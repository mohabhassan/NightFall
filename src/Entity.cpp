#include "Entity.h"
#include "ScriptedEvent.h"
#include "detours.h"
#include "Event.h"
#define DAMAGE_ADDR 0x31112370
void(__thiscall *Entity::DamageEvent_Orignal)(Entity*_this, Event *ev);


Entity::Entity()
{
	sizeof(Entity);
}


Entity::~Entity()
{
}

void Entity::Init()
{
	DamageEvent_Orignal = reinterpret_cast<void(__thiscall *)(Entity*_this, Event*)>(DAMAGE_ADDR);
	LONG ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourAttach(&(PVOID&)(Entity::DamageEvent_Orignal), (PVOID)(&DamageEvent));
	ret = DetourTransactionCommit();
}

void Entity::Shutdown()
{
	LONG ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourDetach(&(PVOID&)(Entity::DamageEvent_Orignal), (PVOID)(&DamageEvent));
	ret = DetourTransactionCommit();
}

qboolean Entity::checkEntity()
{
	return entnum > 0 && entnum < globals->num_entities && (Entity *)globals->gentities[entnum].entity == this;
}

void DamageEvent(Entity * _this, Event * ev)
{
	ScriptedEvent sev(SEV_DAMAGE);
	if (sev.isRegistered())
	{
		sev.Trigger({
			ev->GetEntity(1),
			ev->GetFloat(2),
			ev->GetEntity(3),
			ev->GetVector(4),
			ev->GetVector(5),
			ev->GetVector(6),
			ev->GetInteger(7),
			ev->GetInteger(8),
			ev->GetInteger(9),
			ev->GetInteger(10),
			_this
		});
	}
	_this->DamageEvent_Orignal(_this, ev);
}
