#include "ScriptVariable.h"
#include "Director.h"
#include "Class.h"
#include "AddressDefinitions.h"

#include <string>
#include <algorithm>

using std::max;

Listener	*(__thiscall *ScriptVariable::listenerValue)(ScriptVariable*_this);
void		(__thiscall *ScriptVariable::RealClearInternal)(ScriptVariable*_this);
void		(__thiscall *ScriptVariable::setArrayAtRefReal)(ScriptVariable*_this, ScriptVariable*index, ScriptVariable*value);
void		(__thiscall *ScriptVariable::stringValueReal)(const ScriptVariable*_this, str* in);
bool		(__thiscall *ScriptVariable::booleanValueReal)(const ScriptVariable*_this);
void		(__thiscall *ScriptVariable::setListenerValueReal)(const ScriptVariable*_this, Listener* newValue);
bool		(__thiscall *ScriptVariable::operatorEquReal)(const ScriptVariable*_this, const ScriptVariable* var);
bool		(__thiscall *ScriptVariable::operatorEquEquReal)(const ScriptVariable*_this, const ScriptVariable* var);
void		(__thiscall *ScriptVariable::setConstArrayValueReal)(const ScriptVariable*_this, const ScriptVariable* var, unsigned int size);

extern void *__cdecl  MemoryMalloc(int size);
extern void __cdecl  MemoryFree(void * ptr);

//correct sizeof = 8
ScriptVariable::ScriptVariable()
{
	key = 0;
	type = 0;
	m_data.pointerValue = NULL;
}

ScriptVariable::ScriptVariable(const ScriptVariable& variable)
{
	type = 0;
	m_data.pointerValue = NULL;

	*this = variable;
}

ScriptVariable::~ScriptVariable()
{
	ClearInternal();
}

void ScriptVariable::Init()
{
	listenerValue = reinterpret_cast<Listener*(__thiscall*)(ScriptVariable*__this)>((int)LISTENERVALUE_ADDR);
	RealClearInternal = reinterpret_cast<void(__thiscall*)(ScriptVariable*__this)>((int)CLEARINTERNAL_ADDR);
	setArrayAtRefReal = reinterpret_cast<void(__thiscall*)(ScriptVariable*_this, ScriptVariable*index, ScriptVariable*value)>((int)SETARRAYATREF_ADDR);
	stringValueReal = reinterpret_cast<void(__thiscall*)(const ScriptVariable*_this, str*in)>((int)STRINGVALUE_ADDR);
	booleanValueReal = reinterpret_cast<bool(__thiscall*)(const ScriptVariable*_this)>((int)BOOLEANVALUE_ADDR);
	setListenerValueReal = reinterpret_cast<void(__thiscall*)(const ScriptVariable*_this, Listener*)>((int)SETLISENERVALUEVALUE_ADDR);
	operatorEquReal = reinterpret_cast<bool(__thiscall*)(const ScriptVariable*_this, const ScriptVariable*)>((int)OPERATOREQU_ADDR);
	operatorEquEquReal = reinterpret_cast<bool(__thiscall*)(const ScriptVariable*_this, const ScriptVariable*)>((int)OPERATOREQUEQU_ADDR);
	setConstArrayValueReal = reinterpret_cast<void(__thiscall*)(const ScriptVariable*_this, const ScriptVariable*, unsigned int)>((int)SETCONSTARRAYVALUE_ADDR);
}

void ScriptVariable::Clear()
{
	ClearInternal();
	type = 0;
}




void ScriptVariable::CastBoolean(void)
{
	int newvalue = booleanValue();

	ClearInternal();

	type = VARIABLE_INTEGER;
	m_data.intValue = newvalue;
}
//void					CastConstArrayValue(void)
void ScriptVariable::CastEntity(void)
{
	//FIXME
}
void ScriptVariable::CastFloat(void)
{
	setFloatValue(floatValue());
}
void ScriptVariable::CastInteger(void)
{
	setIntValue(intValue());
}
void ScriptVariable::CastString(void)
{
	setStringValue(stringValue());
}

