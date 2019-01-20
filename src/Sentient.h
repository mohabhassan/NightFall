#pragma once
#include "Animate.h"

#define MAX_ACTIVE_WEAPONS 2
#define MAX_DAMAGE_MULTIPLIERS 19

typedef int WeaponPtr[4];//FIXME
typedef int VehiclePtr[4];//FIXME
typedef int TurretGunPtr[4];//FIXME

class ActiveWeapon : public Class
{
public:
	WeaponPtr      weapon;
	weaponhand_t   hand;
	void Archive(Archiver &arc);
};


class Sentient : public Animate
{
protected:
	Vector /*Container<int>*/ inventory;//FIXME
	Vector /*Container<Ammo *>*/ ammo_inventory;//FIXME
	float LMRF;
	WeaponPtr newWeapon;
	int poweruptype;
	int poweruptimer;
	Vector offset_color;
	Vector offset_delta;
	float offset_time;
	float charge_start_time;
	str blood_model;
	WeaponPtr activeWeaponList[MAX_ACTIVE_WEAPONS];
	ActiveWeapon newActiveWeapon;
	WeaponPtr holsteredWeapon;
	bool weapons_holstered_by_code;
	ActiveWeapon lastActiveWeapon;
	float m_fDamageMultipliers[MAX_DAMAGE_MULTIPLIERS];
	VehiclePtr /*class SafePtr<Vehicle>*/ m_pVehicle;
	TurretGunPtr/*SafePtr< TurretGun >*/ m_pTurret;
	SafePtr< Entity > m_pLadder;
	str m_sHelmetSurface1;
	str m_sHelmetSurface2;
	str m_sHelmetTiki;
	float m_fHelmetSpeed;
	bool m_bDontDropWeapons;
public:

	Vector mTargetPos;
	float mAccuracy;
	SafePtr<Sentient> m_pNextSquadMate;
	SafePtr<Sentient> m_pPrevSquadMate;
	Sentient *m_NextSentient;
	Sentient *m_PrevSentient;
	int m_Team;
	int m_iAttackerCount;
	SafePtr<Entity> m_pLastAttacker;
	SafePtr<Sentient> m_Enemy;
	float m_fPlayerSightLevel;
	bool m_bIsDisguised;
	bool m_bHasDisguise;
	int m_ShowPapersTime;
	int m_iLastHitTime;
	int m_iThreatBias;
	Vector gunoffset;
	Vector eyeposition;
	int viewheight;
	Vector m_vViewVariation;
	int means_of_death;
	bool in_melee_attack;
	bool in_block;
	bool in_stun;
	bool on_fire;
	float on_fire_stop_time;
	float next_catch_on_fire_time;
	int on_fire_tagnums[3];
	SafePtr<Entity> fire_owner;
	bool attack_blocked;
	float attack_blocked_time;
	float max_mouth_angle;
	int max_gibs;
	float next_bleed_time;
	bool m_bFootOnGround_Right;
	bool m_bFootOnGround_Left;
public:
	Sentient();
	~Sentient();
};

