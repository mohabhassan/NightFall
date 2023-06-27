#pragma once
#include "safeptr.h"
#include "ClassMemory.h"
/*
 * Class Class
 * Used as a sub class for the patch.
 **/
class Class
{
public:
	//void				 *vftable;
	SafePtrBase *SafePtrList;//FIXME
public:
	Class();
	virtual ~Class();
	CLASS_CUSTOM_ALLOCATION;
};

