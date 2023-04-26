#include "Entity.h"
#include "ScriptedEvent.h"
#include "detours.h"
#include "Event.h"
void(__thiscall *Entity::Damage_Orignal)(Entity * _this, Entity *pTargetEntity, Entity *pInflictorEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location);


Entity::Entity()
{
	sizeof(Entity);
}


Entity::~Entity()
{
}
/* Entity::Init()
 * Initialize Entity related hooks.
 **/
void Entity::Init()
{
	//hook damage event for Scripted Event usage.
	Damage_Orignal = reinterpret_cast<void(__thiscall *)(Entity * _this, Entity *pTargetEntity, Entity *pInflictorEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location)>((int)DAMAGE_ADDR);
	LONG ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourAttach(&(PVOID&)(Entity::Damage_Orignal), (PVOID)(&Damage));
	ret = DetourTransactionCommit();
}

/* Entity::Init()
 * Shudown Entity related hooks.
 **/
void Entity::Shutdown()
{
	//remove our hooks.
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

/* MOD_matches()
 * Returns whether MOD matches damage type or not.
 **/
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

/* Damage()
 * Used as a trampoline for the original Damage function.
 * Hooked for ScriptedEvent usage.
 **/
//TODO: make better hook by hooking the event itself.
void __fastcall Damage(Entity * _this, void* edx, Entity * pInflictorEntity, Entity* pAttackerEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location)
{
	if (MOD_matches(meansofdeath, _this->damage_type))
	{
		ScriptedEvent sev(SEV_DAMAGE);
		if (sev.isRegistered())
		{
			//Entity target, Entity inflictor, Float damage, Vector position, Vector direction, Vector normal, Integer knockback, Integer damageflags, Integer meansofdeath, Integer location, Entity entity
			sev.Trigger({
				pAttackerEntity,
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
	_this->Damage_Orignal(_this, pInflictorEntity,
		pAttackerEntity,
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
