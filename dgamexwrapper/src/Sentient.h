#pragma once
#include "Animate.h"
#include "OffsetDefinitions.h"
#define MAX_ACTIVE_WEAPONS WEAPON_ERROR
#define MAX_DAMAGE_MULTIPLIERS 19

class Sentient {}; // empty definition to avoid mistakes

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

class Container_Inventory
{
	int	*objlist;
	int		numobjects;
	int		maxobjects;
public:
	int NumObjects() const
	{
		return numobjects;
	}
	int & ObjectAt(int index) const
	{
		if ((index <= 0) || (index > numobjects)) {
			gi->Error(ERR_DROP, "Container::ObjectAt : index out of range");
		}

		return objlist[index - 1];
	}
	int & operator[](int index) const
	{
		return ObjectAt(index + 1);
	}
};

/*
 * Class Sentient
 * Used as an important utility class in the patch.
 **/
class SentientAA : public AnimateAA
{
public:
	//Can't bother, more info is found inside Sentient.txt
	Container_Inventory /*Container<int>*/ inventory;
	uint8_t sfiller1[ACTIVEWEAPONLIST_OFFSET_AA - sizeof(inventory) - sizeof(AnimateAA)];
	WeaponPtr activeWeaponList[MAX_ACTIVE_WEAPONS];
	uint8_t sfiller2[SENTEINT_SIZE_AA - sizeof(activeWeaponList) - ACTIVEWEAPONLIST_OFFSET_AA];
};

class SentientDSH : public AnimateDSH
{
public:
	//Can't bother, more info is found inside Sentient.txt
	Container_Inventory /*Container<int>*/ inventory;
	uint8_t sfiller1[ACTIVEWEAPONLIST_OFFSET_DSH - sizeof(inventory) - sizeof(AnimateDSH)];
	WeaponPtr activeWeaponList[MAX_ACTIVE_WEAPONS];
	uint8_t sfiller2[SENTEINT_SIZE_DSH - sizeof(activeWeaponList) - ACTIVEWEAPONLIST_OFFSET_DSH];
};

using SentientDBT = SentientDSH;


/*
 * Class SentientNF
 * Used as an wrapper class for different sentient definitions (depending on which game is running).
 **/

class SentientNF : public EntityNF
{

	union realSentientType
	{
		SentientAA sentientAA;
		SentientDSH sentientDSH;
		SentientDBT sentientDBT;
	};
	realSentientType* realSentient;

#define SENTIENTNF_MEMEBER_GETTER(varname) \
		decltype(SentientAA::varname)& init_##varname() \
		{\
			static decltype(SentientAA::varname) s_##varname; \
			if (!realSentient) return s_##varname; \
			if (gameInfo.IsAA())\
				return realSentient->sentientAA.varname;\
			else if (gameInfo.IsSH())\
				return realSentient->sentientDSH.varname;\
			else if (gameInfo.IsBT())\
				return realSentient->sentientDBT.varname;\
		}

	SENTIENTNF_MEMEBER_GETTER(inventory);
	//SENTIENTNF_MEMEBER_GETTER(activeWeaponList);



#undef SENTIENTNF_MEMEBER_GETTER
public:
	Container_Inventory& inventory;
	SentientNF(Sentient *s)
		: EntityNF((Entity*) s), realSentient((realSentientType*) s), inventory(init_inventory())
	{

	}

	bool isValid()
	{
		return realSentient != NULL;
	}
	static void Init();
	static Animate* (__thiscall* GetActiveWeapon_real)(Sentient* _this, weaponhand_t hand);
	Animate* GetActiveWeapon(weaponhand_t hand);
};

