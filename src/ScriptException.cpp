#include "ScriptException.h"
#include <stdarg.h>

void ScriptException::CreateException(const char *data)
{
	string = data;

	bAbort = 0;
	bIsForAnim = 0;
}


ScriptException::ScriptException(str text)
{
	CreateException(text.c_str());
}

ScriptException::ScriptException(const char *format, ...)
{
	va_list va;
	char data[4100];

	va_start(va, format);
	vsprintf(data, format, va);
	va_end(va);

	CreateException(data);
}

ScriptException::ScriptException(char *text)
{
	CreateException(text);
}