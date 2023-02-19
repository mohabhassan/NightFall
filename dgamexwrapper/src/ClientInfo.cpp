#include "ClientFilter.h"

list<ClientFilter> ClientFilter::clients;

list<ClientFilter>::iterator ClientFilter::findClientIndex(int cnum)
{
	list<ClientFilter>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		if (it->client_num == cnum)
		{
			return it;
		}
	}
	return it;
}

ClientFilter::ClientFilter(int cnum, bool conn)
{
	connected = conn;
	client_num = cnum;
	last_ping_check_time = 0;
	ping_exceeded_count = 0;
}

ClientFilter& ClientFilter::ClientConnected(int cnum)
{
	list<ClientFilter>::iterator it = findClientIndex(cnum);
	if (it == clients.end())
	{
		clients.emplace_back(cnum, false);
		it = clients.end();
		it--;
	}

	return *it;
}

void ClientFilter::ClientDisconnected(int cnum)
{
	list<ClientFilter>::iterator it = findClientIndex(cnum);
	if (it != clients.end())
	{
		clients.erase(it);
	}
}

ClientFilter& ClientFilter::GetClient(int cnum)
{
	list<ClientFilter>::iterator it = findClientIndex(cnum);
	return *it;
}

ClientFilter::CheckPingKick(int cnum)
{
}

int ClientFilter::GetLastPingCheckTime()
{
	return last_ping_check_time;
}

void ClientFilter::SetLastPingCheckTime(int ms)
{
	last_ping_check_time = ms;
}

int ClientFilter::GetPingExceededCOunt()
{
	return ping_exceeded_count;
}

void ClientFilter::SetPingExceededCOunt(int ms)
{
	ping_exceeded_count = ms;
}
