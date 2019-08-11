#include "ChatFilter.h"
#include <fstream>
#include "CustomCvar.h"
#include "ScriptedEvent.h"

vector<ChatEntry> ChatFilter::ChatEntries;

vector<ChatFilterClientEntry> ChatFilter::ChatClientEntries;


ChatEntry::ChatEntry(string word_str)
{
	SetString(word_str);
}

bool ChatEntry::ChatMatches(string chat_str) const
{
	return stristr(chat_str.c_str(), word.c_str()) != NULL;
}

bool ChatEntry::ChatMatchesExact(string chat_str) const
{
	return stricmp(chat_str.c_str(), word.c_str()) == 0;
}

string ChatEntry::GetString() const
{
	return word;
}

void ChatEntry::SetString(string chat_str)
{
	word = chat_str;
}

size_t ChatFilter::FindChat(string word_str, bool exact = false)
{
	for (size_t i = 0; i < ChatEntries.size(); i++)
	{
		const ChatEntry &e = ChatEntries[i];
		if (exact)
		{
			if (e.ChatMatchesExact(word_str))
			{
				return i;
			}
		}
		else
		{
			if (e.ChatMatches(word_str))
			{
				return i;
			}
		}
	}
	return defaultChatIndex;
}

size_t ChatFilter::FindChatClient(int ClientNum)
{
	for (size_t i = 0; i < ChatClientEntries.size(); i++)
	{
		if (ChatClientEntries[i].GetClientNum() == ClientNum)
		{
			return i;
		}
	}
	return defaultChatClientIndex;
}

ChatFilterClientEntry::ChatFilterClientEntry(int cNum, int iAttempts = 0, bool bChatAllowed = true, bool bTauntsAllowed = true)
{
	clientNum = cNum;
	badChatAttempts = iAttempts;
	chatAllowed = bChatAllowed;
	tauntsAllowed = bTauntsAllowed;
}

int ChatFilterClientEntry::GetClientNum() const
{
	return clientNum;
}

int ChatFilterClientEntry::GetNumAttempts() const
{
	return badChatAttempts;
}

bool ChatFilterClientEntry::GetChatAllowed() const
{
	return chatAllowed;
}


bool ChatFilterClientEntry::GetTauntsAllowed() const
{
	return tauntsAllowed;
}

void ChatFilterClientEntry::SetNumAttempts(int iAttempts)
{
	badChatAttempts = iAttempts;
}

void ChatFilterClientEntry::SetChatAllowed(bool bAllowed)
{
	chatAllowed = bAllowed;
}

void ChatFilterClientEntry::SetTauntsAllowed(bool bAllowed)
{
	tauntsAllowed = bAllowed;
}

ChatFilter::ChatFilter()
{
}


ChatFilter::~ChatFilter()
{
}

bool ChatFilter::AddWord(string word_str)
{
	size_t index = FindChat(word_str, true);

	if (index != defaultChatIndex)
	{
		return false;
	}
	else
	{
		ChatEntries.emplace_back(word_str);
		return true;
	}
}

bool ChatFilter::RemoveWord(string word_str)
{
	size_t index = FindChat(word_str, true);

	if (index == defaultChatIndex)
	{
		return false;
	}
	else
	{
		ChatEntries.erase(ChatEntries.begin() + index);
		return true;
	}
}

