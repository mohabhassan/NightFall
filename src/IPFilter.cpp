#include "IPFilter.h"
#include <sstream>
#include <fstream>
#include "misc.h"

vector<IPEntry> IPFilter::IPEntries;

IPEntry::IPEntry(string ip_str)
{
	istringstream iss(ip_str);
	getline(iss, ipSegments[0], '.');
	getline(iss, ipSegments[1], '.');
	getline(iss, ipSegments[2], '.');
	getline(iss, ipSegments[3], '.');
}

IPEntry::IPEntry(string ip_str[4])
{
	for (size_t i = 0; i < 4; i++)
	{
		ipSegments[i] = ip_str[i];
	}
}

bool IPEntry::IPMatches(string ip_str) const
{
	string segmentStr[4];
	istringstream iss(ip_str);

	getline(iss, segmentStr[0], '.');
	getline(iss, segmentStr[1], '.');
	getline(iss, segmentStr[2], '.');
	getline(iss, segmentStr[3], '.');

	for (size_t i = 0; i < 4; i++)
	{
		if (ipSegments[i] != "*")
		{
			if (ipSegments[i] != segmentStr[i])
			{
				return false;
			}
		}
	}
	return true;
}

bool IPEntry::IPMatchesExact(string ip_str) const
{
	string segmentStr[4];
	istringstream iss(ip_str);

	getline(iss, segmentStr[0], '.');
	getline(iss, segmentStr[1], '.');
	getline(iss, segmentStr[2], '.');
	getline(iss, segmentStr[3], '.');

	for (size_t i = 0; i < 4; i++)
	{
		if (ipSegments[i] != segmentStr[i])
		{
			return false;
		}
	}
	return true;
}

string IPEntry::GetString() const
{
	return ipSegments[0] + '.' + ipSegments[1] + '.' + ipSegments[2] + '.' + ipSegments[3];
}

void IPEntry::SetIP(string ip_str)
{
	istringstream iss(ip_str);
	char dot;

	iss >> ipSegments[0] >> dot >> ipSegments[1] >> dot >> ipSegments[2] >> dot >> ipSegments[3];
}

IPFilter::IPFilter()
{
}

IPFilter::~IPFilter()
{
}

//returns pos, or defaultIPIndex if not found
size_t IPFilter::FindIP(string ip_str, bool masked = false)
{

	for (size_t i = 0; i < IPEntries.size(); i++)
	{
		const IPEntry &e = IPEntries[i];
		if (masked)
		{
			if (e.IPMatches(ip_str))
			{
				return i;
			}
		}
		else
		{
			if (e.IPMatchesExact(ip_str))
			{
				return i;
			}
		}
	}
	return defaultIPIndex;
}

//returns true if IP is added
//returns false if IP already exists
bool IPFilter::AddIP(string ip_str)
{
	//search for port
	size_t pos = ip_str.find_first_of(':');
	if (pos != string::npos)
	{
		//we don't care for port so just remove it.
		ip_str.erase(pos);
	}
	size_t index = FindIP(ip_str);
	if (index != defaultIPIndex)
	{
		return false;
	}
	else
	{
		IPEntries.emplace_back(ip_str);
		return true;
	}
}

//returns true if IP is removed
//return false if IP doesn't exist
bool IPFilter::RemoveIP(string ip_str)
{
	//search for port
	size_t pos = ip_str.find_first_of(':');
	if (pos != string::npos)
	{
		//we don't care for port so just remove it.
		ip_str.erase(pos);
	}

	size_t index = FindIP(ip_str);
	if (index == defaultIPIndex)
	{
		return false;
	}
	else
	{
		IPEntries.erase(IPEntries.begin() + index);
		return true;
	}
}

//returns true if IP can connect
bool IPFilter::CanConnect(string ip_str)
{
	//search for port
	size_t pos = ip_str.find_first_of(':');
	if (pos != string::npos)
	{
		//we don't care for port so just remove it.
		ip_str.erase(pos);
	}

	size_t index = FindIP(ip_str, true);
	if (index == defaultIPIndex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//page_number should start from 1
string IPFilter::GetIPsInPage(int page_num)
{
	constexpr int perPage = 100;
	int startIndex = (page_num - 1)*perPage;
	int endIndex = startIndex + perPage - 1;
	
	if (endIndex > IPEntries.size() - 1)
	{
		endIndex = IPEntries.size() - 1;
	}

	string retStr;

	if (IPEntries.size() == 0)
	{
		return "IP Ban List Empty";
	}

	if (startIndex > IPEntries.size() - 1 || startIndex < 1)
	{
		return "Page Empty";
	}
	
	retStr = "===PAGE START===\n";
	for (auto it = IPEntries.begin() + startIndex; it != IPEntries.begin() + endIndex + 1; it++)
	{
		retStr += it->GetString();
		retStr += "\n";
	}

	retStr += "===PAGE END===\n";

	retStr += "Showed " + to_string(endIndex - startIndex + 1) + " IPs from " + to_string(startIndex + 1) + " to " + to_string(endIndex + 1) + " out of " + to_string(IPEntries.size()) + " banned IPs\n";
	return retStr;
}

void IPFilter::Init()
{

	ifstream ifs(MAIN_PATH "/ipfilter.cfg", ifstream::in);
	if (!ifs.is_open())
	{
		gi.Printf(PATCH_NAME " IPFilter error: could not open " MAIN_PATH "/ipfilter.cfg for reading!\n");
		return;
	}

	string line;
	for (int lineNum = 1; getline(ifs, line); lineNum++)
	{
		

		//ignore comments
		if (line.substr(0, 2) == "//")
			continue;

		//validate ip str
		if (!validateIP(line.c_str()))
		{
			gi.Printf(PATCH_NAME " IPFilter error: invalid ip: %s in line %d in " MAIN_PATH "/ipfilter.cfg! Skipping...\n", line.c_str(), lineNum);
			continue;
		}

		//add our ip filter entry
		IPEntries.emplace_back(line);
	}
	gi.Printf(PATCH_NAME " IPFilter loaded %d ip filter entries successfully\n", IPEntries.size());

}

void IPFilter::Shutdown()
{

	ofstream ofs(MAIN_PATH "/ipfilter.cfg", ofstream::out | ofstream::trunc);
	if (!ofs.is_open())
	{
		char errStr[128] = { 0 };
		strerror_s(errStr, errno);
		gi.Printf(PATCH_NAME " IPFilter error: could not open " MAIN_PATH "/ipfilter.cfg for writing : %s!\n", errStr);
		return;
	}

	size_t i;
	for (i = 0; i < IPEntries.size(); i++)
	{
		const IPEntry &e = IPEntries[i];
		ofs << e.GetString() << endl;

	}

	gi.Printf(PATCH_NAME " IPFilter: saved %d ip entries in " MAIN_PATH "/ipfilter.cfg\n", i);
}

