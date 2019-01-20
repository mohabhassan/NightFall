#include "ScriptThread.h"
#include "g_misc.h"
#include "ihuddraw.h"

#include <string>
#include <regex>

Event *EV_ScriptThread_Test;


ResponseDef<ScriptThread> *ScriptThread::Responses;

CustomEventResponseSet<ScriptThread> ScriptThread::cerSet;

ScriptThread::ScriptThread()
{
}


ScriptThread::~ScriptThread()
{
}

void ScriptThread::Test(Event*ev)
{
	ScriptVariable& sv = ev->GetValue(0);

	str & strTat = sv.stringValue();

	ScriptVariable& sv1 = ev->GetValue(1);

	str & strTat1 = sv1.stringValue();

	ScriptVariable& sv2 = ev->GetValue(2);

	str & strTat2 = sv2.stringValue();

	ScriptVariable& sv3 = ev->GetValue(3);

	str & strTat3 = sv3.stringValue();

	ScriptVariable& sv4 = ev->GetValue(4);

	str & strTat4 = sv4.stringValue();

	gentity_t *gent = G_GetEntityByClient(0);
	gi.centerprintf(gent, "ScriptThread Test success");
}


void ScriptThread::Init()
{
	cerSet.AddEventResponse(new Event(
		"stest",
		EV_DEFAULT,
		"IFSB",
		"test_int test_float test_string test_bool",
		"SCRIPTTHREAD TEST COMMAND"
	),
		&ScriptThread::Test);


	cerSet.AddEventResponse(new Event(
		"stuffsrv",
		EV_DEFAULT,
		"s",
		"command",
		"Sends command to server"
	),
		&ScriptThread::StuffSrvEvent);

	cerSet.AddEventResponse(new Event(
		"netname",
		EV_DEFAULT,
		"e",
		"player",
		"Gets player's name",
		EV_RETURN
	),
		&ScriptThread::PlayerNetNameEvent);

	cerSet.AddEventResponse(new Event(
		"getip",
		EV_DEFAULT,
		"e",
		"player",
		"Gets player's ip",
		EV_RETURN
	),
		&ScriptThread::PlayerGetIpEvent);

	cerSet.AddEventResponse(new Event(
		"getping",
		EV_DEFAULT,
		"e",
		"player",
		"Gets player's ping",
		EV_RETURN
	),
		&ScriptThread::PlayerGetPingEvent);

	cerSet.AddEventResponse(new Event(
		"getclientnum",
		EV_DEFAULT,
		"e",
		"player",
		"Gets player's client number",
		EV_RETURN
	),
		&ScriptThread::PlayerGetClientNumEvent);

	cerSet.AddEventResponse(new Event(
		"getentity",
		EV_DEFAULT,
		"i",
		"entnum",
		"returns entity with given entnum",
		EV_RETURN
	),
		&ScriptThread::GetEntityEvent);

	cerSet.AddEventResponse(new Event(
		"ihuddraw_align",
		EV_DEFAULT,
		"eiss",
		"player index h_align v_align",
		"Sets the alignment of a huddraw element for given player."
	),
		&ScriptThread::iHudDrawAlignEvent);

	cerSet.AddEventResponse(new Event(
		"ihuddraw_alpha",
		EV_DEFAULT,
		"eif",
		"player index alpha",
		"Sets the alpha(transparency) of a huddraw element for given player."
	),
		&ScriptThread::iHudDrawAlphaEvent);

	cerSet.AddEventResponse(new Event(
		"ihuddraw_color",
		EV_DEFAULT,
		"eifff",
		"player index reg green blue",
		"Sets the color(red,green,blue) of a huddraw element for given player."
	),
		&ScriptThread::iHudDrawColorEvent);

	cerSet.AddEventResponse(new Event(
		"ihuddraw_font",
		EV_DEFAULT,
		"eis",
		"player index font",
		"Sets the font of a string of a huddraw element for given player."
	),
		&ScriptThread::iHudDrawFontEvent);


	cerSet.AddEventResponse(new Event(
		"ihuddraw_rect",
		EV_DEFAULT,
		"eiiiii",
		"player index x y width height",
		"Sets the rect(position, area) of a huddraw element for given player."
	),
		&ScriptThread::iHudDrawRectEvent);


	cerSet.AddEventResponse(new Event(
		"ihuddraw_shader",
		EV_DEFAULT,
		"eis",
		"player index shader",
		"Sets the shader of a huddraw element for given player."
	),
		&ScriptThread::iHudDrawShaderEvent);


	cerSet.AddEventResponse(new Event(
		"ihuddraw_string",
		EV_DEFAULT,
		"eis",
		"player index string",
		"Sets the string of a huddraw element for given player."
	),
		&ScriptThread::iHudDrawStringEvent);


	cerSet.AddEventResponse(new Event(
		"ihuddraw_virtualsize",
		EV_DEFAULT,
		"eii",
		"player index virtualsize",
		"Enables/disables using huddraw element virtual resolution for a player."
	),
		&ScriptThread::iHudDrawVirtualSizeEvent);


	int rscount = cerSet.size() + 1;
	size_t sz = sizeof(ResponseDef<ScriptThread>) * rscount;
	//Responses = reinterpret_cast<ResponseDef<ScriptThread>*>(gi.Malloc(sz));
	Responses = new ResponseDef<ScriptThread>[rscount];
	memset(Responses, 0, sz);

	//Could be added as a member func of cerSet.
	for (size_t i = 0; i < rscount - 1; i++)
	{
		const std::string str = cerSet.GetResponseFuncAt(i).target_type().name();
		const std::string str2 = typeid(ResponseDef<ScriptThread>::response).name();
		Responses[i].event = cerSet.GetEventAt(i);
		Responses[i].response = *cerSet.GetResponseFuncAt(i).target<void(ScriptThread::*)(Event*)>();
	}
}

