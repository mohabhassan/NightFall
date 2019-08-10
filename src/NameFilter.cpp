#include "NameFilter.h"
#include <fstream>


vector<NameEntry> NameFilter::NameEntries;

vector<ProtectedNameEntry> NameFilter::ProtectedNameEntries;

NameEntry::NameEntry(string name_str, bool bAny)
{
	SetName(name_str, bAny);
}

bool NameEntry::NameMatches(string name_str) const
{
	if (AnyOccurence())
	{
		return stristr(name_str.c_str(), name.c_str()) != NULL;
	}
	else
	{
		return stricmp(name_str.c_str(), name.c_str()) == 0;
	}
}

bool NameEntry::NameMatchesExact(string name_str) const
{
	return stricmp(name.c_str(), name_str.c_str()) == 0;
}

string NameEntry::GetString() const
{
	return name + (AnyOccurence() ? " ~any" : "");
}

bool NameEntry::AnyOccurence() const
{
	return any;
}

void NameEntry::SetName(string name_str, bool bAny)
{
	any = bAny;
	name = name_str;
}



ProtectedNameEntry::ProtectedNameEntry(string name_str, string pw_str)
{
	SetName(name_str, pw_str);
}

bool ProtectedNameEntry::NameMatches(string name_str) const
{
	return stricmp(name.c_str(), name_str.c_str()) == 0;
}

bool ProtectedNameEntry::PasswordMatches(string pw_str) const
{
	return pw_str == password;
}

string ProtectedNameEntry::GetString() const
{
	return "name=" + name + " password=" + password;
}

void ProtectedNameEntry::SetName(string name_str, string pw_str)
{
	name = name_str;
	password = pw_str;
}


size_t NameFilter::FindName(string name_str, bool exact = false)
{
	for (size_t i = 0; i < NameEntries.size(); i++)
	{
		const NameEntry &e = NameEntries[i];
		if (exact)
		{
			if (e.NameMatchesExact(name_str))
			{
				return i;
			}
		}
		else
		{
			if (e.NameMatches(name_str))
			{
				return i;
			}
		}
	}
	return defaultNameIndex;
}

size_t NameFilter::FindProtectedName(string name_str)
{
	for (size_t i = 0; i < ProtectedNameEntries.size(); i++)
	{
		const ProtectedNameEntry &e = ProtectedNameEntries[i];

		if (e.NameMatches(name_str))
		{
			return i;
		}
	}
	return defaultNameIndex;
}

NameFilter::NameFilter()
{
}


NameFilter::~NameFilter()
{
}

//returns true if name added
//returns false if name already exists
//returns false if name already exists
bool NameFilter::AddName(string name_str)
{
	static string anyStr = " ~any";
	bool any = false;
	if (name_str.size() > anyStr.size())
	{
		if (name_str.compare(name_str.size() - anyStr.size() - 1, anyStr.size(), anyStr))
		{
			name_str.erase(name_str.size() - anyStr.size());
			any = true;
		}
	}
	if (name_str.empty())
	{
		name_str = anyStr;
		any = false;
	}
	size_t index = FindName(name_str, true);

	if (index != defaultNameIndex)
	{
		return false;
	}
	else
	{
		NameEntries.emplace_back(name_str, any);
		return true;
	}
}

bool NameFilter::AddProtectedName(string name_str, string pasword)
{
	size_t index = FindProtectedName(name_str);

	if (index != defaultNameIndex)
	{
		return false;
	}
	else
	{
		ProtectedNameEntries.emplace_back(name_str, pasword);
		return true;
	}
}

bool NameFilter::RemoveName(string name_str)
{
	size_t index = FindName(name_str, true);

	if (index == defaultNameIndex)
	{
		return false;
	}
	else
	{
		NameEntries.erase(NameEntries.begin() + index);
		return true;
	}

}

bool NameFilter::RemoveProtectedName(string name_str)
{
	size_t index = FindProtectedName(name_str);

	if (index == defaultNameIndex)
	{
		return false;
	}
	else
	{
		ProtectedNameEntries.erase(ProtectedNameEntries.begin() + index);
		return true;
	}
}

