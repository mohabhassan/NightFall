#pragma once

class SafePtrBase;
class Class
{
public:
	void				 *vftable;
	SafePtrBase *SafePtrList;//FIXME
public:
	Class();
	~Class();
};