bool ScriptVariable::CastConstArray(ScriptVariable &var)
{
	//only do our stuff if it's a "VARIABLE_ARRAY"
	if (var.GetType() != VARIABLE_ARRAY)
		return false;
	Entry_scriptarrayholder		** const table = var.arrayValue()->arrayValue.getConSet().getTable();
	Entry_scriptarrayholder *entry;
	if (var.arrayValue()->arrayValue.getConSet().getCount() == 0)
	{
		return false;
	}

	int max_index = 0;
	int min_index = std::numeric_limits<int>::max();
	//for now, we can loop on hash table, it might have empty/null entries, but that's ok.
	for (size_t i = 0; i < var.arrayValue()->arrayValue.getConSet().getTableLength(); i++)
	{
		for (entry = table[i]; entry != NULL; entry = entry->next)
		{
			ScriptVariable &key = entry->key;
			variabletype type = key.GetType();
			if (type == VARIABLE_STRING || type == VARIABLE_CONSTSTRING)
			{
				str val = key.stringValue();
				try
				{
					int i = std::stoi(val.c_str());
					max_index = std::max(max_index, i);
					min_index = std::min(min_index, i);
				}
				catch (const std::exception&)
				{
					return false;
				}
			}
			else if(type == VARIABLE_INTEGER)
			{
				int i = key.intValue();
				max_index = std::max(max_index, i);
				min_index = std::min(min_index, i);
			}
			else
			{
				return false;
			}
		}
	}

	int newVarSize = max_index - min_index + 1;
	ScriptVariable *pVar = new ScriptVariable[newVarSize];
	//for now, we can loop on hash table, it might have empty/null entries, but that's ok.
	for (size_t i = 0; i < var.arrayValue()->arrayValue.getConSet().getTableLength(); i++)
	{
		for (entry = table[i]; entry != NULL; entry = entry->next)
		{
			ScriptVariable &key = entry->key;
			variabletype type = key.GetType();
			if (type == VARIABLE_STRING || type == VARIABLE_CONSTSTRING)
			{
				str val = key.stringValue();
				int i = std::stoi(val.c_str()) - min_index;
				pVar[i] = entry->value;
			}
			else if (type == VARIABLE_INTEGER)
			{
				int i = key.intValue() - min_index;
				pVar[i] = entry->value;
			}
		}
	}
	setConstArrayValue(pVar, newVarSize);
	delete[] pVar;
	return true;
	
}


void ScriptVariable::ClearInternal()
{
	//todo: must take care of script variables that are auto-deallocated after dgamex86mohbt.dll is unloaded.
	//prolly should make the dynamically allocated
	//update: apparently they are no longer there ?
	if (type != VARIABLE_NONE)
	{
		ScriptVariable*_this = this;
		RealClearInternal(this);
	}
	return;
	///////////////////////////////////////////////
	/*
	switch (GetType())
	{
	case VARIABLE_STRING:
		if (m_data.stringValue)
		{
			delete m_data.stringValue;
		}
		m_data.stringValue = NULL;

		break;

	case VARIABLE_ARRAY:
		if (m_data.arrayValue->refCount)
		{
			m_data.arrayValue->refCount--;
		}
		else
		{
			delete m_data.arrayValue;
		}

		m_data.arrayValue = NULL;
		break;

	case VARIABLE_CONSTARRAY:
		if (m_data.constArrayValue->refCount)
		{
			m_data.constArrayValue->refCount--;
		}
		else
		{
			delete m_data.constArrayValue;
		}

		m_data.constArrayValue = NULL;
		break;

	case VARIABLE_LISTENER:
	case VARIABLE_SAFECONTAINER:
		if (m_data.listenerValue)
		{
			delete m_data.listenerValue;
		}
		m_data.listenerValue = NULL;

		break;

	case VARIABLE_POINTER:
		m_data.pointerValue->remove(this);
		m_data.pointerValue = NULL;
		break;

	case VARIABLE_VECTOR:
		delete[] m_data.vectorValue;
		m_data.vectorValue = NULL;
		break;

	default:
		break;
	}
	*/
}

const char *ScriptVariable::GetTypeName() const
{
	return typenames[type];
}

