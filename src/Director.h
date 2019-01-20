#pragma once
#include "gamex86.h"
#include "con_set.h"
#include "con_arrayset.h"
#include "str.h";
class Director
{
	static	Entry_index< str, str >		***StringDict_reverseTable;		// const strings (improve performance)
public:
	Director();
	~Director();


	static str& GetString(const_str s);
	static void Init();
};

