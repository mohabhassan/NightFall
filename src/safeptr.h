#pragma once

class SafePtrBase
{

protected:
	SafePtrBase* prev;
	SafePtrBase* next;
	Class* ptr;

public:
	virtual		~SafePtrBase()
	{
		throw "Shouldn't execute nightfall's SafePtrBaSE Destructor.";
	}
};
template<class T>
class SafePtr : public SafePtrBase
{

};