variabletype ScriptVariable::GetType() const
{
	return (variabletype)type;
}

qboolean ScriptVariable::IsEntity(void)
{
	return type == VARIABLE_LISTENER; //FIXME
}
qboolean ScriptVariable::IsListener(void)
{
	return type == VARIABLE_LISTENER;
}
qboolean ScriptVariable::IsNumeric(void)
{
	return type == VARIABLE_INTEGER || type == VARIABLE_FLOAT;
}
qboolean ScriptVariable::IsSimpleEntity(void)
{
	return type == VARIABLE_LISTENER; //FIXME
}
qboolean ScriptVariable::IsString(void)
{
	return (type == VARIABLE_STRING || type == VARIABLE_CONSTSTRING);
}
qboolean ScriptVariable::IsVector(void)
{
	return type == VARIABLE_VECTOR;
}


void ScriptVariable::SetFalse(void)
{
	setIntValue(0);
}
void ScriptVariable::SetTrue(void)
{
	setIntValue(1);
}

bool ScriptVariable::booleanValue(void) const
{
	return booleanValueReal(this);
	/*
	switch (GetType())
	{
	case VARIABLE_NONE:
		return false;

	case VARIABLE_STRING:
		if (m_data.stringValue)
		{
			return m_data.stringValue->length() != 0;
		}

		return false;

	case VARIABLE_INTEGER:
		return m_data.intValue != 0;

	case VARIABLE_FLOAT:
		return fabs(m_data.floatValue) >= 0.00009999999747378752;

	case VARIABLE_CONSTSTRING:
		return m_data.intValue != STRING_EMPTY;

	case VARIABLE_LISTENER:
		return (*reinterpret_cast<int*>(m_data.listenerValue)) != NULL;

	default:
		return true;
	}
	}*/
}

bool ScriptVariable::booleanNumericValue(void)
{
	str value;

	switch (GetType())
	{
	case VARIABLE_STRING:
	case VARIABLE_CONSTSTRING:
		value = stringValue();

		return atoi(value.c_str()) ? true : false;

	case VARIABLE_INTEGER:
		return m_data.intValue != 0;

	case VARIABLE_FLOAT:
		return fabs(m_data.floatValue) >= 0.00009999999747378752;

	case VARIABLE_LISTENER:
		return false;// (*m_data.listenerValue) != NULL;FIXME

	default:
		return false;//ScriptError("Cannot cast '%s' to boolean numeric", GetTypeName());FIXME
	}

	return true;
}

char ScriptVariable::charValue(void) const
{
	str value;

	switch (GetType())
	{
	case VARIABLE_CHAR:
		return m_data.charValue;

	case VARIABLE_CONSTSTRING:
	case VARIABLE_STRING:
		value = stringValue();

		if (value.length() != 1)
		{
			//ScriptError("Cannot cast string not of length 1 to char"); // FIXME
			break;//FIXME
		}

		return *value;

	default:
		//ScriptError("Cannot cast '%s' to char", GetTypeName()); // FIXME
		break;
	}

	return 0;
}

void ScriptVariable::setCharValue(char newvalue)
{
	ClearInternal();

	type = VARIABLE_CHAR;
	m_data.charValue = newvalue;
}

int ScriptVariable::intValue(void) const
{
	str string;
	int val;

	switch (type)
	{
	case VARIABLE_INTEGER:
		return m_data.intValue;

	case VARIABLE_FLOAT:
		return (int)m_data.floatValue;

	case VARIABLE_STRING:
	case VARIABLE_CONSTSTRING:
		string = stringValue();
		val = atoi(string);

		return val;

	default:
		ScriptError("Cannot cast '%s' to int", typenames[type]);
		return 0;
	}
}
void ScriptVariable::setIntValue(int newvalue)
{
	ClearInternal();
	type = VARIABLE_INTEGER;
	m_data.intValue = newvalue;
}

