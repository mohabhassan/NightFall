#pragma once
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
};

