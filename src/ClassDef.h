#pragma once
#include "Event.h"
#include "Class.h"

template< class Type >
class ResponseDef
{
public:
	Event			*event;
	DWORD			dummy1;//Extra in BT
	void			(Type::*response)(Event *ev);
	DWORD			dummy2;//Extra in BT
	EventDef		*def;
	DWORD			dummy3;//Extra in BT
};


class ClassDef
{
public:
	const char								*classname;
	const char								*classID;
	const char								*superclass;
	void									*(*newInstance)(void);
	int										classSize;
	ResponseDef<Class>						*responses;
	ResponseDef<Class>						**responseLookup;
	ClassDef								*super;
	ClassDef								*next;
	ClassDef								*prev;

#ifndef NO_SCRIPTENGINE
	void /*con_set<const_str, const_str>*/	*waitTillSet;//FIXME ?
#endif

public:
	ClassDef();
	~ClassDef();
	void			BuildExtendedResponseList(ResponseDef<Class> Responses[], int eventCount);
	static void		(__thiscall *BuildResponseList_Orignal)(ClassDef*_this);
	static void		Init();
};

void  __fastcall  BuildResponseListHook(ClassDef*_this);