#pragma once
#include "dgamex86.h"
#include <vector>
#include <string>
class CustomCvar
{
	cvar_t *cvar;
	std::string name;
	std::string defaultValue;
	int flags;

public:
	CustomCvar(const std::string sName, const std::string sVal, const int flags);
	~CustomCvar();


	char * GetStringValue();
	int GetIntValue();
	float GetFloatValue();

	void SetValue(std::string v, bool silent = false);

};

