#include "CustomCvar.h"



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
