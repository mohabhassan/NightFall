#include "ChatFilter.h"
#include <fstream>
#include "CustomCvar.h"
#include "ScriptedEvent.h"

vector<ChatEntry> ChatFilter::ChatEntries;

vector<ChatFilterClientEntry> ChatFilter::ChatClientEntries;

/* 
 * ChatEntry::ChatEntry
 * Constructor, takes banned word string as an argument.
 * */
ChatEntry::ChatEntry(string word_str)
{
	SetString(word_str);
}

/*
 * ChatEntry::ChatMatches
 * Returns true if banned word (member of chat entry) is found inside given chat message string.
 * Case-insensitive
 * */
bool ChatEntry::ChatMatches(string chat_str) const
{
	return stristr(chat_str.c_str(), word.c_str()) != NULL;
}

/*
 * ChatEntry::ChatMatchesExact
 * Returns true if banned word (member of chat entry) is exactly same as chat message string.
 * Case-insensitive.
 * */
bool ChatEntry::ChatMatchesExact(string chat_str) const
{
	return stricmp(chat_str.c_str(), word.c_str()) == 0;
}

/*
 * ChatEntry::GetString
 * Returns banned word string.
 * */
string ChatEntry::GetString() const
{
	return word;
}

/*
 * ChatEntry::SetString
 * Sets banned word string.
 * */
void ChatEntry::SetString(string chat_str)
{
	word = chat_str;
}

/*
 * ChatFilterClientEntry::ChatFilterClientEntry
 * Constructor
 * */
ChatFilterClientEntry::ChatFilterClientEntry(int cNum, int iAttempts = 0, bool bChatAllowed = true, bool bTauntsAllowed = true)
{
	clientNum = cNum;
	badChatAttempts = iAttempts;
	chatAllowed = bChatAllowed;
	tauntsAllowed = bTauntsAllowed;
}

/*
 * ChatFilterClientEntry::GetClientNum
 * Getter for client number.
 * */
int ChatFilterClientEntry::GetClientNum() const
{
	return clientNum;
}

/*
 * ChatFilterClientEntry::GetNumAttempts
 * Getter for number of bad word attempts.
 * */
int ChatFilterClientEntry::GetNumAttempts() const
{
	return badChatAttempts;
}

/*
 * ChatFilterClientEntry::GetChatAllowed
 * Returns whether chat is allowed for client or not.
 * */
bool ChatFilterClientEntry::GetChatAllowed() const
{
	return chatAllowed;
}

/*
 * ChatFilterClientEntry::GetTauntsAllowed
 * Returns whether taunts are allowed for client or not.
 * */
bool ChatFilterClientEntry::GetTauntsAllowed() const
{
	return tauntsAllowed;
}

/*
 * ChatFilterClientEntry::SetNumAttempts
 * Sets number of bad word attempts.
 * */
void ChatFilterClientEntry::SetNumAttempts(int iAttempts)
{
	badChatAttempts = iAttempts;
}

/*
 * ChatFilterClientEntry::SetChatAllowed
 * Sets if chat is allowed for client.
 * */
void ChatFilterClientEntry::SetChatAllowed(bool bAllowed)
{
	chatAllowed = bAllowed;
}

/*
 * ChatFilterClientEntry::SetTauntsAllowed
 * Sets if taunts are allowed for client.
 * */
void ChatFilterClientEntry::SetTauntsAllowed(bool bAllowed)
{
	tauntsAllowed = bAllowed;
}

/*
 * ChatFilter::FindChat
 * Search for ChatEntry that matches word_str.
 * Arguments:
 * word_str - string to match against.
 * exact - whether or not to do exact search vs in-string search.
 * Returns id of found ChatEntry or defaultChatIndex if not found.
 * 
 * */
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

/*
 * ChatFilter::FindChatClient
 * Search for ChatClientEntry that matches ClientNum.
 * Arguments:
 * ClientNum - client num to search for.
 * Returns id of found ChatClientEntry or defaultChatClientIndex if not found.
 *
 * */
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

