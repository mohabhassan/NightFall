#pragma once


#include "dgamex86.h"
#include "short3.h"
#include "str.h"
#include "Listener.h"
#include "Entity.h"
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
class ScriptVariable;
class ScriptArrayHolder {
public:
	int /*con_map< ScriptVariable, ScriptVariable > */arrayValue[8];
	unsigned int	refCount;

public:
	/*void			Archive(Archiver& arc);
	static void		Archive(Archiver& arc, ScriptArrayHolder *& arrayValue);*/
};

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
	static bool				(__thiscall *ScriptVariable::operatorEquReal)(const ScriptVariable*_this, const ScriptVariable* var);
	static bool				(__thiscall *ScriptVariable::operatorEquEquReal)(const ScriptVariable*_this, const ScriptVariable* var);

	void					Clear();


	void					CastBoolean(void);
	//void					CastConstArrayValue(void);
	void					CastEntity(void);
	void					CastFloat(void);
	void					CastInteger(void);
	void					CastString(void);


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

	Entity * entityValue(void);

	void setArrayAtRef(ScriptVariable & index, ScriptVariable & value);

	bool operator==(const ScriptVariable &value);
	bool operator=(const ScriptVariable &value);
	ScriptVariable *operator[](unsigned index) const;
};
