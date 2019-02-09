#pragma once
#include "gamex86.h"
#include "Listener.h"
#include "con_set.h"
#include "con_arrayset.h"
#include "str.h";
class DirectorClass : public Listener //ScriptMaster Director; and ScriptMaster inherents from Listener
{
	static	Entry_index< str, str >		***StringDict_reverseTable;		// const strings (improve performance)
public:
	DirectorClass();
	~DirectorClass();


	static str& GetString(const_str s);
	static void Init();
};

