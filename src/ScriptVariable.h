#pragma once


#include "gamex86.h"
#include "short3.h"
#include "str.h"
#include "Listener.h"
#include "Entity.h"
#include "safeptr.h"
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

		void /*ScriptArrayHolder*/			*arrayValue;
		void /*ScriptConstArrayHolder*/		*constArrayValue;

		void /*Container< SafePtr< Listener > >*/					*containerValue;
		void /*SafePtr< ContainerClass< SafePtr< Listener > > >*/	*safeContainerValue;

		void /*ScriptPointer*/								*pointerValue;
	} m_data;


	ScriptVariable();
	ScriptVariable(const ScriptVariable& variable);

	~ScriptVariable();

	static void				Init();

	static void				( __thiscall *ClearInternal)(ScriptVariable*_this);
	static Listener			*( __thiscall *listenerValue)(ScriptVariable*_this);
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

};
