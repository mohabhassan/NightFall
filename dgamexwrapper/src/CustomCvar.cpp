#include "CustomCvar.h"
#include "nf_misc.h"


CustomCvar::CustomCvar(const std::string sName, const std::string sVal, const int iFlags)
	: name(sName), defaultValue(sVal), flags(iFlags)
{
	cvar = gi->Cvar_Get(name.c_str(), defaultValue.c_str(), flags);
}

CustomCvar::~CustomCvar()
{
}


char * CustomCvar::GetStringValue()
{
	return cvar->string;
}

int CustomCvar::GetIntValue()
{
	return cvar->integer;
}

float CustomCvar::GetFloatValue()
{
	return cvar->value;
}

void CustomCvar::SetValue(string v, bool silent)
{
	cvar_t* developer = gi->Cvar_Get("developer", "0", 0);
	char* developer_value = developer->string;
	if (silent) // set developer to zero
	{
		developer->modified = qtrue;
		developer->modificationCount++;
		//gi->Free(developer->string);
		developer->string = CopyString("0");
		developer->value = 0;
		developer->integer = 0;
	}
	gi->Cvar_Set(name.c_str(), v.c_str());
	if (silent) // set developer to old value
	{
		developer->modified = qtrue;
		developer->modificationCount++;
		gi->Free(developer->string);
		developer->string = developer_value;
		developer->value = atof(developer->string);
		developer->integer = atoi(developer->string);
	}
}
