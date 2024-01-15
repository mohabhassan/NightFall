#pragma once
#include "dgamex86.h"
#include "Listener.h"
typedef int entflags_t;

/*
 * Class Entity
 * Used as a sub class for the patch.
 **/
class SimpleEntity : public Listener
{
public:
	// Base coord variable
	Vector			origin;
	Vector			angles;

	// Flag (used to set a class flag)
	entflags_t		entflags;

	// Used by scripts
	str				target;
	str				targetname;

	// Centered origin based on mins/maxs
	Vector			centroid;
public:
	SimpleEntity();
	~SimpleEntity();

	int IsSubclassOfPlayer() const;
	int IsSubclassOfTurretGun() const;
	int IsSubclassOfInventoryItem() const;
};

