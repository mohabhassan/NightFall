#pragma once


#include "gamex86.h"
#include "short3.h"
#include "str.h"
#include "Listener.h"
#include "Entity.h"
#include "safeptr.h"
#include "con_set.h"
#include "Container.h"
#include "ContainerClass.h"
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
	con_map< ScriptVariable, ScriptVariable > arrayValue;
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
	Container< ScriptVariable * > list;

public:
	void			Archive(Archiver& arc);
	static void		Archive(Archiver& arc, ScriptPointer *& pointerValue);

	/*void		Clear();

	void		add(ScriptVariable *var);
	void		setValue(const ScriptVariable& var);*/
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
	}
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
		SafePtr<Listener>			*listenerValue;
		str							*stringValue;
		float						*vectorValue;

		ScriptVariable				*refValue;

		ScriptArrayHolder			*arrayValue;
		ScriptConstArrayHolder		*constArrayValue;

		Container< SafePtr< Listener > >					*containerValue;
		SafePtr< ContainerClass< SafePtr< Listener > > >	*safeContainerValue;

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
	str						stringValue(void) const;
	void					setStringValue(str newvalue);
	Vector					vectorValue(void) const;
	void					setVectorValue(const Vector &newvector);

	void					setListenerValue(Listener * newvalue);

	Entity * entityValue(void);

	void setArrayAtRef(ScriptVariable & index, ScriptVariable & value);

	bool operator==(const ScriptVariable &value);
	bool operator=(const ScriptVariable &value);
};
