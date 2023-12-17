#pragma once
#include <string>
#include <vector>
#include "dgamex86.h"
#include "ScriptVariable.h"
using std::string, std::vector;
constexpr int defaultChatIndex = -1;
constexpr int defaultChatClientIndex = -1;
/* Class ChatEntry
 * A chat entry to be used in ChatFilter entry list.
 * Represents a banned word in chat.
 * */
class ChatEntry
{
	/* banned word */
	string word;
public:
	ChatEntry(string word_str);

	bool ChatMatches(string chat_str) const;
	bool ChatMatchesExact(string chat_str) const;
	string GetString() const;
	void SetString(string word_str);
};

/* Class ChatFilterClientEntry
 * A chat client entry to be used in ChatFilter client entry list.
 * Represents a client that used a banned word(ChatEntry) at least once in chat.
 * Or a client that has been disallowed chats or taunts.
 * */
class ChatFilterClientEntry
{
	/* client number */
	int clientNum;
	/* number of bad word attepmpts */
	int badChatAttempts;
	/* allowed chat */
	bool chatAllowed;
	/* allowed taunts */
	bool tauntsAllowed;
public:
	ChatFilterClientEntry(int cNum, int iAttempts, bool bChatAllowed, bool bTauntsAllowed);

	int GetClientNum() const;
	int GetNumAttempts() const;
	bool GetChatAllowed() const;
	bool GetTauntsAllowed() const;

	void SetNumAttempts(int iAttempts);
	void SetChatAllowed(bool bAllowed);
	void SetTauntsAllowed(bool bAllowed);
};

/* Class ChatFilter
 * A filter that is responsible to handle any blockage of chat messages for a given client.
 * */
class ChatFilter
{
	/* list of banned word entries */
	static vector<ChatEntry> ChatEntries;
	/* list of client rules(banned chat/taunts/number of penalites) entries */
	static vector<ChatFilterClientEntry> ChatClientEntries;
	size_t FindChat(string word_str, bool exact);
	size_t FindChatClient(int ClientNum);

public:
	ChatFilter();
	~ChatFilter();

	bool AddWord(string word_str);
	bool RemoveWord(string word_str);
	bool CanSend(const vector<string>& chat_args, int clientNum, bool &shouldKick, string& rejectReason);

	bool CheckScriptCallback(vector<string>& chat_args, gentity_t *ent, int target);

	string GetWordsInPage(int page_number);


	void ClientConnected(int clientNum);
	void ClientDisconnected(int clientNum);

	bool ToggleDisableChat(int clientNum, bool & chatAllowed);
	bool ToggleDisableTaunt(int clientNum, bool & tauntsAllowed);

	static void Init();
	static void Shutdown();
};

