#include "ScriptVariable.h"



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


void ScriptVariable::ClearInternal()
{
	switch (GetType())
	{
	case VARIABLE_STRING:
		if (m_data.stringValue)
		{
			delete m_data.stringValue;
			m_data.stringValue = NULL;
		}

		break;

	case VARIABLE_ARRAY:
		/*if (m_data.arrayValue->refCount) //FIXME
		{
			m_data.arrayValue->refCount--;
		}
		else
		{
			delete m_data.arrayValue;
		}*/

		m_data.arrayValue = NULL;
		break;

	case VARIABLE_CONSTARRAY:
		/*if (m_data.constArrayValue->refCount) //FIXME
		{
			m_data.constArrayValue->refCount--;
		}
		else
		{
			delete m_data.constArrayValue;
		}*/

		m_data.constArrayValue = NULL;
		break;

	case VARIABLE_LISTENER:
	case VARIABLE_SAFECONTAINER:
		if (m_data.listenerValue)
		{
			delete m_data.listenerValue;
			m_data.listenerValue = NULL;
		}

		break;

	case VARIABLE_POINTER:
		//m_data.pointerValue->remove(this); //FIXME
		m_data.pointerValue = NULL;
		break;

	case VARIABLE_VECTOR:
		delete[] m_data.vectorValue;
		m_data.vectorValue = NULL;
		break;

	default:
		break;
	}
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
		//ScriptError("Cannot cast '%s' to int", typenames[type]);//FIXME
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
		return 0;
	}
}
void ScriptVariable::setFloatValue(float newvalue)
{
	ClearInternal();
	type = VARIABLE_FLOAT;
	m_data.floatValue = newvalue;
}

str ScriptVariable::stringValue(void) const
{
	str string;

	switch (GetType())
	{
	case VARIABLE_NONE:
		return "NIL";

	case VARIABLE_CONSTSTRING:
		return str("CONSTSTRING FIXME");


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
	
	m_data.vectorValue = (float*)gi.Malloc(sizeof(float) * 3);
	newvector.copyTo(m_data.vectorValue);
}