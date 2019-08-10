#pragma once
#include "str.h"
class ScriptException
{
public:
	str		string;
	int		bAbort;
	int		bIsForAnim;

private:
	void CreateException(const char * data);

public:
	ScriptException(str text);
	ScriptException(const char *format, ...);
	ScriptException(char *text);


	//static int next_abort;
	//static int next_bIsForAnim;
};

//TODO: confirm if it works in mohaa and on linux
#define ScriptError throw ScriptException
