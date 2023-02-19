#pragma once
#include <string>
#include <vector>
#include "dgamex86.h"
using namespace std;
constexpr int defaultNameIndex = -1;

/* Class NameEntry
 * A name entry to be used in NameFilter entry list.
 * Represents a banned name.
 * */
class NameEntry
{
	/* name to be banned */
	string name;
	/* whether or not to check for partial matches */
	bool any;
public:
	NameEntry(string name_str, bool bAny);

	bool NameMatches(string name_str) const;
	bool NameMatchesExact(string name_str) const;
	string GetString() const;
	bool AnyOccurence() const;
	void SetName(string name_str, bool bAny);
};

/* Class ProtectedNameEntry
 * A protected name entry to be used in ProtectedNameFilter entry list.
 * Represents a protected name.
 * */
class ProtectedNameEntry
{
	/* name to be protected */
	string name;
	/* password name to be protected */
	string password;
public:
	ProtectedNameEntry(string name_str, string pw_str);

	bool NameMatches(string name_str) const;
	bool PasswordMatches(string pw_str) const;
	string GetString() const;
	void SetName(string name_str, string pw_str);
};

/* Class NameFilter
 * A filter that is responsible to handle any blockage of client connections based on their names.
 * It also blocks client renames.
 * */
class NameFilter
{
	/* list of banned name entries */
	static vector<NameEntry> NameEntries;
	/* list of protected name entries */
	static vector<ProtectedNameEntry> ProtectedNameEntries;
	size_t FindName(string name_str, bool exact);
	size_t FindProtectedName(string name_str);
public:
	NameFilter();
	~NameFilter();


	bool AddName(string name_str);
	bool AddProtectedName(string name_str, string pasword);
	bool RemoveName(string name_str);
	bool RemoveProtectedName(string name_str);
	bool CanConnect(string name_str);
	bool CanConnectProtected(string name_str, string password);
	string GetNamesInPage(int page_number);
	string GetProtectedNamesInPage(int page_number);


	static void Init();
	static void Shutdown();
};

