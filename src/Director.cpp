#include "Director.h"


Entry_index_director		***DirectorClass::StringDict_reverseTable;
DirectorClass *Director;

DirectorClass::DirectorClass()
{
}


DirectorClass::~DirectorClass()
{
}

str & DirectorClass::GetString(const_str s)
{
	str & ret2 = (*StringDict_reverseTable)[s]->key;
	return ret2;
}

void DirectorClass::Init()
{
	StringDict_reverseTable = reinterpret_cast<Entry_index_director ***>(STRINGDICT_ADDR);
	Director = reinterpret_cast<DirectorClass *>(DIRECTOR_ADDR);
}
