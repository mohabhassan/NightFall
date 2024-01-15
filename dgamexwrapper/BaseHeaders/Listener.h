#pragma once
#include "Class.h"
//#include "Event.h"
#include "GameVersion.h" //for EXECUTESCRIPT_ADDR

class Event;

// entity subclass
#define ECF_ENTITY        (1 << 0)
#define ECF_ANIMATE       (1 << 1)
#define ECF_SENTIENT      (1 << 2)
#define ECF_PLAYER        (1 << 3)
#define ECF_ACTOR         (1 << 4)
#define ECF_ITEM          (1 << 5)
#define ECF_INVENTORYITEM (1 << 6)
#define ECF_WEAPON        (1 << 7)
#define ECF_PROJECTILE    (1 << 8)
#define ECF_DOOR          (1 << 9)
#define ECF_CAMERA        (1 << 10)
#define ECF_VEHICLE       (1 << 11)
#define ECF_VEHICLETANK   (1 << 12)
#define ECF_VEHICLETURRET (1 << 13)
#define ECF_TURRET        (1 << 14)
#define ECF_PATHNODE      (1 << 15)
#define ECF_WAYPOINT      (1 << 16)
#define ECF_TEMPWAYPOINT  (1 << 17)
#define ECF_VEHICLEPOINT  (1 << 18)
#define ECF_SPLINEPATH    (1 << 19)
#define ECF_CRATEOBJECT   (1 << 20)

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