void ScriptThread::Shutdown()
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


void ScriptThread::PlayerNetNameEvent(Event * ev)
{
	Entity *ent = NULL;

	ent = (Entity*)ev->GetEntity(1);

	if (ent == NULL || ent->client == NULL)
	{
		ev->AddString("");
		return;
	}

	ev->AddString(ent->client->pers.netname);
}

void ScriptThread::StuffSrvEvent(Event*ev)
{
	gi.SendConsoleCommand(ev->GetString(1));
}


void ScriptThread::PlayerGetIpEvent(Event * ev)
{
	using namespace std;
	Entity *ent = NULL;

	ent = (Entity*)ev->GetEntity(1);

	if (ent == NULL || ent->client == NULL)
	{
		ev->AddString("");
		return;
	}
	string uinfo = ent->client->pers.userinfo;
	string ip = "";
	smatch m;
	regex e(R"(\\ip\\(\S+?)\:(\d+)\\)");//matches ip and port separately
	if (regex_search(uinfo, m, e))
	{
		ip = m[1].str() + ":" + m[2].str();//m[0] is whole match.
	}

	ev->AddString(ip.c_str());
}


void ScriptThread::PlayerGetPingEvent(Event * ev)
{
	Entity *ent = NULL;

	ent = (Entity*)ev->GetEntity(1);

	if (ent == NULL || ent->client == NULL)
	{
		ev->AddString("");
		return;
	}

	ev->AddString(ent->client->pers.netname);
}


void ScriptThread::PlayerGetClientNumEvent(Event * ev)
{
	Entity *ent = NULL;

	ent = (Entity*)ev->GetEntity(1);

	if (ent == NULL || ent->client == NULL)
	{
		ev->AddString("");
		return;
	}

	ev->AddString(ent->client->pers.netname);
}

void ScriptThread::GetEntityEvent(Event *ev)
{

	int entnum = -1;
	Entity *ent = NULL;

	entnum = ev->GetInteger(1);

	if (entnum < 0 || entnum > globals->max_entities)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Entity number %d out of scope!\n", entnum);
	}
	else
	{
		ent = G_GetEntity(entnum);
		if (ent)
		{
			gi.Printf("newpatchname SCRIPT ERROR: Entity not found!\n");
		}
		else
		{
			ev->AddEntity(ent);
		}
	}

}

void ScriptThread::iHudDrawAlignEvent(Event *ev)
{
	Entity *player;
	int index, h_align = -1, v_align = -1;
	str h_alignstr, v_alignstr;
	int argnum = ev->NumArgs();

	if (argnum != 4)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for ihuddraw_align!\n");
		return;
	}

	player = ev->GetEntity(1);
	index = ev->GetInteger(2);
	h_alignstr = ev->GetString(3);
	v_alignstr = ev->GetString(4);

	if (index < 0 || index > 255)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_align: invalid index %d\n", index);
		return;
	}
	if (!player)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_align: invalid player!\n");
		return;
	}
	h_alignstr.tolower();
	v_alignstr.tolower();
	// 0 - left		
	// 1 - center	 - horizontalAlign
	// 2 - right
	switch (h_alignstr[0])
	{
	case 'l':
		h_align = 0;
		break;
	case 'c':
		h_align = 1;
		break;
	case 'r':
		h_align = 2;
		break;
	default:
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_align: invalid h_align value\n", h_alignstr);
		return;
		break;
	}
	// 0 - top		
	// 1 - center	 - verticalAlign
	// 2 - bottom	
	switch (v_alignstr[0])
	{
	case 't':
		v_align = 0;
		break;
	case 'c':
		v_align = 1;
		break;
	case 'b':
		v_align = 2;
		break;
	default:
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_align: invalid v_align value\n", v_alignstr);
		return;
		break;
	}

	iHudDrawAlign(player->client->ps.clientNum, index, h_align, v_align);
}

