#include "Sentient.h"
#include "AddressDefinitions.h"

Animate *(__thiscall *SentientNF::GetActiveWeapon_real)(Sentient*_this, weaponhand_t hand);
/*
Sentient::Sentient()
{
	sizeof(Sentient);
}


Sentient::~Sentient()
{
}
template<typename T, typename U> constexpr size_t classOffsetOf(U T::*member)
{
	return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

*/
/* 
 * Sentient::Init()
 * Initialize related sentient hooks.
 * */
void SentientNF::Init()
{
	GetActiveWeapon_real = reinterpret_cast<Animate *(__thiscall *)(Sentient *__this, weaponhand_t hand)>((int)GETACTIVEWEAPON_ADDR);
	//gi->Printf("offset of inventory = %d \n", classOffsetOf(&Sentient::inventory));//940
	//gi->Printf("offset of activeWeaponList = %d \n", classOffsetOf(&Sentient::activeWeaponList));//??? should be 1036

	/*
	gi->Printf("offset of ammo_inventory = %d \n", classOffsetOf(&Sentient::ammo_inventory));//FIXME
	gi->Printf("offset of LMRF = %d \n", classOffsetOf(&Sentient::LMRF));
 	gi->Printf("offset of newWeapon = %d \n", classOffsetOf(&Sentient::newWeapon));
	gi->Printf("offset of poweruptype = %d \n", classOffsetOf(&Sentient::poweruptype));
	gi->Printf("offset of poweruptimer = %d \n", classOffsetOf(&Sentient::poweruptimer));//correct
	gi->Printf("offset of offset_color = %d \n", classOffsetOf(&Sentient::offset_color));
	gi->Printf("offset of offset_delta = %d \n", classOffsetOf(&Sentient::offset_delta));
	gi->Printf("offset of offset_time = %d \n", classOffsetOf(&Sentient::offset_time));
	gi->Printf("offset of charge_start_time = %d \n", classOffsetOf(&Sentient::charge_start_time));
	gi->Printf("offset of blood_model = %d \n", classOffsetOf(&Sentient::blood_model));
	gi->Printf("offset of newActiveWeapon = %d \n", classOffsetOf(&Sentient::newActiveWeapon));// ??? should be 1076
	gi->Printf("offset of holsteredWeapon = %d \n", classOffsetOf(&Sentient::holsteredWeapon));// ??? should be 1096, should be a Weapon * ?
	gi->Printf("offset of weapons_holstered_by_code = %d \n", classOffsetOf(&Sentient::weapons_holstered_by_code));// ??? should be 1100
	gi->Printf("offset of lastActiveWeapon = %d \n", classOffsetOf(&Sentient::lastActiveWeapon));
	gi->Printf("offset of m_fDamageMultipliers = %d \n", classOffsetOf(&Sentient::m_fDamageMultipliers));// ??? should be 1132
	gi->Printf("offset of m_pVehicle = %d \n", classOffsetOf(&Sentient::m_pVehicle));// ???? should be 1220
	gi->Printf("offset of m_pTurret = %d \n", classOffsetOf(&Sentient::m_pTurret));// ???? should be 1236
	gi->Printf("offset of m_pLadder = %d \n", classOffsetOf(&Sentient::m_pLadder));// ???? should be 1240
	gi->Printf("offset of m_sHelmetSurface1 = %d \n", classOffsetOf(&Sentient::m_sHelmetSurface1));//1260 should be 1256
	gi->Printf("offset of m_sHelmetSurface2 = %d \n", classOffsetOf(&Sentient::m_sHelmetSurface2));//1264 should be 1260
	gi->Printf("offset of m_sHelmetTiki = %d \n", classOffsetOf(&Sentient::m_sHelmetTiki));//1268, should be 1264
	gi->Printf("offset of m_fHelmetSpeed = %d \n", classOffsetOf(&Sentient::m_fHelmetSpeed));//1272, should be 1268
	gi->Printf("offset of m_bDontDropWeapons = %d \n", classOffsetOf(&Sentient::m_bDontDropWeapons));//1276, should be 1272
	gi->Printf("offset of mTargetPos = %d \n", classOffsetOf(&Sentient::mTargetPos));
	gi->Printf("offset of mAccuracy = %d \n", classOffsetOf(&Sentient::mAccuracy));
	gi->Printf("offset of m_pNextSquadMate = %d \n", classOffsetOf(&Sentient::m_pNextSquadMate));
	gi->Printf("offset of m_pPrevSquadMate = %d \n", classOffsetOf(&Sentient::m_pPrevSquadMate));
	gi->Printf("offset of m_NextSentient = %d \n", classOffsetOf(&Sentient::m_NextSentient));
	gi->Printf("offset of m_PrevSentient = %d \n", classOffsetOf(&Sentient::m_PrevSentient));
	gi->Printf("offset of m_Team = %d \n", classOffsetOf(&Sentient::m_Team));
	gi->Printf("offset of m_iAttackerCount = %d \n", classOffsetOf(&Sentient::m_iAttackerCount));
	gi->Printf("offset of m_pLastAttacker = %d \n", classOffsetOf(&Sentient::m_pLastAttacker));
	gi->Printf("offset of m_Enemy = %d \n", classOffsetOf(&Sentient::m_Enemy));
	gi->Printf("offset of m_fPlayerSightLevel = %d \n", classOffsetOf(&Sentient::m_fPlayerSightLevel));
	gi->Printf("offset of m_bIsDisguised = %d \n", classOffsetOf(&Sentient::m_bIsDisguised));
	gi->Printf("offset of m_bHasDisguise = %d \n", classOffsetOf(&Sentient::m_bHasDisguise));
	gi->Printf("offset of m_ShowPapersTime = %d \n", classOffsetOf(&Sentient::m_ShowPapersTime));
	gi->Printf("offset of m_iLastHitTime = %d \n", classOffsetOf(&Sentient::m_iLastHitTime));
	gi->Printf("offset of m_iThreatBias = %d \n", classOffsetOf(&Sentient::m_iThreatBias));
	gi->Printf("offset of gunoffset = %d \n", classOffsetOf(&Sentient::gunoffset));
	gi->Printf("offset of eyeposition = %d \n", classOffsetOf(&Sentient::eyeposition));
	gi->Printf("offset of viewheight = %d \n", classOffsetOf(&Sentient::viewheight));
	gi->Printf("offset of m_vViewVariation = %d \n", classOffsetOf(&Sentient::m_vViewVariation));
	gi->Printf("offset of means_of_death = %d \n", classOffsetOf(&Sentient::means_of_death));
	gi->Printf("offset of in_melee_attack = %d \n", classOffsetOf(&Sentient::in_melee_attack));
	gi->Printf("offset of in_block = %d \n", classOffsetOf(&Sentient::in_block));
	gi->Printf("offset of in_stun = %d \n", classOffsetOf(&Sentient::in_stun));
	gi->Printf("offset of on_fire = %d \n", classOffsetOf(&Sentient::on_fire));
	gi->Printf("offset of on_fire_stop_time = %d \n", classOffsetOf(&Sentient::on_fire_stop_time));
	gi->Printf("offset of next_catch_on_fire_time = %d \n", classOffsetOf(&Sentient::next_catch_on_fire_time));
	gi->Printf("offset of on_fire_tagnums = %d \n", classOffsetOf(&Sentient::on_fire_tagnums));
	gi->Printf("offset of fire_owner = %d \n", classOffsetOf(&Sentient::fire_owner));
	gi->Printf("offset of attack_blocked = %d \n", classOffsetOf(&Sentient::attack_blocked));
	gi->Printf("offset of attack_blocked_time = %d \n", classOffsetOf(&Sentient::attack_blocked_time));
	gi->Printf("offset of max_mouth_angle = %d \n", classOffsetOf(&Sentient::max_mouth_angle));
	gi->Printf("offset of max_gibs = %d \n", classOffsetOf(&Sentient::max_gibs));
	gi->Printf("offset of next_bleed_time = %d \n", classOffsetOf(&Sentient::next_bleed_time));
	gi->Printf("offset of m_bFootOnGround_Right = %d \n", classOffsetOf(&Sentient::m_bFootOnGround_Right));
	gi->Printf("offset of m_bFootOnGround_Left = %d \n", classOffsetOf(&Sentient::m_bFootOnGround_Left));
	*/
}
/*
 * Sentient::GetActiveWeapon()
 * Gets currently active weapon in given hand.
 * */
Animate * SentientNF::GetActiveWeapon
(
	weaponhand_t hand
)

{
	return GetActiveWeapon_real((Sentient *)realSentient, hand);
	/*
	////////////////////////////////////////////
	if ((hand > MAX_ACTIVE_WEAPONS) || (hand < 0))
	{
		gi->Printf(PATCH_NAME " error: Sentient::GetActiveWeapon: Weapon hand number \"%d\" is out of bounds of 0 to MAX_ACTIVE_WEAPONS:%d\n", hand, MAX_ACTIVE_WEAPONS);
		return NULL;
	}
	else
	{
		sizeof(Sentient);
		
		//int off = classOffsetOf(&Sentient::activeWeaponList);
		//int off2 = classOffsetOf(&Sentient::blood_model);
		//int off3 = classOffsetOf(&Sentient::charge_start_time);
		//int off4 = classOffsetOf(&Sentient::m_bDontDropWeapons);
		return (Animate*)(activeWeaponList[hand].Pointer());
	}
	*/
}
