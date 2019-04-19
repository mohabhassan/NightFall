#pragma once
#include "Animate.h"
#include "Container.h"
#define MAX_ACTIVE_WEAPONS WEAPON_ERROR
#define MAX_DAMAGE_MULTIPLIERS 19

#define ACTIVEWEAPONLIST_OFFSET 1036
#define SENTEINT_SIZE 1504

typedef SafePtr<Animate> WeaponPtr;//FIXME
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
	//Can't bother, more info is found inside Sentient.txt
	Container<int> inventory;
	uint8_t sfiller1[ACTIVEWEAPONLIST_OFFSET - sizeof(inventory) - sizeof(Animate)];
	WeaponPtr activeWeaponList[MAX_ACTIVE_WEAPONS];
	uint8_t sfiller2[SENTEINT_SIZE - sizeof(activeWeaponList) - ACTIVEWEAPONLIST_OFFSET];
#if 0//940
	Vector /*Container<Ammo *>*/ ammo_inventory;//FIXME
	float LMRF;
	WeaponPtr newWeapon;
	int poweruptype;//984 correct
	int poweruptimer;//988 correct
	Vector offset_color;
	Vector offset_delta;
	float offset_time;// maybe move offset_time to end ?
	float charge_start_time;// 1020 should be 1016
	str blood_model;// 1024 should be 1020
	//delta +4
	WeaponPtr activeWeaponList[MAX_ACTIVE_WEAPONS];// 1028 should be 1036
	ActiveWeapon newActiveWeapon;// 1060 should be 1068
	WeaponPtr holsteredWeapon;// 1088 should be 1096
	//delta -8

	bool weapons_holstered_by_code;// 1104 should be 1100
	ActiveWeapon lastActiveWeapon;// 1108 should be 1116
	float m_fDamageMultipliers[MAX_DAMAGE_MULTIPLIERS];// ??? should be 1132
	VehiclePtr /*class SafePtr<Vehicle>*/ m_pVehicle;// ???? should be 1220
	TurretGunPtr/*SafePtr< TurretGun >*/ m_pTurret;// ???? should be 1236
	SafePtr< Entity > m_pLadder;// ???? should be 1240
	str m_sHelmetSurface1;//1260 should be 1256
	str m_sHelmetSurface2;//1264 should be 1260
	str m_sHelmetTiki;//1268, should be 1264
	float m_fHelmetSpeed;//1272, should be 1268
	bool m_bDontDropWeapons;//1276, should be 1272
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
#endif
	
public:
	Sentient();
	~Sentient();
	static void Init();
	static Animate *(__thiscall *GetActiveWeapon_real)(Sentient*_this, weaponhand_t hand);
	Animate * GetActiveWeapon(weaponhand_t hand);
};

