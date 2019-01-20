#include "Director.h"

#define STRINGDICT_ADDR 0x3125B3C4

Entry_index< str, str >		***Director::StringDict_reverseTable;

Director::Director()
{
}


Director::~Director()
{
}

str & Director::GetString(const_str s)
{
	sizeof(Entry_index< str, str >);
	str & ret2 = (*StringDict_reverseTable)[s]->key;
	return ret2;
}

void Director::Init()
{
	StringDict_reverseTable = reinterpret_cast<Entry_index< str, str > ***>(STRINGDICT_ADDR);
}
