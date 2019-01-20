#include "Player.h"
#include "g_misc.h"

ResponseDef<Player> *Player::Responses;

CustomEventResponseSet<Player> Player::cerSet{};

/* Offset updates:
 * x-> opm size
 * - : opm is larger
 * + : opm is smaller
 * 
 * BT Player sizeof is 2404 (x-192)
 * BT Sentient sizeof is 1504 (x+24) -> Fixed, no var added/removed
 * BT Animate sizeof is 940 (x+24) -> Fixed, 2 dimmies added
 * BT Entity sizeof is 652 (x+16) -> Fixed, no var added/removed.
 * BT SimpleEntity sizeof is 68 (x-4) -> Remove Listener.m_EndList (-4)
 * BT Listener sizeof is 20 (x-4) -> Remove m_EndList (-4)
 * BT Class sizeof is 8
 **/
Player::Player()
{
	sizeof(gentity_t);
}


Player::~Player()
{
}


void Player::Init()
{
	cerSet.AddEventResponse(new Event(
		"ptest",
		EV_DEFAULT,
		"IFSB",
		"test_int test_float test_string test_bool",
		"PLAYER TEST COMMAND"
	),
		&Player::Test);


	int rscount = cerSet.size()+1;
	size_t sz = sizeof(ResponseDef<Player>) * rscount;
	//Responses = reinterpret_cast<ResponseDef<Player>*>(gi.Malloc(sz));
	Responses = new ResponseDef<Player>[rscount];
	memset(Responses, 0, sz);

	//Could be added as a member func of cerSet.
	for (size_t i = 0; i < rscount-1; i++)
	{
		const std::string str = cerSet.GetResponseFuncAt(i).target_type().name();
		const std::string str2 = typeid(ResponseDef<Player>::response).name();
		Responses[i].event = cerSet.GetEventAt(i);
		Responses[i].response = *cerSet.GetResponseFuncAt(i).target<void(Player::*)(Event*)>();
	}
}

void Player::Shutdown()
{
	for (size_t i = 0; i < cerSet.size(); i++)
	{
		Event* ev = cerSet.GetEventAt(i);
		if (ev)
		{
			delete ev;
		}
	}
	//gi.Free(Responses);
	delete Responses;
}

void Player::Test(Event*ev)
{
	str strTat = ev->GetString(2);
	gentity_t *gent = G_GetEntityByClient(0);
	gi.centerprintf(gent, "Player Test success");
}
