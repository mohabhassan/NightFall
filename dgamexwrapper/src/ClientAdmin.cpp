#include "ClientAdmin.h"
#include <fstream>
#include "g_misc.h"
#include "IPFilter.h"
#include "NameFilter.h"
#include "ChatFilter.h"
#include <sstream>
#include <iomanip>
using std::ifstream, std::includes, std::stringstream;

constexpr int defaultClientNum = -1;
constexpr int defaultEntryID = -1;
constexpr int defaultSessionID = -1;

constexpr int rconSessionID = -2;

constexpr int internalSessionID = -3;

vector<ClientAdminEntry> ClientAdminEntry::entries;

std::vector<ClientKick> ClientAdmin::kicks;
std::vector<ClientBan> ClientAdmin::bans;
std::vector<ClientAdminSession> ClientAdmin::sessions;

ClientAdmin::ClientAdmin(int cnum)
	: clientNum(cnum)
{
	sessionID = findSession(cnum);
}


ClientAdmin::~ClientAdmin()
{
}

void ClientAdmin::Init()
{
	LoadAdminList();
	//PrintClientStructOffsets();
}

void ClientAdmin::LoadAdminList()
{
	ifstream ifs(MAIN_PATH+"/admins.ini", ifstream::in);
	if (!ifs.is_open())
	{
		gi->Printf((PATCH_NAME " ClientAdmin system error: could not open " + MAIN_PATH + "/admins.ini!\n").c_str());
		return;
	}

	string line;
	for (int lineNum = 1; getline(ifs, line); lineNum++)
	{
		size_t loginPos, pwPos, rightsPos;
		string login, password, rights;
		static string loginlbl("login="), passwordlbl("password="), rightslbl("rights="), whitespace(" \t\n\r\f\v");

		//ignore comments
		if (line.substr(0, 2) == "//")
			continue;

		loginPos = line.find(loginlbl);
		pwPos = line.find(passwordlbl);
		rightsPos = line.find(rightslbl);
		if (loginPos == string::npos || pwPos == string::npos || rightsPos == string::npos)
		{
			gi->Printf((PATCH_NAME " ClientAdmin system error: could not parse line %d properly in  " + MAIN_PATH + "/admins.ini! Skipping...\n").c_str(), lineNum);
			continue;
		}
		login = line.substr(loginPos + loginlbl.size(), pwPos - (loginPos + loginlbl.size()));
		password = line.substr(pwPos + passwordlbl.size(), rightsPos - (pwPos + passwordlbl.size()));
		rights = line.substr(rightsPos + rightslbl.size());

		//trim suffixing whitespace:
		login.erase(login.find_last_not_of(whitespace) + 1);
		password.erase(password.find_last_not_of(whitespace) + 1);
		rights.erase(rights.find_last_not_of(whitespace) + 1);

		//validate rights number
		if (rights.find_first_not_of("0123456789") != string::npos)
		{
			gi->Printf((PATCH_NAME " ClientAdmin system error: invalid rights: %s in line %d in  " + MAIN_PATH + "/admins.ini! Skipping...\n").c_str(), rights.c_str(), lineNum);
			continue;
		}
		//add our client admin entry
		ClientAdminEntry::entries.emplace_back(login, password, atoi(rights.c_str()));
	}
	gi->Printf(PATCH_NAME " ClientAdmin system loaded %d admin entries successfully\n", ClientAdminEntry::entries.size());

}