void ScriptThread::iHudDrawAlphaEvent(Event *ev)
{
	Entity *player;
	int index;
	float alpha = -1;
	int argnum = ev->NumArgs();

	if (argnum != 3)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for ihuddraw_alpha!\n");
		return;
	}

	player = ev->GetEntity(1);

	if (!player)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_alpha: invalid player!\n");
		return;
	}

	index = ev->GetInteger(2);

	if (index < 0 || index > 255)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_alpha: invalid index %d!\n", index);
		return;
	}

	alpha = ev->GetFloat(3);

	if (alpha < 0 || alpha > 1)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_alpha: invalid alpha %f!\n", alpha);
		return;
	}

	iHudDrawAlpha(player->client->ps.clientNum, index, alpha);
}


void ScriptThread::iHudDrawColorEvent(Event *ev)
{
	Entity *player;
	int index;
	float red, green, blue;
	int argnum = ev->NumArgs();

	if (argnum != 5)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for ihuddraw_color!\n");
		return;
	}

	player = ev->GetEntity(1);

	if (!player)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_color: invalid player!\n");
		return;
	}

	index = ev->GetInteger(2);

	if (index < 0 || index > 255)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_color: invalid index %d!\n", index);
		return;
	}

	red = ev->GetFloat(3);

	if (red < 0 || red > 1)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_color: invalid red %f!\n", red);
		return;
	}

	green = ev->GetFloat(4);

	if (green < 0 || green > 1)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_color: invalid green %f!\n", green);
		return;
	}

	blue = ev->GetFloat(5);

	if (blue < 0 || blue > 1)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_color: invalid blue %f!\n", blue);
		return;
	}

	iHudDrawColor(player->client->ps.clientNum, index, red, green, blue);
}


void ScriptThread::iHudDrawFontEvent(Event *ev)
{
	Entity *player;
	int index;
	str font;
	int argnum = ev->NumArgs();

	if (argnum != 3)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for ihuddraw_font!\n");
		return;
	}

	player = ev->GetEntity(1);

	if (!player)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_font: invalid player!\n");
		return;
	}

	index = ev->GetInteger(2);

	if (index < 0 || index > 255)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_font: invalid index %d!\n", index);
		return;
	}

	font = ev->GetString(3);

	iHudDrawFont(player->client->ps.clientNum, index, font);
}

void ScriptThread::iHudDrawRectEvent(Event *ev)
{
	Entity *player;
	int index;
	int x, y, w, h;//x, y, width, height
	int argnum = ev->NumArgs();

	if (argnum != 6)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for ihuddraw_rect!\n");
		return;
	}

	player = ev->GetEntity(1);

	if (!player)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_rect: invalid player!\n");
		return;
	}

	index = ev->GetInteger(2);

	if (index < 0 || index > 255)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_rect: invalid index %d!\n", index);
		return;
	}

	x = ev->GetInteger(3);
	y = ev->GetInteger(4);
	w = ev->GetInteger(5);
	h = ev->GetInteger(6);


	iHudDrawRect(player->client->ps.clientNum, index, x, y, w, h);
}



void ScriptThread::iHudDrawShaderEvent(Event *ev)
{
	Entity *player;
	int index;
	str shader;
	int argnum = ev->NumArgs();

	if (argnum != 3)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for ihuddraw_shader!\n");
		return;
	}

	player = ev->GetEntity(1);

	if (!player)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_shader: invalid player!\n");
		return;
	}

	index = ev->GetInteger(2);

	if (index < 0 || index > 255)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_shader: invalid index %d!\n", index);
		return;
	}

	shader = ev->GetString(3);

	iHudDrawShader(player->client->ps.clientNum, index, shader);
}


void ScriptThread::iHudDrawStringEvent(Event *ev)
{
	Entity *player;
	int index;
	str text;
	int argnum = ev->NumArgs();

	if (argnum != 3)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for ihuddraw_string!\n");
		return;
	}

	player = ev->GetEntity(1);

	if (!player)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_string: invalid player!\n");
		return;
	}

	index = ev->GetInteger(2);

	if (index < 0 || index > 255)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_string: invalid index %d!\n", index);
		return;
	}

	text = ev->GetString(3);

	iHudDrawString(player->client->ps.clientNum, index, text);
}



void ScriptThread::iHudDrawVirtualSizeEvent(Event *ev)
{
	Entity *player;
	int index;
	int virtualsize;
	int argnum = ev->NumArgs();

	if (argnum != 3)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for ihuddraw_virtualsize!\n");
		return;
	}

	player = ev->GetEntity(1);

	if (!player)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_virtualsize: invalid player!\n");
		return;
	}

	index = ev->GetInteger(2);

	if (index < 0 || index > 255)
	{
		gi.Printf("newpatchname SCRIPT ERROR: ihuddraw_virtualsize: invalid index %d!\n", index);
		return;
	}

	virtualsize = ev->GetInteger(3);

	iHudDrawVirtualSize(player->client->ps.clientNum, index, virtualsize);
}