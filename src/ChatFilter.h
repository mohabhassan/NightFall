#pragma once
#include <string>
#include <vector>
#include "dgamex86.h"
#include "ScriptVariable.h"
using namespace std;
constexpr int defaultChatIndex = -1;
constexpr int defaultChatClientIndex = -1;

class ChatEntry
{
	string word;
	bool any;
public:
	ChatEntry(string word_str);

	bool ChatMatches(string chat_str) const;
	bool ChatMatchesExact(string chat_str) const;
	string GetString() const;
	void SetString(string word_str);
};

class ChatFilterClientEntry
{
	int clientNum;
	int badChatAttempts;
	bool chatAllowed;
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

class ChatFilter
{
	static vector<ChatEntry> ChatEntries;
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

