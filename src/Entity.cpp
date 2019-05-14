#include "Entity.h"
#include "ScriptedEvent.h"
#include "detours.h"
#include "Event.h"
#define DAMAGE_ADDR 0x31112130
void(__thiscall *Entity::Damage_Orignal)(Entity * _this, Entity *pTargetEntity, Entity *pInflictorEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location);


Entity::Entity()
{
	sizeof(Entity);
}


Entity::~Entity()
{
}

void Entity::Init()
{
	Damage_Orignal = reinterpret_cast<void(__thiscall *)(Entity * _this, Entity *pTargetEntity, Entity *pInflictorEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location)>(DAMAGE_ADDR);
	LONG ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourAttach(&(PVOID&)(Entity::Damage_Orignal), (PVOID)(&Damage));
	ret = DetourTransactionCommit();
}

void Entity::Shutdown()
{
	LONG ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourDetach(&(PVOID&)(Entity::Damage_Orignal), (PVOID)(&Damage));
	ret = DetourTransactionCommit();
}

qboolean Entity::checkEntity()
{
	return entnum > 0 && entnum < globals->num_entities && (Entity *)globals->gentities[entnum].entity == this;
}
//
//void Entity_Damage_hook(void *pThis, Entity *pTargetEntity, Entity *pInflictorEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location)

qboolean MOD_matches(int incoming_damage, int damage_type)
{
	if (damage_type == -1)
	{
		return true;
	}
	else
	{
		return incoming_damage == damage_type;
	}
}

//TODO: make better hook by hooking the event itself.
void __fastcall Damage(Entity * _this, void* edx, Entity *pTargetEntity, Entity *pInflictorEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location)
{
	if (MOD_matches(meansofdeath, _this->damage_type))
	{
		ScriptedEvent sev(SEV_DAMAGE);
		if (sev.isRegistered())
		{
			//Entity target, Entity inflictor, Float damage, Vector position, Vector direction, Vector normal, Integer knockback, Integer damageflags, Integer meansofdeath, Integer location, Entity entity
			sev.Trigger({
				pTargetEntity,
				pInflictorEntity,
				damage,
				Vector(vectPositionx,	vectPositiony,	vectPositionz),
				Vector(vectDirectionx,	vectDirectiony, vectDirectionz),
				Vector(vectNormalx,		vectNormaly,	vectNormalz),
				knockback,
				damageflags,
				meansofdeath,
				location,
				_this
				});
		}
	}
	_this->Damage_Orignal(_this, pTargetEntity,
		pInflictorEntity,
		damage, 
		vectPositionx, vectPositiony, vectPositionz,
		vectDirectionx, vectDirectiony, vectDirectionz,
		vectNormalx, vectNormaly, vectNormalz,
		knockback,
		damageflags,
		meansofdeath,
		location
	);
}
