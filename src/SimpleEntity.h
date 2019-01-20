#pragma once
#include "Listener.h"
#include "gamex86.h"
typedef int entflags_t;
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
};

