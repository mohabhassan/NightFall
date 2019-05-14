#pragma once
#include "gamex86.h"
#include "Listener.h"
#include "str.h";
class Entry_index_director
{
public:
	str		key;
};

class DirectorClass : public Listener //ScriptMaster Director; and ScriptMaster inherents from Listener
{
	static	Entry_index_director		***StringDict_reverseTable;		// const strings (improve performance)
public:
	DirectorClass();
	~DirectorClass();


	static str& GetString(const_str s);
	static void Init();
};