float ScriptVariable::floatValue(void) const
{
	const char *string;
	float val;

	switch (type)
	{
	case VARIABLE_FLOAT:
		return m_data.floatValue;

	case VARIABLE_INTEGER:
		return (float)m_data.intValue;

		/* Transform the string into an integer if possible */
	case VARIABLE_STRING:
	case VARIABLE_CONSTSTRING:
		string = stringValue();
		val = atof((const char *)string);

		return val;

	default:
		//ScriptError("Cannot cast '%s' to float", typenames[type]);//FIXME
		throw 0;
		return 0;
	}
}
void ScriptVariable::setFloatValue(float newvalue)
{
	ClearInternal();
	type = VARIABLE_FLOAT;
	m_data.floatValue = newvalue;
}

void ScriptVariable::setConstStringValue(const_str s)
{
	ClearInternal();
	type = VARIABLE_CONSTSTRING;
	m_data.intValue = s;
}

const_str ScriptVariable::constStringValue() const
{
	return m_data.intValue;
}

str ScriptVariable::stringValue(void) const
{
	str string;
	stringValueReal(this, &string);
	return string;
	/////////////////////////////////////////
	switch (GetType())
	{
	case VARIABLE_NONE:
		return "NIL";

	case VARIABLE_CONSTSTRING:
		return DirectorClass::GetString(m_data.intValue);


	case VARIABLE_STRING:
		return *m_data.stringValue;

	case VARIABLE_INTEGER:
		return str(m_data.intValue);

	case VARIABLE_FLOAT:
		return str(m_data.floatValue);

	case VARIABLE_CHAR:
		return str(m_data.charValue);
	case VARIABLE_LISTENER:
		/*if (m_data.listenerValue->Pointer())
		{
#ifndef NO_SCRIPTENGINE
			if (m_data.listenerValue->Pointer()->isSubclassOf(SimpleEntity))
			{
				SimpleEntity *s = (SimpleEntity *)m_data.listenerValue->Pointer();
				return s->targetname;
			}
			else
			{
				string = "class '" + str(m_data.listenerValue->Pointer()->getClassname()) + "'";
				return string;
			}
#else
			string = "class '" + str(m_data.listenerValue->Pointer()->getClassname()) + "'";
			return string;
#endif
		}
		else
		{
			return "NULL";
		}*/
		return str("LISTENER FIXME");
	case VARIABLE_VECTOR:
		return str("( ") + str(m_data.vectorValue[0]) + str(" ") + str(m_data.vectorValue[1]) + str(" ") + str(m_data.vectorValue[2] + str(" )"));

	default:
		//ScriptError("Cannot cast '%s' to string", typenames[GetType()]);//FIXME
		return "ScriptVariable::11stringValue22() default";
		break;
	}

	return "";
}
void ScriptVariable::setStringValue(str newvalue)
{
	str *s;

	ClearInternal();
	type = VARIABLE_STRING;

	
	s = new str(newvalue);

	m_data.stringValue = s;
}

Vector ScriptVariable::vectorValue(void) const
{
	const char *string;
	float x = 0.f, y = 0.f, z = 0.f;

	switch (type)
	{
	case VARIABLE_VECTOR:
		return Vector(m_data.vectorValue);

	case VARIABLE_CONSTSTRING:
	case VARIABLE_STRING:
		string = stringValue();

		if (strcmp(string, "") == 0) {
			//ScriptError("cannot cast empty string to vector");//FIXME
			return vec_zero;//FIXME
		}

		if (*string == '(')
		{
			if (sscanf(string, "(%f %f %f)", &x, &y, &z) != 3)
			{
				if (sscanf(string, "(%f, %f, %f)", &x, &y, &z) != 3) {
					//ScriptError("Couldn't convert string to vector - malformed string '%s'", string);//FIXME
					return vec_zero;//FIXME
				}
			}
		}
		else
		{
			if (sscanf(string, "%f %f %f", &x, &y, &z) != 3)
			{
				if (sscanf(string, "%f, %f, %f", &x, &y, &z) != 3) {
					//ScriptError("Couldn't convert string to vector - malformed string '%s'", string);//FIXME
					return vec_zero;//FIXME
				}
			}
		}

		return Vector(x, y, z);
	case VARIABLE_LISTENER:
	{
		/*if (!m_data.listenerValue->Pointer()) {
			ScriptError("Cannot cast NULL to vector");
		}

		if (!checkInheritance(&SimpleEntity::ClassInfo, m_data.listenerValue->Pointer()->classinfo()))
		{
			ScriptError("Cannot cast '%s' to vector", GetTypeName());
		}

		SimpleEntity *ent = (SimpleEntity *)m_data.listenerValue->Pointer();

		return Vector(ent->origin[0], ent->origin[1], ent->origin[2]);*/
		return vec_zero;//FIXME
	}

	default:
		//ScriptError("Cannot cast '%s' to vector", GetTypeName());//FIXME
		return vec_zero;//FIXME

	}
}