void ClientAdmin::PrintClientStructOffsets()
{
	/*
	sizeof(client_t);//should be 1179620

	gi->Printf("client_t offsetof userinfo = %d\n", offsetof(client_t, userinfo));
	gi->Printf("client_t sizeof(userinfo) = %d\n", sizeof(client_t::userinfo));
	gi->Printf("client_t offsetof reliableSequence = %d\n", offsetof(client_t, reliableSequence));
	gi->Printf("client_t sizeof(reliableSequence) = %d\n", sizeof(client_t::reliableSequence));
	gi->Printf("client_t offsetof reliableAcknowledge = %d\n", offsetof(client_t, reliableAcknowledge));
	gi->Printf("client_t sizeof(reliableAcknowledge) = %d\n", sizeof(client_t::reliableAcknowledge));
	gi->Printf("client_t offsetof reliableCommands = %d\n", offsetof(client_t, reliableCommands));
	gi->Printf("client_t sizeof(reliableCommands) = %d\n", sizeof(client_t::reliableCommands));
	gi->Printf("client_t offsetof reliableSent = %d\n", offsetof(client_t, reliableSent));
	gi->Printf("client_t sizeof(reliableSent) = %d\n", sizeof(client_t::reliableSent));
	gi->Printf("client_t offsetof messageAcknowledge = %d\n", offsetof(client_t, messageAcknowledge));
	gi->Printf("client_t sizeof(messageAcknowledge) = %d\n", sizeof(client_t::messageAcknowledge));
	gi->Printf("client_t offsetof gamestateMessageNum = %d\n", offsetof(client_t, gamestateMessageNum));
	gi->Printf("client_t sizeof(gamestateMessageNum) = %d\n", sizeof(client_t::gamestateMessageNum));
	gi->Printf("client_t offsetof challenge = %d\n", offsetof(client_t, challenge));
	gi->Printf("client_t sizeof(challenge) = %d\n", sizeof(client_t::challenge));
	gi->Printf("client_t offsetof lastUsercmd = %d\n", offsetof(client_t, lastUsercmd));
	gi->Printf("client_t sizeof(lastUsercmd) = %d\n", sizeof(client_t::lastUsercmd));
	gi->Printf("client_t offsetof lastEyeinfo = %d\n", offsetof(client_t, lastEyeinfo));
	gi->Printf("client_t sizeof(lastEyeinfo) = %d\n", sizeof(client_t::lastEyeinfo));
	gi->Printf("client_t offsetof lastMessageNum = %d\n", offsetof(client_t, lastMessageNum));
	gi->Printf("client_t sizeof(lastMessageNum) = %d\n", sizeof(client_t::lastMessageNum));
	gi->Printf("client_t offsetof lastClientCommand = %d\n", offsetof(client_t, lastClientCommand));
	gi->Printf("client_t sizeof(lastClientCommand) = %d\n", sizeof(client_t::lastClientCommand));
	gi->Printf("client_t offsetof lastClientCommandString = %d\n", offsetof(client_t, lastClientCommandString));
	gi->Printf("client_t sizeof(lastClientCommandString) = %d\n", sizeof(client_t::lastClientCommandString));
	gi->Printf("client_t offsetof gentity = %d\n", offsetof(client_t, gentity));
	gi->Printf("client_t sizeof(gentity) = %d\n", sizeof(client_t::gentity));
	gi->Printf("client_t offsetof name = %d\n", offsetof(client_t, name));
	gi->Printf("client_t sizeof(name) = %d\n", sizeof(client_t::name));
	gi->Printf("client_t offsetof downloadName = %d\n", offsetof(client_t, downloadName));
	gi->Printf("client_t sizeof(downloadName) = %d\n", sizeof(client_t::downloadName));
	gi->Printf("client_t offsetof download = %d\n", offsetof(client_t, download));
	gi->Printf("client_t sizeof(download) = %d\n", sizeof(client_t::download));
	gi->Printf("client_t offsetof downloadSize = %d\n", offsetof(client_t, downloadSize));
	gi->Printf("client_t sizeof(downloadSize) = %d\n", sizeof(client_t::downloadSize));
	gi->Printf("client_t offsetof downloadCount = %d\n", offsetof(client_t, downloadCount));
	gi->Printf("client_t sizeof(downloadCount) = %d\n", sizeof(client_t::downloadCount));
	gi->Printf("client_t offsetof downloadClientBlock = %d\n", offsetof(client_t, downloadClientBlock));
	gi->Printf("client_t sizeof(downloadClientBlock) = %d\n", sizeof(client_t::downloadClientBlock));
	gi->Printf("client_t offsetof downloadCurrentBlock = %d\n", offsetof(client_t, downloadCurrentBlock));
	gi->Printf("client_t sizeof(downloadCurrentBlock) = %d\n", sizeof(client_t::downloadCurrentBlock));
	gi->Printf("client_t offsetof downloadXmitBlock = %d\n", offsetof(client_t, downloadXmitBlock));
	gi->Printf("client_t sizeof(downloadXmitBlock) = %d\n", sizeof(client_t::downloadXmitBlock));
	gi->Printf("client_t offsetof downloadBlocks = %d\n", offsetof(client_t, downloadBlocks));
	gi->Printf("client_t sizeof(downloadBlocks) = %d\n", sizeof(client_t::downloadBlocks));
	gi->Printf("client_t offsetof downloadBlockSize = %d\n", offsetof(client_t, downloadBlockSize));
	gi->Printf("client_t sizeof(downloadBlockSize) = %d\n", sizeof(client_t::downloadBlockSize));
	gi->Printf("client_t offsetof downloadEOF = %d\n", offsetof(client_t, downloadEOF));
	gi->Printf("client_t sizeof(downloadEOF) = %d\n", sizeof(client_t::downloadEOF));
	gi->Printf("client_t offsetof downloadSendTime = %d\n", offsetof(client_t, downloadSendTime));
	gi->Printf("client_t sizeof(downloadSendTime) = %d\n", sizeof(client_t::downloadSendTime));
	gi->Printf("client_t offsetof deltaMessage = %d\n", offsetof(client_t, deltaMessage));
	gi->Printf("client_t sizeof(deltaMessage) = %d\n", sizeof(client_t::deltaMessage));
	gi->Printf("client_t offsetof nextReliableTime = %d\n", offsetof(client_t, nextReliableTime));
	gi->Printf("client_t sizeof(nextReliableTime) = %d\n", sizeof(client_t::nextReliableTime));
	gi->Printf("client_t offsetof lastPacketTime = %d\n", offsetof(client_t, lastPacketTime));
	gi->Printf("client_t sizeof(lastPacketTime) = %d\n", sizeof(client_t::lastPacketTime));
	gi->Printf("client_t offsetof lastConnectTime = %d\n", offsetof(client_t, lastConnectTime));
	gi->Printf("client_t sizeof(lastConnectTime) = %d\n", sizeof(client_t::lastConnectTime));
	gi->Printf("client_t offsetof nextSnapshotTime = %d\n", offsetof(client_t, nextSnapshotTime));
	gi->Printf("client_t sizeof(nextSnapshotTime) = %d\n", sizeof(client_t::nextSnapshotTime));
	gi->Printf("client_t offsetof rateDelayed = %d\n", offsetof(client_t, rateDelayed));
	gi->Printf("client_t sizeof(rateDelayed) = %d\n", sizeof(client_t::rateDelayed));
	gi->Printf("client_t offsetof timeoutCount = %d\n", offsetof(client_t, timeoutCount));
	gi->Printf("client_t sizeof(timeoutCount) = %d\n", sizeof(client_t::timeoutCount));
	gi->Printf("client_t offsetof frames = %d\n", offsetof(client_t, frames));
	gi->Printf("client_t sizeof(frames) = %d\n", sizeof(client_t::frames));
	gi->Printf("client_t offsetof ping = %d\n", offsetof(client_t, ping));
	gi->Printf("client_t sizeof(ping) = %d\n", sizeof(client_t::ping));
	gi->Printf("client_t offsetof rate = %d\n", offsetof(client_t, rate));
	gi->Printf("client_t sizeof(rate) = %d\n", sizeof(client_t::rate));
	gi->Printf("client_t offsetof snapshotMsec = %d\n", offsetof(client_t, snapshotMsec));
	gi->Printf("client_t sizeof(snapshotMsec) = %d\n", sizeof(client_t::snapshotMsec));
	gi->Printf("client_t offsetof netchan = %d\n", offsetof(client_t, netchan));
	gi->Printf("client_t sizeof(netchan) = %d\n", sizeof(client_t::netchan));
	gi->Printf("client_t offsetof sounds = %d\n", offsetof(client_t, sounds));
	gi->Printf("client_t sizeof(sounds) = %d\n", sizeof(client_t::sounds));
	gi->Printf("client_t offsetof numberOfSounds = %d\n", offsetof(client_t, numberOfSounds));
	gi->Printf("client_t sizeof(numberOfSounds) = %d\n", sizeof(client_t::numberOfSounds));
	gi->Printf("client_t offsetof locprint = %d\n", offsetof(client_t, locprint));
	gi->Printf("client_t sizeof(locprint) = %d\n", sizeof(client_t::locprint));
	gi->Printf("client_t offsetof locprintX = %d\n", offsetof(client_t, locprintX));
	gi->Printf("client_t sizeof(locprintX) = %d\n", sizeof(client_t::locprintX));
	gi->Printf("client_t offsetof locprintY = %d\n", offsetof(client_t, locprintY));
	gi->Printf("client_t sizeof(locprintY) = %d\n", sizeof(client_t::locprintY));
	gi->Printf("client_t offsetof stringToPrint = %d\n", offsetof(client_t, stringToPrint));
	gi->Printf("client_t sizeof(stringToPrint) = %d\n", sizeof(client_t::stringToPrint));

	gi->Printf("==================================\n"); gi->Printf("netChan_t offsetof sock = %d\n", offsetof(netChan_t, sock));
	gi->Printf("netChan_t sizeof(sock) = %d\n", sizeof(netChan_t::sock));
	gi->Printf("netChan_t offsetof dropped = %d\n", offsetof(netChan_t, dropped));
	gi->Printf("netChan_t sizeof(dropped) = %d\n", sizeof(netChan_t::dropped));
	gi->Printf("netChan_t offsetof remoteAddress = %d\n", offsetof(netChan_t, remoteAddress));
	gi->Printf("netChan_t sizeof(remoteAddress) = %d\n", sizeof(netChan_t::remoteAddress));
	gi->Printf("netChan_t offsetof qport = %d\n", offsetof(netChan_t, qport));
	gi->Printf("netChan_t sizeof(qport) = %d\n", sizeof(netChan_t::qport));
	gi->Printf("netChan_t offsetof incomingSequence = %d\n", offsetof(netChan_t, incomingSequence));
	gi->Printf("netChan_t sizeof(incomingSequence) = %d\n", sizeof(netChan_t::incomingSequence));
	gi->Printf("netChan_t offsetof outgoingSequence = %d\n", offsetof(netChan_t, outgoingSequence));
	gi->Printf("netChan_t sizeof(outgoingSequence) = %d\n", sizeof(netChan_t::outgoingSequence));
	gi->Printf("netChan_t offsetof fragmentSequence = %d\n", offsetof(netChan_t, fragmentSequence));
	gi->Printf("netChan_t sizeof(fragmentSequence) = %d\n", sizeof(netChan_t::fragmentSequence));
	gi->Printf("netChan_t offsetof fragmentLength = %d\n", offsetof(netChan_t, fragmentLength));
	gi->Printf("netChan_t sizeof(fragmentLength) = %d\n", sizeof(netChan_t::fragmentLength));
	gi->Printf("netChan_t offsetof fragmentBuffer = %d\n", offsetof(netChan_t, fragmentBuffer));
	gi->Printf("netChan_t sizeof(fragmentBuffer) = %d\n", sizeof(netChan_t::fragmentBuffer));
	gi->Printf("netChan_t offsetof unsentFragments = %d\n", offsetof(netChan_t, unsentFragments));
	gi->Printf("netChan_t sizeof(unsentFragments) = %d\n", sizeof(netChan_t::unsentFragments));
	gi->Printf("netChan_t offsetof unsentFragmentStart = %d\n", offsetof(netChan_t, unsentFragmentStart));
	gi->Printf("netChan_t sizeof(unsentFragmentStart) = %d\n", sizeof(netChan_t::unsentFragmentStart));
	gi->Printf("netChan_t offsetof unsentLength = %d\n", offsetof(netChan_t, unsentLength));
	gi->Printf("netChan_t sizeof(unsentLength) = %d\n", sizeof(netChan_t::unsentLength));
	gi->Printf("netChan_t offsetof unsentBuffer = %d\n", offsetof(netChan_t, unsentBuffer));
	gi->Printf("netChan_t sizeof(unsentBuffer) = %d\n", sizeof(netChan_t::unsentBuffer));
	*/
}

