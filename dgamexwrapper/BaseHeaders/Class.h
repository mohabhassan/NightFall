#pragma once
#include "ClassMemory.h"

class SafePtrBase;
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
#ifndef REBORNSECURITYFIXES_EXPORTS
	CLASS_CUSTOM_ALLOCATION;
#endif
};

#include "safeptr.h"
