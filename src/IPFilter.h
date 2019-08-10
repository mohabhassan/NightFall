#pragma once
#include <string>
#include <vector>
#include "dgamex86.h"
using namespace std;
constexpr int defaultIPIndex = -1;

class IPEntry
{
	string ipSegments[4];
public:
	IPEntry(string ip_str);
	IPEntry(string ip_str[4]);

	bool IPMatches(string ip_str) const;
	bool IPMatchesExact(string ip_str) const;
	string GetString() const;
	void SetIP(string ip_str);
};

class IPFilter
{
private:
	static vector<IPEntry> IPEntries;

	size_t FindIP(string ip_str, bool masked);
public:
	IPFilter();
	~IPFilter();
	
	bool AddIP(string ip_str);
	bool RemoveIP(string ip_str);
	bool CanConnect(string ip_str);
	string GetIPsInPage(int page_number);


	static void Init();
	static void Shutdown();
};

