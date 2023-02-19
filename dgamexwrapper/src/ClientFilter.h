#pragma once
#include <list>
#include "CustomCvar.h"
using namespace std;
class ClientFilter
{
	int client_num;
	bool connected;
	int last_ping_check_time;
	int ping_exceeded_count;
	static list<ClientFilter> clients;


	list<ClientFilter>::iterator findClientIndex(int cnum);
	ClientFilter& GetClient(int cnum);

	int GetLastPingCheckTime();
	void SetLastPingCheckTime(int ms);
	int GetPingExceededCOunt();
	void SetPingExceededCOunt(int ms);
public:

	ClientFilter();
	ClientFilter(int cnum, bool conn);

	void ClientConnected(int cnum, int ms);
	void ClientDisconnected(int cnum);
	
	bool CheckPingKick(int cnum, int ping, gentity_t* ent);


};

