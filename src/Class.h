#pragma once


class Class
{
	void				 *vftable;
	void /*SafePtrBase*/ *SafePtrList;//FIXME
public:
	Class();
	~Class();
};

