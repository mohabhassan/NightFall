#include "IPFilter.h"
#include <sstream>
#include <fstream>
#include "misc.h"
#include "CustomCvar.h"
#include "sv_misc.h"

vector<IPEntry> IPFilter::IPEntries;

/*
 * IPEntry::IPEntry
 * Constructor, IP address string as an argument.
 * */
IPEntry::IPEntry(string ip_str)
{
	istringstream iss(ip_str);
	getline(iss, ipSegments[0], '.');
	getline(iss, ipSegments[1], '.');
	getline(iss, ipSegments[2], '.');
	getline(iss, ipSegments[3], '.');
}

/*
 * IPEntry::IPEntry
 * Constructor, IP address four segments string as an argument.
 * */
IPEntry::IPEntry(string ip_str[4])
{
	for (size_t i = 0; i < 4; i++)
	{
		ipSegments[i] = ip_str[i];
	}
}

/*
 * IPEntry::IPMatches
 * Returns true if banned IP address (member of ip entry) is same as IP address string.
 * Mask checks included
 * */
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

/*
 * IPEntry::IPMatchesExact
 * Returns true if IP address (member of ip entry) is exactly same as IP address string.
 * Mask checks excluded
 * */
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

/*
 * IPEntry::GetString
 * Returns banned IP address string.
 * */
string IPEntry::GetString() const
{
	return ipSegments[0] + '.' + ipSegments[1] + '.' + ipSegments[2] + '.' + ipSegments[3];
}

/*
 * IPEntry::SetIP
 * Sets banned IP address string.
 * Arguments:
 * ip_str - banned IP address string.
 * */
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

/*
 * IPFilter::FindIP
 * Search for IPEntry that matches ip_str.
 * Arguments:
 * ip_str - string to match against.
 * masked - whether or not to do mask checks.
 * Returns id of found IPEntry or defaultIPIndex if not found.
 *
 * */
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

/*
 * IPFilter::AddIP
 * Add a new banned IP (IPEntry) to IPEntries.
 * Arguments:
 * ip_str - IP address to be banned.
 * Returns false if IP address already exists(already banned).
 * Returns true on success.
 *
 * */
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

/*
 * IPFilter::RemoveIP
 * Remove a banned IP address (IPEntry) from IPEntries.
 * Arguments:
 * ip_str - banned IP address to be removed.
 * Returns false if IP address does not exist(not banned).
 * Returns true on success.
 *
 * */
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

/*
 * IPFilter::CanConnect
 * Check whether user can connect to server based on his IP address.
 * Arguments:
 * ip_str - IP address to be checked.
 * Returns false if IP address is banned.
 * Returns true if user can connect.
 * Modfies reason to specified block reason.
 * */
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
extern int* svs_numclients;
//returns false if client should not pass (too many connections)
bool IPFilter::CanConnectMaxConnections(int clientNum)
{
	CustomCvar sv_maxconnperip("sv_maxconnperip", "3", CVAR_ARCHIVE);
	int numConnections = 0;
	client_t* cl = GetClientByClientNum(clientNum);
	if (sv_maxconnperip.GetIntValue() <= 0)
	{
		return true;
	}

	for (size_t i = 0; i < *svs_numclients; i++)
	{
		client_t *icl = GetClientByClientNum(i);
		if (!icl || icl->state == CS_FREE)
			continue;
		if (cl->netchan.remoteAddress.ip[0] == icl->netchan.remoteAddress.ip[0]
			&& cl->netchan.remoteAddress.ip[1] == icl->netchan.remoteAddress.ip[1]
			&& cl->netchan.remoteAddress.ip[2] == icl->netchan.remoteAddress.ip[2]
			&& cl->netchan.remoteAddress.ip[3] == icl->netchan.remoteAddress.ip[3])
		{
			numConnections++;
		}
	}
	
	return numConnections <= sv_maxconnperip.GetIntValue();
}

/*
 * IPFilter::GetIPsInPage
 * Create a string of banned IP addresses indexed by page number.
 * Arguments:
 * page_num - page number to get words of.
 * Returns a formatted/printable string of the list of banned IP addresses in given page, if they exist.
 * */
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

	if (startIndex > IPEntries.size() - 1 || startIndex < 0)
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

/*
 * IPFilter::Init
 * Initialize IP filter lists, parse IP filter file (ipfilter.cfg)
 *
 * */
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

/*
 * IPFilter::Shutdown
 * Shutdown IP filter lists, save to IP filter file (ipfilter.cfg)
 *
 * */
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

