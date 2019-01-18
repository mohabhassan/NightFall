#include "ClassDef.h"
#include "Player.h"
#include "ScriptThread.h"
#include <cstring>

#define	BUILDREPONSELIST_ADDRESS 0x310FDBB0
#define	ADDNEWKEYENTRY_ADDR 0x310FF160

void(__thiscall *ClassDef::BuildResponseList_Orignal)(ClassDef*_this);
using addNewKeyEntryPtr = Entry< Event *, EventDef > *(__thiscall *)(con_map< Event *, EventDef > *_this, void*r, unsigned int loc);
static addNewKeyEntryPtr addNewKeyEntry;



ClassDef::ClassDef()
{
	//Not used
}


ClassDef::~ClassDef()
{
	//Not used
}
EventDef* getInfo(ResponseDef<Class>* r)
{
	Entry< Event *, EventDef > *entry = Event::eventDefList->getConSet().findKeyEntry(r->event);

	if (entry != NULL) {
		return &entry->value;
	}
	else {
		return &addNewKeyEntry(Event::eventDefList, r, (unsigned int)r->event % Event::eventDefList->getConSet().getTableLength())->value;
	}
	//sizeof(con_map< Event *, EventDef >);
	//return &((*eventDefList)[this]);
}

void ClassDef::BuildExtendedResponseList(ResponseDef<Class> exResponses[], int eventCount)
{
	ClassDef		*_this = this;
	ClassDef		*superC;
	ResponseDef<Class> *r;
	size_t			num;

	if (_this->responseLookup)
	{
		return;
	}


	num = Event::NumEventCommands() + 1;
	
	size_t size = num * sizeof(ResponseDef< Class > *);

	_this->responseLookup = (ResponseDef< Class > **)gi.Malloc(size);
	sizeof(ClassDef);
	superC = _this->super;

	if (superC)
	{
		BuildResponseListHook(superC);
		memcpy(_this->responseLookup, superC->responseLookup, size);
	}
	else
	{
		memset(_this->responseLookup, 0, size);
	}

	r = _this->responses;

	if (r)
	{
		for (int i = 0, ev; r[i].event != NULL; i++)
		{
			// in BT it allocates 2 ResponseDefs insde c->responses
			// one contains event and event and response func,
			// the other contains def
			// this could be some sort of compiler optimization
			// UPDATE: Could be wrong, maybe ResponseDef is larger
			// UPDATE: yes, ResponseDef is larger. I've added 3 dummies corresponding to the offsets.
			Event* evi = r[i].event;
			ev = (int)evi->eventnum;
			r[i].def = getInfo(&r[i]);

			if (r[i].response)
			{
				_this->responseLookup[ev] = &r[i];
			}
			else
			{
				_this->responseLookup[ev] = NULL;
			}
		}
	}


	r = exResponses;
	if (eventCount > 0 && r)
	{
		for (int i = 0, ev; r[i].event != NULL; i++)
		{
			// in BT it allocates 2 ResponseDefs insde c->responses
			// one contains event and event and response func,
			// the other contains def
			// this could be some sort of compiler optimization
			// UPDATE: Could be wrong, maybe ResponseDef is larger
			// UPDATE: yes, ResponseDef is larger. I've added 3 dummies corresponding to the offsets.
			Event* evi = r[i].event;
			ev = (int)evi->eventnum;
			r[i].def = getInfo(&r[i]);

			if (r[i].response)
			{
				_this->responseLookup[ev] = &r[i];
			}
			else
			{
				_this->responseLookup[ev] = NULL;
			}
		}
	}
}

/*
void ClassDef::BuildExtendedResponseList(ResponseDef<Class> exResponses[], int eventCount)
{
	ClassDef		*c;
	ResponseDef<Class> *r;
	qboolean		*set;
	int			num;

	if (responseLookup)
	{
		gi.Free(responseLookup);

		responseLookup = NULL;
	}

	num = Event::NumEventCommands()+1;//size will be total event count, because it WAS faster to look for an event via eventnum
									//nowadays there's not much overhead in performance, TODO: change size to appropriate.
	//num += eventCount; // add up our extra event count : not needed, Event::LoadEvents() takes care of it.
	responseLookup = (ResponseDef< Class > **)gi.Malloc(sizeof(ResponseDef< Class > *) * num);
	memset(responseLookup, 0, sizeof(ResponseDef< Class > *) * num);

	set = new qboolean[num];
	memset(set, 0, sizeof(qboolean) * num);

	this->numEvents = num;

	for (c = this; c != NULL; c = c->super)
	{
		r = c->responses;

		if (r)
		{
			for (int i = 0, ev; r[i].event != NULL; i++)
			{
				//in BT it allocates 2 ResponseDefs insde c->responses
				//one contains event and event and response func,
				// the other contains def
				// this could be some sort of compiler optimization
				// UPDATE: Could be wrong, maybe ResponseDef is larger
				Event* evi = r[i].event;
				ev = (int)evi->eventnum;
				r[i].def = evi->getInfo();

				if (!set[ev])
				{
					set[ev] = true;

					if (r[i].response)
					{
						responseLookup[ev] = &r[i];
					}
					else
					{
						responseLookup[ev] = NULL;
					}
				}
			}
		}

		//override out of r, incase our class has no responses

		if (c == this)
		{
			ResponseDef<Class> *r;// redefine r
			r = exResponses;

			for (int i = 0, ev; r[i].event != NULL; i++)
			{
				//in BT it allocates 2 ResponseDefs insde c->responses
				//one contains event and event and response func,
				// the other contains def
				// this could be some sort of compiler optimization
				// UPDATE: Could be wrong, maybe ResponseDef is larger
				Event* evi = r[i].event;
				ev = (int)evi->eventnum;
				r[i].def = evi->getInfo();

				if (!set[ev])
				{
					set[ev] = true;

					if (r[i].response)
					{
						responseLookup[ev] = &r[i];
					}
					else
					{
						responseLookup[ev] = NULL;
					}
				}
			}
		}
	}


	delete[] set;
}
*/
int classcount = 0;
void __fastcall BuildResponseListHook(ClassDef*_this)
{
	if (!strcmp(_this->classname, "Player"))
	{
		_this->BuildExtendedResponseList(reinterpret_cast<ResponseDef<Class>*>(Player::Responses), Player::cerSet.size());
	}
	else if (!strcmp(_this->classname, "ScriptThread"))
	{
		_this->BuildExtendedResponseList(reinterpret_cast<ResponseDef<Class>*>(ScriptThread::Responses), ScriptThread::cerSet.size());
	}
	else
	{
		_this->BuildResponseList_Orignal(_this);
	}
}

void ClassDef::Init()
{
	BuildResponseList_Orignal = reinterpret_cast<void(__thiscall *)(ClassDef*_this)>(BUILDREPONSELIST_ADDRESS);
	addNewKeyEntry = reinterpret_cast<addNewKeyEntryPtr>(ADDNEWKEYENTRY_ADDR);
}
