#include "Sentient.h"



Sentient::Sentient()
{
	sizeof(Sentient);
}


Sentient::~Sentient()
{
}

Animate *Sentient::GetActiveWeapon
(
	weaponhand_t hand
)

{
	if ((hand > MAX_ACTIVE_WEAPONS) || (hand < 0))
	{
		gi.Printf("newpatchaname error: Sentient::GetActiveWeapon: Weapon hand number \"%d\" is out of bounds of 0 to MAX_ACTIVE_WEAPONS:%d\n", hand, MAX_ACTIVE_WEAPONS);
		return NULL;
	}
	else
	{
		return (Animate *)activeWeaponList[hand][3];
	}
}