void ClientAdmin::Shutdown()
{
}

//Called by G_ClientDisconnect
void ClientAdmin::HandlePreDisconnect()
{
	//try to logout first
	attemptLogout();
	//gi->DropClient()
	//if kicked or banned, do our magic
	client_t *cl_actual = GetClientByClientNum(clientNum);
	if (!cl_actual)
	{
		return;
	}
	Client cl(cl_actual);

	//NET_OutOfBandPrint()

	//look for kicks
	for (auto it = kicks.begin(); it != kicks.end(); it++)
	{
		//found
		if (it->getClientNum() == clientNum)
		{
			if (it->reasonExists())
			{
				NET_OutOfBandPrint(NS_SERVER, cl->netchan.remoteAddress, "droperror\nKicked from server for:\n%s", it->getReason().c_str());
			}
			else
			{
				NET_OutOfBandPrint(NS_SERVER, cl->netchan.remoteAddress, "droperror\nKicked from server");
			}
			//kicks.erase(it);//delete kick//delted in post
			return;
		}
	}

	//look for bans
	for (auto it = bans.begin(); it != bans.end(); it++)
	{
		//found
		if (it->getClientNum() == clientNum)
		{
			if (it->reasonExists())
			{
				NET_OutOfBandPrint(NS_SERVER, cl->netchan.remoteAddress, "droperror\nBanned from server for:\n%s", it->getReason().c_str());
			}
			else
			{
				NET_OutOfBandPrint(NS_SERVER, cl->netchan.remoteAddress, "droperror\nBanned from server");
			}
			//bans.erase(it);//delete bans//delted in post
			return;
		}
	}
}