void ScriptVariable::setVectorValue(const Vector &newvector)
{
	ClearInternal();

	type = VARIABLE_VECTOR;
	
	m_data.vectorValue = (float*)MemoryMalloc(sizeof(float) * 3);
	newvector.copyTo(m_data.vectorValue);
}


void ScriptVariable::setListenerValue(Listener *newvalue)
{
	setListenerValueReal(this, newvalue);
	/*
	ClearInternal();

	type = VARIABLE_LISTENER;

	m_data.listenerValue = new SafePtr< Listener >(newvalue);
	*/
}

void ScriptVariable::setConstArrayValue(ScriptVariable * pVar, unsigned int size)
{
	setConstArrayValueReal(this, pVar, size);
}

ScriptArrayHolder * ScriptVariable::arrayValue() const
{
	return m_data.arrayValue;
}


Entity *ScriptVariable::entityValue(void)
{
	return (Entity *)listenerValue(this);
}


void ScriptVariable::setArrayAtRef(ScriptVariable& index, ScriptVariable& value)
{
	setArrayAtRefReal(this, &index, &value);
	return;
	//////////////////////////////////////////////
	/*
	int intValue;
	str string;
	sizeof(ScriptVariable);
	switch (type)
	{
	case VARIABLE_VECTOR:
		intValue = index.intValue();

		if (intValue > 2) {
			gi->Printf("Vector index '%d' out of range", intValue);
			return;
		}

		m_data.vectorValue[intValue] = value.floatValue();
		break;

	case VARIABLE_REF:
		return;

	case VARIABLE_NONE:
		type = VARIABLE_ARRAY;
		sizeof(ScriptArrayHolder);//28

		m_data.arrayValue = new ScriptArrayHolder;

		if (value.GetType() != VARIABLE_NONE)
		{
			m_data.arrayValue->arrayValue[index] = value;
		}

		break;

	case VARIABLE_ARRAY:
		if (value.GetType() == VARIABLE_NONE)
		{
			m_data.arrayValue->arrayValue.remove(index);
		}
		else
		{
			m_data.arrayValue->arrayValue[index] = value;
		}
		break;

	case VARIABLE_STRING:
	case VARIABLE_CONSTSTRING:
		intValue = index.intValue();
		string = stringValue();

		if (intValue >= strlen(string)) {
			gi->Printf("String index '%d' out of range", intValue);
			return;
		}

		string[intValue] = value.charValue();

		setStringValue(string);

		break;

	case VARIABLE_CONSTARRAY:
		intValue = index.intValue();

		if (!intValue || intValue > m_data.constArrayValue->size) {
			gi->Printf("array index %d out of range", intValue);
			return;
		}

		if (value.GetType())
		{
			m_data.constArrayValue->constArrayValue[intValue] = value;
		}
		else {
			m_data.constArrayValue->constArrayValue[intValue].Clear();
		}

		break;

	default:
		gi->Printf("[] applied to invalid type '%s'\n", typenames[GetType()]);
		break;
	}
	}*/
}

static __inline int VectorCompare(const vec3_t v1, const vec3_t v2) {
	if (v1[0] != v2[0] || v1[1] != v2[1] || v1[2] != v2[2]) {
		return 0;
	}
	return 1;
}