bool NameFilter::CanConnect(string name_str)
{
	size_t index = FindName(name_str, false);

	if (index == defaultNameIndex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool NameFilter::CanConnectProtected(string name_str, string password)
{
	size_t index = FindProtectedName(name_str);

	if (index == defaultNameIndex)
	{
		return true;
	}
	else
	{
		return ProtectedNameEntries[index].PasswordMatches(password);
	}
}

string NameFilter::GetNamesInPage(int page_num)
{
	constexpr int perPage = 100;
	int startIndex = (page_num - 1)*perPage;
	int endIndex = startIndex + perPage - 1;

	if (endIndex > NameEntries.size() - 1)
	{
		endIndex = NameEntries.size() - 1;
	}

	string retStr;

	if (NameEntries.size() == 0)
	{
		return "Name Ban List Empty";
	}

	if (startIndex > NameEntries.size() - 1 || startIndex < 1)
	{
		return "Page Empty";
	}

	retStr = "===PAGE START===\n";
	for (auto it = NameEntries.begin() + startIndex; it != NameEntries.begin() + endIndex + 1; it++)
	{
		retStr += it->GetString();
		retStr += "\n";
	}

	retStr += "===PAGE END===\n";

	retStr += "Showed " + to_string(endIndex - startIndex + 1) + " Names from " + to_string(startIndex + 1) + " to " + to_string(endIndex + 1) + " out of " + to_string(NameEntries.size()) + " banned Names\n";
	return retStr;
}

string NameFilter::GetProtectedNamesInPage(int page_num)
{
	constexpr int perPage = 100;
	int startIndex = (page_num - 1)*perPage;
	int endIndex = startIndex + perPage - 1;

	if (endIndex > ProtectedNameEntries.size() - 1)
	{
		endIndex = ProtectedNameEntries.size() - 1;
	}

	string retStr;

	if (ProtectedNameEntries.size() == 0)
	{
		return "Protected Name List Empty";
	}

	if (startIndex > ProtectedNameEntries.size() - 1 || startIndex < 1)
	{
		return "Page Empty";
	}

	retStr = "===PAGE START===\n";
	for (auto it = ProtectedNameEntries.begin() + startIndex; it != ProtectedNameEntries.begin() + endIndex + 1; it++)
	{
		retStr += it->GetString();
		retStr += "\n";
	}

	retStr += "===PAGE END===\n";

	retStr += "Showed " + to_string(endIndex - startIndex + 1) + " protected names from " + to_string(startIndex + 1) + " to " + to_string(endIndex + 1) + " out of " + to_string(ProtectedNameEntries.size()) + " protected Names\n";
	return retStr;
}


void NameFilter::Init()
{
	ifstream ifs(MAIN_PATH "/namefilter.cfg", ifstream::in);
	if (!ifs.is_open())
	{
		gi.Printf(PATCH_NAME " NameFilter error: could not open " MAIN_PATH "/namefilter.cfg for reading!\n");
		return;
	}

	string line;
	NameFilter filter;
	for (int lineNum = 1; getline(ifs, line); lineNum++)
	{


		//ignore comments
		if (line.substr(0, 2) == "//")
			continue;

		//validate name str
		if (line.empty())
		{
			gi.Printf(PATCH_NAME " NameFilter error: empty name: %s in line %d in " MAIN_PATH "/namefilter.cfg! Skipping...\n", line.c_str(), lineNum);
			continue;
		}

		//add our name filter entry
		filter.AddName(line);
	}
	gi.Printf(PATCH_NAME " NameFilter loaded %d name filter entries successfully\n", NameEntries.size());

	ifs.close();
	///////////////////////////////////////////////////////////////////////

	ifs.open(MAIN_PATH "/protectednamefilter.cfg", ifstream::in);
	if (!ifs.is_open())
	{
		gi.Printf(PATCH_NAME " Protected NameFilter error: could not open " MAIN_PATH "/protectednamefilter.cfg for reading!\n");
		return;
	}

	for (int lineNum = 1; getline(ifs, line); lineNum++)
	{

		size_t namePos, pwPos;
		string name, password;
		static string namelbl("name="), passwordlbl("password="), whitespace(" \t\n\r\f\v");

		//ignore comments
		if (line.substr(0, 2) == "//")
			continue;

		namePos = line.find(namelbl);
		pwPos = line.find(passwordlbl);

		//validate name str
		if (namePos == string::npos || pwPos == string::npos)
		{
			gi.Printf(PATCH_NAME " Protected NameFilter error: could not parse line %d properly in  " MAIN_PATH "/protectednamefilter.cfg! Skipping...\n", lineNum);
			continue;
		}

		name = line.substr(namePos + namelbl.size(), pwPos - (namePos + namelbl.size()));
		password = line.substr(pwPos + passwordlbl.size());

		//trim suffixing whitespace:
		name.erase(name.find_last_not_of(whitespace) + 1);
		password.erase(password.find_last_not_of(whitespace) + 1);

		//add our name filter entry
		filter.AddProtectedName(name, password);
	}
	gi.Printf(PATCH_NAME " Protected NameFilter loaded %d name filter entries successfully\n", ProtectedNameEntries.size());

}

void NameFilter::Shutdown()
{

	ofstream ofs(MAIN_PATH "/namefilter.cfg", ofstream::out | ofstream::trunc);
	if (!ofs.is_open())
	{
		char errStr[128] = { 0 };
		strerror_s(errStr, errno);
		gi.Printf(PATCH_NAME " NameFilter error: could not open " MAIN_PATH "/namefilter.cfg for writing : %s!\n", errStr);
		return;
	}

	size_t i;
	for (i = 0; i < NameEntries.size(); i++)
	{
		const NameEntry &e = NameEntries[i];
		ofs << e.GetString() << endl;

	}

	gi.Printf(PATCH_NAME " NameFilter: saved %d name entries in " MAIN_PATH "/namefilter.cfg\n", i);

	ofs.close();

	//////////////////////////////
	ofs.open(MAIN_PATH "/protectednamefilter.cfg", ofstream::out | ofstream::trunc);
	if (!ofs.is_open())
	{
		char errStr[128] = { 0 };
		strerror_s(errStr, errno);
		gi.Printf(PATCH_NAME " Protected NameFilter error: could not open " MAIN_PATH "/protectednamefilter.cfg for writing : %s!\n", errStr);
		return;
	}

	for (i = 0; i < ProtectedNameEntries.size(); i++)
	{
		const ProtectedNameEntry &e = ProtectedNameEntries[i];
		ofs << e.GetString() << endl;

	}

	gi.Printf(PATCH_NAME " Protected NameFilter: saved %d name entries in " MAIN_PATH "/protectednamefilter.cfg\n", i);
}