void ClientAdmin::HandlePostDisconnect()
{
	client_t *cl_actual = GetClientByClientNum(clientNum);
	if (!cl_actual)
	{
		return;
	}

	Client cl(cl_actual);
	//G_PrintToAllClients((cl->name + string("was kicked\n")).c_str());

	//look for kicks
	for (auto it = kicks.begin(); it != kicks.end(); it++)
	{
		//found
		if (it->getClientNum() == clientNum)
		{
			if (it->reasonExists())
			{
				G_PrintToAllClients((cl->name + string(" was kicked for ") + it->getReason() + "\n").c_str());
			}
			else
			{
				G_PrintToAllClients((cl->name + string("was kicked\n")).c_str());
			}
			kicks.erase(it);//delete kick
			return;
		}
	}

	//look for bans
	for (auto it = bans.begin(); it != bans.end(); it++)
	{
		//found
		if (it->getClientNum() == clientNum)
		{
			if (it->reasonExists())
			{
				G_PrintToAllClients((cl->name + string(" was banned for ") + it->getReason() + "\n").c_str());
			}
			else
			{
				G_PrintToAllClients((cl->name + string("was banned\n")).c_str());
			}

			IPFilter filter;
			filter.AddIP(it->getIP());

			bans.erase(it);//delete ban
			return;
		}
	}
}


