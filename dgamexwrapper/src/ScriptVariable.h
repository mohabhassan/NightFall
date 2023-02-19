#pragma once


#include "dgamex86.h"
#include "short3.h"
#include "str.h"
#include "Listener.h"
#include "Entity.h"
#include "ScriptException.h"
//#include "safeptr.h"
enum variabletype
{
	VARIABLE_NONE,
	VARIABLE_STRING,
	VARIABLE_INTEGER,
	VARIABLE_FLOAT,
	VARIABLE_CHAR,
	VARIABLE_CONSTSTRING,
	VARIABLE_LISTENER,
	VARIABLE_REF,
	VARIABLE_ARRAY,
	VARIABLE_CONSTARRAY,
	VARIABLE_CONTAINER,
	VARIABLE_SAFECONTAINER,
	VARIABLE_POINTER,
	VARIABLE_VECTOR,
	VARIABLE_MAX
};


static const char *typenames[] =
{
	"none",
	"string",
	"int",
	"float",
	"char",
	"const string",
	"listener",
	"ref",
	"array",
	"const array",
	"array",
	"array",
	"pointer",
	"vector",
	"double"
};


//int HashCode_ScriptVariable(ScriptVariable& key);

//template< typename k = ScriptVariable , typename v = ScriptVariable>
class ScriptVariable;
class Entry_scriptarrayholder;
class con_set_scriptarrayholder;
class con_map_scriptarrayholder;

class ScriptArrayHolder;

class ScriptConstArrayHolder {
public:
	ScriptVariable			*constArrayValue;
	unsigned int			refCount;
	unsigned int			size;
	//unsigned int			dummy;

public:
	ScriptConstArrayHolder();
	~ScriptConstArrayHolder();

	/*void			Archive(Archiver& arc);
	static void		Archive(Archiver& arc, ScriptConstArrayHolder *& constArrayValue);

	ScriptConstArrayHolder(ScriptVariable *pVar, unsigned int size);
	ScriptConstArrayHolder(unsigned int size);
	ScriptConstArrayHolder();
	~ScriptConstArrayHolder();*/
};

class ScriptPointer {
public:
	int /*Container< ScriptVariable * >*/ list[3];

public:
	void			Archive(Archiver& arc);
	static void		Archive(Archiver& arc, ScriptPointer *& pointerValue);

	/*void		Clear();

	void		add(ScriptVariable *var);
	void		setValue(const ScriptVariable& var);
	void remove(ScriptVariable *var)
	{
		list.RemoveObject(var);

		if (!list.NumObjects()) {
			delete this;
		}
	}

	void add(ScriptVariable *var)
	{
		list.AddObject(var);
	}*/
};
class ScriptVariable
{
public:
	short3			key;		// variable name
	unsigned char	type;		// variable type
	union anon393 {
	public:
		char						charValue;
		float						floatValue;
		int							intValue;
		int /*SafePtr<Listener>			**/listenerValue/*[4]*/;
		str							*stringValue;
		float						*vectorValue;

		ScriptVariable				*refValue;

		ScriptArrayHolder			*arrayValue;
		ScriptConstArrayHolder		*constArrayValue;

		int /*Container< SafePtr< Listener > >					**/containerValue/*[3]*/;
		int /*SafePtr< ContainerClass< SafePtr< Listener > > >	**/safeContainerValue/*[4]*/;

		ScriptPointer					*pointerValue;
	} m_data;


	ScriptVariable();
	ScriptVariable(const ScriptVariable& variable);

	~ScriptVariable();

	static void				Init();

	void					ClearInternal();
	static Listener			*(__thiscall *listenerValue)(ScriptVariable*_this);
	static void				(__thiscall *RealClearInternal)(ScriptVariable*_this);
	static void				(__thiscall *setArrayAtRefReal)(ScriptVariable*_this, ScriptVariable*index, ScriptVariable*value);
	static void				(__thiscall *stringValueReal)(const ScriptVariable*_this, str* in);
	static bool				(__thiscall *booleanValueReal)(const ScriptVariable*_this);
	static void				(__thiscall *setListenerValueReal)(const ScriptVariable*_this, Listener* newValue);
	static bool				(__thiscall *operatorEquReal)(const ScriptVariable*_this, const ScriptVariable* var);
	static bool				(__thiscall *operatorEquEquReal)(const ScriptVariable*_this, const ScriptVariable* var);
	static void				(__thiscall *setConstArrayValueReal)(const ScriptVariable*_this, const ScriptVariable* var, unsigned int size);