bool ChatFilter::CanSend(const vector<string>& chat_args, int clientNum, bool &shouldKick, string & rejectReason)
{

	//sayteam test1 test2 test3 test4 test5 sdfgfsg
	//args are:
	//clientnum part1 part2 part3 part4 ...
	//example:
	//1 test1 test2 test3 test4 ...
	//
	//test1 is arg 2
	//sayteam is -1
	//normal say is 0
	//sayprivate & sayone: clientnum is actualy clientnum (it's a bit fuzzy when using sv_privateclients)
	//important checks first.
	bool isTaunt = chat_args[1].size() == 3 && chat_args[1][0] == '*' && chat_args[1][1] >= '1' && chat_args[1][1] <= '9' && chat_args[1][2] >= '1' && chat_args[1][2] <= '9';
	shouldKick = false;

	CustomCvar sv_disablechat("sv_disablechat", "0", CVAR_ARCHIVE);
	if (sv_disablechat.GetIntValue() == 1)
	{
		rejectReason = "Chat disabled for everyone.";
		return false;
	}
	else
	{
		size_t clientIndex = FindChatClient(clientNum);
		if (clientIndex == defaultChatClientIndex)
		{
			gi.Printf(PATCH_NAME " ChatFilter CanSend error 1: client num %d not found, Ignoring...\n", clientNum);
		}
		else
		{
			if (ChatClientEntries[clientIndex].GetChatAllowed() == false)
			{
				rejectReason = "Chat disabled for you.";
				return false;
			}
		}
	}

	if (isTaunt)
	{
		CustomCvar sv_disabletaunt("sv_disabletaunt", "0", CVAR_ARCHIVE);
		if (sv_disabletaunt.GetIntValue())
		{
			rejectReason = "Taunts disabled for everyone.";
			return false;
		}
		else
		{
			size_t clientIndex = FindChatClient(clientNum);
			if (clientIndex == defaultChatClientIndex)
			{
				gi.Printf(PATCH_NAME " ChatFilter CanSend error 2: client num %d not found, Ignoring...\n", clientNum);
			}
			else
			{
				if (ChatClientEntries[clientIndex].GetTauntsAllowed() == false)
				{
					rejectReason = "Taunts disabled for you.";
					return false;
				}
			}
		}
	}
	else
	{

		CustomCvar sv_filterchat("sv_filterchat", "1", CVAR_ARCHIVE);
		if (sv_filterchat.GetIntValue())
		{
			string chat_str = "";
			size_t index;
			for (size_t i = 0; i < chat_args.size(); i++)
			{
				chat_str += chat_args[i];
				chat_str += " ";
			}
			chat_str.pop_back();

			index = FindChat(chat_str, false);

			if (index == defaultChatIndex)
			{
				return true;
			}
			else
			{

				rejectReason = "Dissallowed word in chat.\n";

				size_t clientIndex = FindChatClient(clientNum);
				if (clientIndex == defaultChatClientIndex)
				{
					gi.Printf(PATCH_NAME " ChatFilter CanSend error 3: client num %d not found, Ignoring...\n", clientNum);
				}
				else
				{
					CustomCvar g_badchatlimit("g_badchatlimit", "3", CVAR_ARCHIVE);
					ChatFilterClientEntry & e = ChatClientEntries[clientIndex];
					e.SetNumAttempts(e.GetNumAttempts() + 1);
					if (e.GetNumAttempts() >= g_badchatlimit.GetIntValue())
					{
						shouldKick = true;
						rejectReason += "Maximum number of " + to_string(g_badchatlimit.GetIntValue()) + " warning(s) reached\n";
					}
					else
					{
						rejectReason += "You have " + to_string(g_badchatlimit.GetIntValue() - e.GetNumAttempts()) + " more warning(s) remiaining\n";
					}
				}

				return false;
			}
		}
	}
	return true;
}

bool ChatFilter::CheckScriptCallback(vector<string>& chat_args, gentity_t * ent, int target)
{

	ScriptedEvent sev(SEV_DMMESSAGE);

	if (sev.isRegistered())
	{
		ScriptVariable var;
		sev.Trigger({ (Entity*)ent->entity, target, chat_args}, &var);
		if (var.GetType() != VARIABLE_POINTER)
		{
			return var.intValue();
		}
		else
		{
			gi.Printf(PATCH_NAME " ChatFilter Script Callback error: dmmessage handler script is taking too long to repsond, allowing mesage.\n");
			return true;
		}
	}
	return true;
}