bool ScriptVariable::operator==(const ScriptVariable &value)
{
	return operatorEquEquReal(this, &value);
	/*
	int type = GetType();

	switch (type + value.GetType() * VARIABLE_MAX)
	{
	default:		// ( lval )	==	( nil )
					// ( nil )	==	( rval )
		Clear();
		return false;

	case VARIABLE_NONE + VARIABLE_NONE * VARIABLE_MAX: // ( nil ) == ( nil )
		return true;

	case VARIABLE_LISTENER + VARIABLE_LISTENER * VARIABLE_MAX: // ( listener ) == ( listener )
	{
		Class *lval = NULL;
		Class *rval = NULL;

		if (m_data.listenerValue)
		{
			lval = m_data.listenerValue->Pointer();
		}

		if (value.m_data.listenerValue)
		{
			rval = value.m_data.listenerValue->Pointer();
		}

		return lval == rval;
	}

	case VARIABLE_INTEGER + VARIABLE_INTEGER * VARIABLE_MAX: // ( int ) == ( int )
		return m_data.intValue == value.m_data.intValue;

	case VARIABLE_INTEGER + VARIABLE_FLOAT * VARIABLE_MAX: // ( int ) == ( float )
		return m_data.intValue == value.m_data.floatValue;

	case VARIABLE_FLOAT + VARIABLE_FLOAT * VARIABLE_MAX: // ( float ) == ( float )
		return m_data.floatValue == value.m_data.floatValue;

	case VARIABLE_FLOAT + VARIABLE_INTEGER * VARIABLE_MAX: // ( float ) == ( int )
		return m_data.floatValue == value.m_data.intValue;

	case VARIABLE_CONSTSTRING + VARIABLE_CONSTSTRING * VARIABLE_MAX:	// ( const string )		==		( const string )
		return m_data.intValue == value.m_data.intValue;

	case VARIABLE_STRING + VARIABLE_STRING * VARIABLE_MAX:				// ( string )			==		( string )
	case VARIABLE_INTEGER + VARIABLE_STRING * VARIABLE_MAX:				// ( int )				==		( string )
	case VARIABLE_FLOAT + VARIABLE_STRING * VARIABLE_MAX:				// ( float )			==		( string )
	case VARIABLE_CHAR + VARIABLE_STRING * VARIABLE_MAX:				// ( char )				==		( string )
	case VARIABLE_CONSTSTRING + VARIABLE_STRING * VARIABLE_MAX:			// ( const string )		==		( string )
	case VARIABLE_LISTENER + VARIABLE_STRING * VARIABLE_MAX:			// ( listener )			==		( string )
	case VARIABLE_VECTOR + VARIABLE_STRING * VARIABLE_MAX:				// ( vector )			==		( string )
	case VARIABLE_STRING + VARIABLE_CONSTSTRING * VARIABLE_MAX:			// ( string )			==		( const string )
	case VARIABLE_INTEGER + VARIABLE_CONSTSTRING * VARIABLE_MAX:		// ( int )				==		( const string )
	case VARIABLE_FLOAT + VARIABLE_CONSTSTRING * VARIABLE_MAX:			// ( float )			==		( const string )
	case VARIABLE_CHAR + VARIABLE_CONSTSTRING * VARIABLE_MAX:			// ( char )				==		( const string )
	case VARIABLE_LISTENER + VARIABLE_CONSTSTRING * VARIABLE_MAX:		// ( listener )			==		( const string )
	case VARIABLE_VECTOR + VARIABLE_CONSTSTRING * VARIABLE_MAX:			// ( vector )			==		( const string )
	case VARIABLE_STRING + VARIABLE_INTEGER * VARIABLE_MAX:				// ( string )			==		( int )
	case VARIABLE_CONSTSTRING + VARIABLE_INTEGER * VARIABLE_MAX:		// ( const string )		==		( int )
	case VARIABLE_STRING + VARIABLE_FLOAT * VARIABLE_MAX:				// ( string )			==		( float )
	case VARIABLE_CONSTSTRING + VARIABLE_FLOAT * VARIABLE_MAX:			// ( const string )		==		( float )
	case VARIABLE_STRING + VARIABLE_CHAR * VARIABLE_MAX:				// ( string )			==		( char )
	case VARIABLE_CONSTSTRING + VARIABLE_CHAR * VARIABLE_MAX:			// ( const string )		==		( char )
	case VARIABLE_STRING + VARIABLE_LISTENER * VARIABLE_MAX:			// ( string )			==		( listener )
	case VARIABLE_CONSTSTRING + VARIABLE_LISTENER * VARIABLE_MAX:		// ( const string )		==		( listener )
	case VARIABLE_STRING + VARIABLE_VECTOR * VARIABLE_MAX:				// ( string )			==		( vector )
	case VARIABLE_CONSTSTRING + VARIABLE_VECTOR * VARIABLE_MAX:			// ( const string )		==		( vector )
	{
		str lval = stringValue();
		str rval = value.stringValue();

		return (!lval.length() && !rval.length()) || (lval == rval);
	}

	case VARIABLE_VECTOR + VARIABLE_VECTOR * VARIABLE_MAX: // ( vector ) == ( vector )
		return VectorCompare(m_data.vectorValue, value.m_data.vectorValue) ? true : false;
	}
	}*/
}

