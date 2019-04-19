#include "Event.h"

#define LASTEVENT_ADDR 0x31276F70
#define TOTALEVENTS_ADDR 0x31276ED8
#define EVENTDEFLIST_ADDR 0x31276C80
#define ADDLISTENER_ADDR 0x3113CCE0

static eventInfo_t **lastEvent = NULL;
int *Event::totalevents = NULL;
con_map< Event *, EventDef > * Event::eventDefList = NULL;
void(__thiscall *Event::AddListener_Real)(Event* _this, Listener *listener);

Event::Event()
{
	fromScript = false;
	eventnum = 0;
	data = NULL;
	dataSize = 0;
}

Event::Event(const char * command, int flags, const char * formatspec, const char * argument_names, const char * documentation, uchar type)
{
	eventInfo_t *evi = (eventInfo_t *)MemoryMalloc(sizeof(eventInfo_t)); // de alloced by mohaa
	memset(evi, 0, sizeof(eventInfo_t));
	evi->ev = this;
	evi->command = command;
	evi->flags = flags;
	evi->formatspec = formatspec;
	evi->argument_names = argument_names;
	evi->documentation = documentation;
	evi->type = type;

	evi->prev = *lastEvent;

	*lastEvent = evi;

	fromScript = false;
	dataSize = 0;
	data = NULL;
	eventnum = 0;
}


Event::~Event()
{
	Clear();
}

/*
=======================
Clear
=======================
*/
void Event::Clear(void)
{
	if (data)
	{
		delete[] data;

		data = NULL;
		dataSize = 0;
	}
}

/*
=======================
AddEntity
=======================
*/
void Event::AddEntity(Entity *ent)
{
	AddListener((Listener*)ent);
}

/*
=======================
AddFloat
=======================
*/
void Event::AddFloat(float number)
{
	ScriptVariable& variable = GetValue();
	variable.setFloatValue(number);
}

/*
=======================
AddInteger
=======================
*/
void Event::AddInteger(int number)
{
	ScriptVariable& variable = GetValue();
	variable.setIntValue(number);
}

/*
=======================
AddListener
=======================
*/
void Event::AddListener(Listener * listener)
{
	AddListener_Real(this, listener);
}

/*
=======================
AddNil
=======================
*/
void Event::AddNil(void)
{
	ScriptVariable& variable = GetValue();
	variable.Clear();
}

#ifndef NO_SCRIPTENGINE

/*
=======================
AddConstString
=======================
*/
void Event::AddConstString(const_str string)
{
	ScriptVariable& variable = GetValue();
	variable.setConstStringValue(string);
}

#endif

/*
=======================
AddString
=======================
*/
void Event::AddString(str string)
{
	ScriptVariable& variable = GetValue();
	variable.setStringValue(string);
}

/*
=======================
AddToken
=======================
*/
void Event::AddToken(str token)
{
	ScriptVariable& variable = GetValue();
	variable.setStringValue(token);
}

/*
=======================
AddTokens
=======================
*/
void Event::AddTokens(int argc, const char **argv)
{
	for (int i = 0; i < argc; i++)
	{
		AddToken(argv[i]);
	}
}

/*
=======================
AddValue
=======================
*/
void Event::AddValue(const ScriptVariable &value)
{
	ScriptVariable& variable = GetValue();
	variable = value;
}

/*
=======================
AddVector
=======================
*/
void Event::AddVector(const Vector& vector)
{
	ScriptVariable& variable = GetValue();
	variable.setVectorValue(vector);
}

/*
=======================
NumArgs
=======================
*/
int Event::NumArgs()
{
	return dataSize;
}

bool Event::GetBoolean(int pos)
{
	ScriptVariable& variable = GetValue(pos);

	return variable.booleanNumericValue();
}

int Event::GetConstString(int pos)
{
	return 0;//FIXME
}

float Event::GetFloat(int pos)
{
	ScriptVariable& variable = GetValue(pos);

	return variable.floatValue();
}

int Event::GetInteger(int pos)
{
	ScriptVariable& variable = GetValue(pos);

	return variable.intValue();
}

str Event::GetString(int pos)
{
	ScriptVariable& variable = GetValue(pos);

	return variable.stringValue();
}

str Event::GetToken(int pos)
{
	ScriptVariable& variable = GetValue(pos);
	return variable.stringValue();
}

Entity *Event::GetEntity(int pos)
{
	ScriptVariable& variable = GetValue(pos);
	return variable.entityValue();
}
/*
=======================
CheckPos
=======================
*/
void Event::CheckPos(int pos)
{
	if (pos > NumArgs()) {
		throw NULL;//ScriptError("Index %d out of range.", pos);FIXME
	}
}

/*
=======================
GetValue
=======================
Index starts at 1
*/
ScriptVariable& Event::GetValue(int pos)
{
	if (pos < 0)
	{
		pos = NumArgs() + pos + 1;
	}

	CheckPos(pos);
	return data[pos - 1];
}

//static ScriptVariable m_null;

/*
=======================
GetValue
=======================
*/
ScriptVariable& Event::GetValue(void)
{
	ScriptVariable *tmp;
	if (fromScript)
	{
		return *data;
	}

	if (dataSize % 3 == 0)
	{
		tmp = data;
		data = (ScriptVariable*)MemoryMalloc(sizeof(ScriptVariable) * (dataSize + 1));
		new (data) ScriptVariable();
		if (tmp != NULL)
		{
			for (int i = 0; i < dataSize; i++) {
				data[i] = tmp[i];
			}

			delete[] tmp;
		}
	}

	dataSize++;

	return data[dataSize - 1];
}


Vector Event::GetVector(int pos)
{
	ScriptVariable& variable = GetValue(pos);

	return variable.vectorValue();
}

int Event::NumEventCommands()
{
	return *totalevents;
}

template<>
int HashCode< Event * >(Event * const& key)
{
	// can't use key->eventnum because eventnum will be assigned from con_set
	return (int)key;
}

/*
=======================
getInfo
=======================
*/
EventDef *Event::getInfo()
{
	sizeof(con_map< Event *, EventDef >);
	return &((*eventDefList)[this]);
}

void Event::Init()
{
	lastEvent = reinterpret_cast<eventInfo_t**>(LASTEVENT_ADDR);
	totalevents = reinterpret_cast<int*>(TOTALEVENTS_ADDR);
	eventDefList = reinterpret_cast<con_map< Event *, EventDef > *>(EVENTDEFLIST_ADDR);
	AddListener_Real = reinterpret_cast<void(__thiscall *)(Event*_this, Listener* listener)>(ADDLISTENER_ADDR);
}