	void					Clear();


	void					CastBoolean(void);
	//void					CastConstArrayValue(void);
	void					CastEntity(void);
	void					CastFloat(void);
	void					CastInteger(void);
	void					CastString(void);
	bool					CastConstArray(ScriptVariable &var);

	const char				*GetTypeName(void) const;
	variabletype			GetType(void) const;

	qboolean				IsEntity(void);
	qboolean				IsListener(void);
	qboolean				IsNumeric(void);
	qboolean				IsSimpleEntity(void);
	qboolean				IsString(void);
	qboolean				IsVector(void);


	void					SetFalse(void);
	void					SetTrue(void);

	int						intValue(void) const;
	void					setIntValue(int newvalue);
	bool					booleanValue(void) const;
	bool					booleanNumericValue(void);
	char					charValue(void) const;
	void					setCharValue(char newvalue);
	float					floatValue(void) const;
	void					setFloatValue(float newvalue);
	void					setConstStringValue(const_str s);
	const_str				constStringValue() const;
	str						stringValue(void) const;
	void					setStringValue(str newvalue);
	Vector					vectorValue(void) const;
	void					setVectorValue(const Vector &newvector);

	void					setListenerValue(Listener * newvalue);

	void					setConstArrayValue(ScriptVariable *pVar, unsigned int size);

	ScriptArrayHolder *arrayValue() const;

	Entity * entityValue(void);

	void setArrayAtRef(ScriptVariable & index, ScriptVariable & value);

	bool operator==(const ScriptVariable &value);
	bool operator=(const ScriptVariable &value);
	ScriptVariable *operator[](unsigned index) const;
};

/*
int HashCode_ScriptVariable(ScriptVariable& key)
{

	Entity *e;

	switch (key.GetType())
	{
	case VARIABLE_STRING:
	case VARIABLE_CONSTSTRING:
		return HashCode< str >(key.stringValue());

	case VARIABLE_INTEGER:
		return key.m_data.intValue;

	case VARIABLE_LISTENER:
		e = key.entityValue();

		if (checkInheritance(&Entity::ClassInfo, e->classinfo()))
		{
			return e->entnum;
		}

	default:
		ScriptError("Bad hash code value: %s", key.stringValue().c_str());
	}
}
*/


class Entry_scriptarrayholder
{
public:
	ScriptVariable				key;
	ScriptVariable				value;
	//unsigned int				index;//Not used in BT
	Entry_scriptarrayholder		*next;
	/*
public:
	void *operator new(size_t size)
	{

	}
	void operator delete(void *ptr)
	{

	}

	Entry_eventdeflist()
	{

	}
	*/
};

class con_set_scriptarrayholder
{
	Entry_scriptarrayholder		**table;
	unsigned int				tableLength;
	unsigned int				threshold;
	unsigned int				count;
	short unsigned int			tableLengthIndex;
	Entry_scriptarrayholder		*defaultEntry;
public:
	/*
	Entry_scriptarrayholder *findKeyEntry(ScriptVariable key) const
	{
		Entry_scriptarrayholder *entry;

		entry = table[HashCode_ScriptVariable(key) % tableLength];

		for (; entry != NULL; entry = entry->next)
		{
			if (entry->key == key) {
				return entry;
			}
		}

		return NULL;
	}*/
	int getTableLength() const
	{
		return tableLength;
	}

	Entry_scriptarrayholder *getFirstEntry() const
	{
		return defaultEntry;
	}

	Entry_scriptarrayholder		** const getTable()const
	{
		return (Entry_scriptarrayholder		** const)table;
	}
	unsigned int getCount() const
	{
		return count;
	}
};
class con_map_scriptarrayholder
{
	con_set_scriptarrayholder m_con_set;
public:
	const con_set_scriptarrayholder &getConSet() const
	{
		return m_con_set;
	}
};

class ScriptArrayHolder {
public:
	con_map_scriptarrayholder /*con_map< ScriptVariable, ScriptVariable > */arrayValue;
	unsigned int	refCount;

public:
	/*void			Archive(Archiver& arc);
	static void		Archive(Archiver& arc, ScriptArrayHolder *& arrayValue);*/
};