int ClientAdmin::findSession(int cnum) const
{
	if (cnum == rconClientNum)
	{
		return rconSessionID;
	}
	if (cnum == internalClientNum)
	{
		return internalSessionID;
	}

	for (size_t i = 0; i < sessions.size(); i++)
	{
		if (sessions[i].getClientNum() == cnum)
		{
			return i;
		}
	}

	return defaultSessionID;
}

bool ClientAdmin::isAdmin()
{
	return sessionID != defaultSessionID;
}

bool ClientAdmin::isRcon()
{
	return sessionID == rconSessionID;
}

bool ClientAdmin::isInternal()
{
	return sessionID == internalSessionID;
}

bool ClientAdmin::attemptLogin(string login, string password)
{
	if (sessionID == defaultSessionID)
	{
		//not logged in
		ClientAdminSession session(login, password, clientNum);
		if (session.isValid())
		{
			sessions.push_back(session);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		//already logged in
		return true;
	}
}

bool ClientAdmin::attemptLogout()
{
	for (auto it = sessions.begin(); it != sessions.end(); it++)
	{
		//found
		if (it->getClientNum() == clientNum)
		{
			sessions.erase(it);//delete session
			return true;
		}
	}
	return false;
}

bool ClientAdmin::hasRight(AccessLevel right)
{
	if (!isAdmin())
	{
		return false;
	}
	if (isRcon() || isInternal())
	{
		return true;
	}
	ClientAdminSession & session = sessions[sessionID];
	ClientAdminEntry & entry = ClientAdminEntry::entries[session.getEntryID()];
	return entry.getRigths() & (1<<right);
}

void ClientAdmin::AddKick(int kickedClientNum, bool hasReason, string reason)
{
	if (!isAdmin() || !hasRight(ClientAdmin::Kick))
	{
		return;
	}
	kicks.emplace_back(kickedClientNum, hasReason, reason);
}

void ClientAdmin::AddBan(int bannedClientNum, bool hasReason, string reason)
{
	if (!isAdmin() || !hasRight(ClientAdmin::Ban))
	{
		return;
	}

	client_t *cl_actual = GetClientByClientNum(bannedClientNum);
	if (!cl_actual)
	{
		return;
	}
	Client cl(cl_actual);

	string ip = GetIPFromClient(cl);

	if (ip != "")
	{
		bans.emplace_back(bannedClientNum, hasReason, reason, ip);
	}
	else
	{
		gi->Printf(PATCH_NAME " ClientAdmin system error: could not ban ip of client num: %d, name: %s empty ip!\n", bannedClientNum, cl->name);
	}

}

//Returns true if IP banned.
//Returns false if IP already exists.
bool ClientAdmin::AddIPBan(string ip_str)
{
	if (!isAdmin() || !hasRight(ClientAdmin::Ban))
	{
		return false;
	}

	IPFilter filter;
	return filter.AddIP(ip_str);
}

//Returns true if entry already exists.
bool ClientAdmin::RemoveIPBan(string ip_str)
{
	if (!isAdmin() || !hasRight(ClientAdmin::RemoveBan))
	{
		return false;
	}
	IPFilter filter;
	return filter.RemoveIP(ip_str);
}


string ClientAdmin::ListIPPage(int page_num)
{
	if (!isAdmin() || (!hasRight(ClientAdmin::Ban) && !hasRight(ClientAdmin::RemoveBan)))
	{
		return "";
	}
	IPFilter filter;
	return filter.GetIPsInPage(page_num);
}

bool ClientAdmin::AddNameBan(string name_str)
{
	if (!isAdmin() || !hasRight(ClientAdmin::Ban))
	{
		return false;
	}

	NameFilter filter;
	return filter.AddName(name_str);
}

bool ClientAdmin::RemoveNameBan(string name_str)
{
	if (!isAdmin() || !hasRight(ClientAdmin::RemoveBan))
	{
		return false;
	}
	NameFilter filter;
	return filter.RemoveName(name_str);
}

string ClientAdmin::ListNamePage(int page_num)
{
	if (!isAdmin() || (!hasRight(ClientAdmin::Ban) && !hasRight(ClientAdmin::RemoveBan)))
	{
		return "";
	}
	NameFilter filter;
	return filter.GetNamesInPage(page_num);
}

bool ClientAdmin::AddProtectedName(string name_str, string password)
{
	if (!isAdmin() || !hasRight(ClientAdmin::ProtectName))
	{
		return false;
	}

	NameFilter filter;
	return filter.AddProtectedName(name_str, password);
}

bool ClientAdmin::RemoveProtectedName(string name_str)
{
	if (!isAdmin() || !hasRight(ClientAdmin::ProtectName))
	{
		return false;
	}
	NameFilter filter;
	return filter.RemoveProtectedName(name_str);
}

string ClientAdmin::ListProtectedNamePage(int page_num)
{
	if (!isAdmin() || !hasRight(ClientAdmin::ProtectName))
	{
		return "";
	}
	NameFilter filter;
	return filter.GetProtectedNamesInPage(page_num);
}

bool ClientAdmin::AddChatBan(string word_str)
{
	if (!isAdmin() || !hasRight(ClientAdmin::Chat))
	{
		return false;
	}

	ChatFilter filter;
	return filter.AddWord(word_str);
}

bool ClientAdmin::RemoveChatBan(string word_str)
{
	if (!isAdmin() || !hasRight(ClientAdmin::Chat))
	{
		return false;
	}
	ChatFilter filter;
	return filter.RemoveWord(word_str);
}

string ClientAdmin::ListChatPage(int page_num)
{
	if (!isAdmin() || !hasRight(ClientAdmin::Chat))
	{
		return "";
	}
	ChatFilter filter;
	return filter.GetWordsInPage(page_num);
}

//returns true on success
bool ClientAdmin::DisableChat(int clientNum, bool &chatAllowed)
{
	if (!isAdmin() || !hasRight(ClientAdmin::Chat))
	{
		return false;
	}
	ChatFilter filter;
	return filter.ToggleDisableChat(clientNum, chatAllowed);
}

//returns true on success
bool ClientAdmin::DisableTaunts(int clientNum, bool &tauntsAllowed)
{
	if (!isAdmin() || !hasRight(ClientAdmin::Chat))
	{
		return false;
	}
	ChatFilter filter;
	return filter.ToggleDisableTaunt(clientNum, tauntsAllowed);
}

string ClientAdmin::ListOnlineAdmins()
{
	if (!isAdmin() || !hasRight(ClientAdmin::ListAdmins))
	{
		return "";
	}
	stringstream ss;
	ss << "Name | ";
	ss << "Rights";
	ss << "\n";
	for (auto &e: sessions)
	{
		client_t * cl_real = GetClientByClientNum(e.getClientNum());
		if (!cl_real)
		{
			gi->Printf(PATCH_NAME " ClientAdmin ListOnlineAdmins error: Invalid session clientnum %d, Ignoring...\n", e.getClientNum());
			continue;
		}
		Client cl(cl_real);
		ss << cl->name << " | ";
		ss << ClientAdminEntry::entries[e.getEntryID()].getRigths();
		ss << "\n";
	}
	return ss.str();
}

ClientKick::ClientKick(int num, bool hasR, string R)
	: clientNum(num), hasReason(hasR), reason(R)
{
}

int ClientKick::getClientNum() const
{
	return clientNum;
}

bool ClientKick::reasonExists() const
{
	return hasReason;
}

string ClientKick::getReason() const
{
	return reason;
}

ClientBan::ClientBan(int num, bool hasR, string R, string ip_str)
	: clientNum(num), hasReason(hasR), reason(R), ip(ip_str)
{
}

int ClientBan::getClientNum() const
{
	return clientNum;
}

bool ClientBan::reasonExists() const
{
	return hasReason;
}

string ClientBan::getReason() const
{
	return reason;
}

string ClientBan::getIP() const
{
	return ip;
}

ClientAdminEntry::ClientAdminEntry(string sLogin, string sPassword, int iRights)
	: login(sLogin), password(sPassword), rights(iRights)
{
}

ClientAdminEntry::~ClientAdminEntry()
{
}

string ClientAdminEntry::getLogin() const
{
	return login;
}

string ClientAdminEntry::getPassword() const
{
	return password;
}

int ClientAdminEntry::getRigths() const
{
	return rights;
}

ClientAdminSession::ClientAdminSession(string sLogin, string sPassword, int iClientNum)
{
	for (size_t i = 0; i < ClientAdminEntry::entries.size(); i++)
	{
		ClientAdminEntry &entry = ClientAdminEntry::entries[i];
		if (entry.getLogin() == sLogin && entry.getPassword() == sPassword)
		{
			entryID = i;
			clientNum = iClientNum;
			return;
		}
	}

	//invalid login.
	entryID = defaultEntryID;
	clientNum = defaultClientNum;
}

int ClientAdminSession::getClientNum() const
{
	return clientNum;
}

int ClientAdminSession::getEntryID() const
{
	return entryID;
}

bool ClientAdminSession::isValid() const
{
	return entryID != defaultEntryID;
}
