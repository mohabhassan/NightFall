#include "..\BaseHeaders\SimpleEntity.h"
#include "..\BaseHeaders\SimpleEntity.h"
#include "..\BaseHeaders\SimpleEntity.h"
#include "SimpleEntity.h"



SimpleEntity::SimpleEntity()
{
	sizeof(SimpleEntity);
}


SimpleEntity::~SimpleEntity()
{
}

int SimpleEntity::IsSubclassOfPlayer() const
{
	return (entflags & ECF_PLAYER);
}

int SimpleEntity::IsSubclassOfTurretGun() const
{
	return (entflags & ECF_TURRET);
}

int SimpleEntity::IsSubclassOfInventoryItem() const
{
	return (entflags & ECF_INVENTORYITEM);
}