/*
template<>
int HashCode< ScriptVariable >(const ScriptVariable& key)
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
		e = (Entity *)key.listenerValue((ScriptVariable*)&key);

		if (e->checkEntity())
		{
			return e->entnum;
		}


	default:
		gi->Printf("Bad hash code value: %s", key.stringValue().c_str());
	}
}
*/


ScriptConstArrayHolder::ScriptConstArrayHolder()
{
	refCount = 0;
	size = 0;
	constArrayValue = NULL;
}

ScriptConstArrayHolder::~ScriptConstArrayHolder()
{
	if (constArrayValue)
	{
		delete[](constArrayValue + 1);
	}
}


bool ScriptVariable::operator=(const ScriptVariable &variable)
{
	return operatorEquReal(this, &variable);
	sizeof(ScriptConstArrayHolder);
	/*
	ClearInternal();

	type = variable.GetType();

	switch (type)
	{
	case VARIABLE_NONE:
		return false;

	case VARIABLE_CONSTSTRING:
		m_data.intValue = variable.m_data.intValue;
		return true;

	case VARIABLE_STRING:
		m_data.stringValue = new str(variable.stringValue());
		return true;

	case VARIABLE_FLOAT:
		m_data.floatValue = variable.m_data.floatValue;
		return true;

	case VARIABLE_CHAR:
		m_data.charValue = variable.m_data.charValue;
		return true;

	case VARIABLE_INTEGER:
		m_data.intValue = variable.m_data.intValue;
		return true;

	case VARIABLE_LISTENER:
		sizeof(SafePtr< Listener >);//16
		m_data.listenerValue = new SafePtr< Listener >(*variable.m_data.listenerValue);
		return true;
	case VARIABLE_REF:
		m_data.refValue = variable.m_data.refValue;
		return true;
	case VARIABLE_ARRAY:
		m_data.arrayValue = variable.m_data.arrayValue;
		m_data.arrayValue->refCount++;
		return true;

	case VARIABLE_CONSTARRAY:
		m_data.constArrayValue = variable.m_data.constArrayValue;
		m_data.constArrayValue->refCount++;
		return true;

	case VARIABLE_CONTAINER:
		//m_data.containerValue = new Container< SafePtr< Listener > >(*variable.m_data.containerValue);
		m_data.containerValue = variable.m_data.containerValue;// BT
		return true;

	case VARIABLE_SAFECONTAINER:
		sizeof(SafePtr< ConList >);//16
		m_data.safeContainerValue = new SafePtr< ConList >(*variable.m_data.safeContainerValue);
		return true;

	case VARIABLE_POINTER:
		m_data.pointerValue = variable.m_data.pointerValue;
		m_data.pointerValue->add(this);
		return true;

	case VARIABLE_VECTOR:
		m_data.vectorValue = new float[3];
		m_data.vectorValue[0] = variable.m_data.vectorValue[0];
		m_data.vectorValue[2] = variable.m_data.vectorValue[1];
		m_data.vectorValue[2] = variable.m_data.vectorValue[2];
		return true;
	}

	return true;
	*/
}

ScriptVariable *ScriptVariable::operator[](unsigned index) const
{
	return &m_data.constArrayValue->constArrayValue[index];
}