ChatFilter::ChatFilter()
{
}


ChatFilter::~ChatFilter()
{
}

/*
 * ChatFilter::AddWord
 * Add a new banned chat word (ChatEntry) to ChatEntries.
 * Arguments:
 * word_str - word to be banned.
 * Returns false if word already exists(already banned).
 * Returns true on success.
 *
 * */
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

/*
 * ChatFilter::RemoveWord
 * Remove a banned chat word (ChatEntry) from ChatEntries.
 * Arguments:
 * word_str - banned word to be removed.
 * Returns false if word does not exist(not banned).
 * Returns true on success.
 *
 * */
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

/*
 * ChatFilter::CanSend
 * Check if client can send said chat message or not.
 * Arguments:
 * chat_args - vector of space separate list of chat message split into arguments.
 * clientNum - client number for client that sent the chat message.
 * Return values:
 * Returns true if client can send message, false otherwise.
 * shouldKick - whether or not client should be kicked.
 * rejectReason - a reason that's printed to player screen in case of rejecting chat message.
 *
 * */
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

/*
 * ChatFilter::CheckScriptCallback
 * Check if necessary script callbacks should be called for given chat message.
 * Arguments:
 * chat_args - vector of space separate list of chat message split into arguments.
 * ent - gentity for client that sent the chat message.
 * target - target that recieves chat message, -1 means team(sayteam), 0 means all (say) and other positive numbers mean private message (sayp or sayprivate).
 * Returns true if client can send message, false otherwise.
 * */
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

/*
 * ChatFilter::GetWordsInPage
 * Create a string of banned chat words indexed by page number.
 * Arguments:
 * page_num - page number to get words of.
 * Returns a formatted/printable string of the list of banned chat words in given page, if they exist.
 * */
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

/*
 * ChatFilter::ClientConnected
 * Handle client connected event.
 * Creates a new ChatClientEntry into ChatClientEntries.
 * Arguments:
 * clientNum - client number of connected client.
 * */
void ChatFilter::ClientConnected(int clientNum)
{
	ChatClientEntries.emplace_back(clientNum);
}

/*
 * ChatFilter::ClientDisconnected
 * Handle client disconnected event.
 * Removes existing ChatClientEntry from ChatClientEntries.
 * Arguments:
 * clientNum - client number of disconnected client.
 * */
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

/*
 * ChatFilter::ToggleDisableChat
 * Toggle disable/enable chat for given client number.
 * Arguments:
 * clientNum - client number of client to have chat allowing toggled.
 * Return values:
 * Returns true if chat is toggled, false otherwise.
 * chatAllowed - whether or not chat is allowed for client.
 * 
 * */
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

/*
 * ChatFilter::ToggleDisableTaunt
 * Toggle disable/enable taunts for given client number.
 * Arguments:
 * clientNum - client number of client to have taunt allowing toggled.
 * Return values:
 * Returns true if taunts are toggled, false otherwise.
 * tauntsAllowed - whether or not taunts are allowed for client.
 *
 * */
bool ChatFilter::ToggleDisableTaunt(int clientNum, bool & tauntsAllowed)
{
	size_t clientIndex = FindChatClient(clientNum);
	//just ignore non found client nums
	if (clientIndex != defaultChatClientIndex)
	{
		ChatFilterClientEntry & e = ChatClientEntries[clientIndex];
		e.SetTauntsAllowed(!e.GetTauntsAllowed());
		tauntsAllowed = e.GetTauntsAllowed();
		return true;
	}
	return false;
}

/*
 * ChatFilter::Init
 * Initialize chat filter lists, parse chat filter file (chatfilter.cfg)
 *
 * */
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

/*
 * ChatFilter::Shutdown
 * Shutdown chat filter lists, save to chat filter file (chatfilter.cfg)
 *
 * */
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
