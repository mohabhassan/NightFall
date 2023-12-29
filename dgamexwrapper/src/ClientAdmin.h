#pragma once
#include "dgamex86.h"
#include "sv_misc.h"
#include <vector>
#include <list>
using std::string, std::vector, std::list;

constexpr int rconClientNum = -2;
constexpr int internalClientNum = -3;

class ClientKick
{
	int clientNum;
	bool hasReason;
	string reason;
public:
	ClientKick(int num, bool hasR, string R);
	int getClientNum() const;
	bool reasonExists() const;
	string getReason() const;
};

class ClientBan
{
	int clientNum;
	bool hasReason;
	string reason;
	string ip;
public:
	ClientBan(int num, bool hasR, string R, string ip_str);
	int getClientNum() const;
	bool reasonExists() const;
	string getReason() const;
	string getIP() const;
};

class ClientAdminEntry
{
	string login;
	string password;
	int rights;
public:
	static vector<ClientAdminEntry> entries;

	ClientAdminEntry(string sLogin, string sPassword, int iRights);
	~ClientAdminEntry();

	string getLogin() const;
	string getPassword() const;
	int getRigths() const;

};

class ClientAdminSession
{
	int entryID;
	int clientNum;
public:
	ClientAdminSession(string sLogin, string sPassword, int iClientNum);

	int getClientNum() const;
	int getEntryID() const;

	bool isValid() const;
};

class ClientAdmin
{
	int sessionID;
	int clientNum;
	static std::vector<ClientKick> kicks;
	static std::vector<ClientBan> bans;
	static vector<ClientAdminSession> sessions;
public:
	enum AccessLevel
	{
		ProtectName,
		MapChange,
		Restart,
		GameType,
		FragLimit,
		TimeLimit = FragLimit,
		Kick,
		BadCMD,
		Ban,
		RemoveBan,
		Chat,
		AdminProCMD,
		ListAdmins,
		Rcon,
		Max = 16383,
	};
	ClientAdmin(int cnum);
	~ClientAdmin();

	static void Init();

	static void LoadAdminList();
	static void PrintClientStructOffsets();
	static void Shutdown();



	void HandlePreDisconnect();
	void HandlePostDisconnect();

	int findSession(int cnum) const;

	bool isAdmin();
	bool isRcon();
	bool isInternal();
	bool attemptLogin(string login, string password);
	bool attemptLogout();

	bool hasRight(AccessLevel right);
	int	getRights();

	void AddKick(int kickedClientNum, bool hasReason = false, string reason = "");
	void AddBan(int bannedClientNum, bool hasReason = false, string reason = "");

	bool AddIPBan(string ip_str);
	bool RemoveIPBan(string ip_str);

	string ListIPPage(int page_num);


	bool AddNameBan(string name_str);
	bool RemoveNameBan(string name_str);

	string ListNamePage(int page_num);


	bool AddProtectedName(string name_str, string password);
	bool RemoveProtectedName(string name_str);

	string ListProtectedNamePage(int page_num);

	bool AddChatBan(string word_str);
	bool RemoveChatBan(string word_str);

	string ListChatPage(int page_num);

	bool DisableChat(int clientNum, bool &chatAllowed);
	bool DisableTaunts(int clientNum, bool &tauntsAllowed);

	string ListOnlineAdmins();
};