string ChatFilter::GetWordsInPage(int page_num)
{
	constexpr int perPage = 100;
	int startIndex = (page_num - 1)*perPage;
	int endIndex = startIndex + perPage - 1;

	if (endIndex > ChatEntries.size() - 1)
	{
		endIndex = ChatEntries.size() - 1;
	}

	string retStr;

	if (ChatEntries.size() == 0)
	{
		return "Chat Filter List Empty";
	}

	if (startIndex > ChatEntries.size() - 1 || startIndex < 1)
	{
		return "Page Empty";
	}

	retStr = "===PAGE START===\n";
	for (auto it = ChatEntries.begin() + startIndex; it != ChatEntries.begin() + endIndex + 1; it++)
	{
		retStr += it->GetString();
		retStr += "\n";
	}

	retStr += "===PAGE END===\n";

	retStr += "Showed " + to_string(endIndex - startIndex + 1) + " words from " + to_string(startIndex + 1) + " to " + to_string(endIndex + 1) + " out of " + to_string(ChatEntries.size()) + " banned words\n";
	return retStr;
}

void ChatFilter::ClientConnected(int clientNum)
{
	ChatClientEntries.emplace_back(clientNum);
}

void ChatFilter::ClientDisconnected(int clientNum)
{
	size_t index = FindChatClient(clientNum);
	if (index == defaultChatClientIndex)
	{
		gi.Printf(PATCH_NAME " ChatFilter ClientDisconnected error: client num not found %d, Ignoring...\n", clientNum);
	}
	else
	{
		ChatClientEntries.erase(ChatClientEntries.begin() + index);
	}
}

//returns true on success.
bool ChatFilter::ToggleDisableChat(int clientNum, bool & chatAllowed)
{
	size_t clientIndex = FindChatClient(clientNum);
	//just ignore non found client nums
	if (clientIndex != defaultChatClientIndex)
	{
		ChatFilterClientEntry & e = ChatClientEntries[clientIndex];
		e.SetChatAllowed(!e.GetChatAllowed());
		chatAllowed = e.GetChatAllowed();
		return true;
	}
	return false;
}

//returns true on success.
bool ChatFilter::ToggleDisableTaunt(int clientNum, bool & tauntsAllowed)
{
	size_t clientIndex = FindChatClient(clientNum);
	//just ignore non found client nums
	if (clientIndex != defaultChatClientIndex)
	{
		ChatFilterClientEntry & e = ChatClientEntries[clientIndex];
		e.SetTauntsAllowed(!e.GetTauntsAllowed());
		tauntsAllowed = e.GetChatAllowed();
		return true;
	}
	return false;
}

void ChatFilter::Init()
{
	ifstream ifs(MAIN_PATH "/chatfilter.cfg", ifstream::in);
	if (!ifs.is_open())
	{
		gi.Printf(PATCH_NAME " ChatFilter error: could not open " MAIN_PATH "/chatfilter.cfg for reading!\n");
		return;
	}

	string line;
	ChatFilter filter;
	for (int lineNum = 1; getline(ifs, line); lineNum++)
	{


		//ignore comments
		if (line.substr(0, 2) == "//")
			continue;

		//validate name str
		if (line.empty())
		{
			gi.Printf(PATCH_NAME " ChatFilter error: empty word: %s in line %d in " MAIN_PATH "/chatfilter.cfg! Skipping...\n", line.c_str(), lineNum);
			continue;
		}

		//add our name filter entry
		filter.AddWord(line);
	}
	gi.Printf(PATCH_NAME " ChatFilter loaded %d chat filter entries successfully\n", ChatEntries.size());
}

void ChatFilter::Shutdown()
{
	ofstream ofs(MAIN_PATH "/chatfilter.cfg", ofstream::out | ofstream::trunc);
	if (!ofs.is_open())
	{
		char errStr[128] = { 0 };
		strerror_s(errStr, errno);
		gi.Printf(PATCH_NAME " ChatFilter error: could not open " MAIN_PATH "/chatfilter.cfg for writing : %s!\n", errStr);
		return;
	}

	size_t i;
	for (i = 0; i < ChatEntries.size(); i++)
	{
		const ChatEntry &e = ChatEntries[i];
		ofs << e.GetString() << endl;

	}

	gi.Printf(PATCH_NAME " ChatFilter: saved %d chat entries in " MAIN_PATH "/chatfilter.cfg\n", i);
}
