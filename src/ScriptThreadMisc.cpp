#include <wolfssl/wolfcrypt/md5.h>
#include "ScriptThread.h"
#include "g_misc.h"
#include "misc.h"
using byte = unsigned char;
//std::unordered_map<std::string, std::string > local_storage;

void ScriptThread::MiscInit()
{
	////////////////////////////////////////
	//Player
	////////////////////////////////////////
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

	////////////////////////////////////////
	//Date/Time
	////////////////////////////////////////
	cerSet.AddEventResponse(new Event(
		"gettime",
		EV_DEFAULT,
		"i",
		"zero",
		"Gets current time in format: H:M:S.",
		EV_RETURN
	),
		&ScriptThread::GetTimeEvent);

	cerSet.AddEventResponse(new Event(
		"gettimezone",
		EV_DEFAULT,
		"i",
		"zero",
		"Gets current time zone.",
		EV_RETURN
	),
		&ScriptThread::GetTimeZoneEvent);

	cerSet.AddEventResponse(new Event(
		"getdate",
		EV_DEFAULT,
		"i",
		"zero",
		"Gets current date in format: dd.mm.yyyy",
		EV_RETURN
	),
		&ScriptThread::GetDateEvent);

	cerSet.AddEventResponse(new Event(
		"getdate",
		EV_DEFAULT,
		"s",
		"format",
		"Gets current date in format given as parameter.",
		EV_RETURN
	),
		&ScriptThread::GetDateFormattedEvent);

	////////////////////////////////////////
	//Misc
	////////////////////////////////////////
	cerSet.AddEventResponse(new Event(
		"stuffsrv",
		EV_DEFAULT,
		"s",
		"command",
		"Sends command to server"
	),
		&ScriptThread::StuffSrvEvent);

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
		"conprintf",
		EV_DEFAULT,
		"s",
		"text",
		"Prints text to a console."
	),
		&ScriptThread::ConprintfEvent);

	cerSet.AddEventResponse(new Event(
		"md5string",
		EV_DEFAULT,
		"s",
		"text",
		"Generates MD5 checksum of text.",
		EV_RETURN
	),
		&ScriptThread::Md5Event);

	cerSet.AddEventResponse(new Event(
		"md5file",
		EV_DEFAULT,
		"s",
		"filename",
		"Generates MD5 checksum of file.",
		EV_RETURN
	),
		&ScriptThread::Md5fileEvent);

	cerSet.AddEventResponse(new Event(
		"typeof",
		EV_DEFAULT,
		"s",
		"filename",
		"Gets the type of variable.",
		EV_RETURN
	),
		&ScriptThread::TypeofEvent);

	cerSet.AddEventResponse(new Event(
		"traced",
		EV_DEFAULT,
		"vvIVVI",
		"start end pass_entities mins maxs mask",
		"Performs a Trace Line from the start to the end, returns the array with detailed results",
		EV_RETURN
	),
		&ScriptThread::TraceDetailsEvent);

}



void ScriptThread::PlayerNetNameEvent(Event * ev)
{
	Entity *ent = NULL;
	str netname = "";

	ent = (Entity*)ev->GetEntity(1);

	if (ent != NULL && ent->client != NULL)
	{
		netname = ent->client->pers.netname;
	}

	ev->AddString(netname);
}

void ScriptThread::StuffSrvEvent(Event*ev)
{
	gi.SendConsoleCommand(ev->GetString(1));
}


void ScriptThread::ConprintfEvent(Event *ev)
{
	if (ev->NumArgs() != 1)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for conprintf!\n");
	}
	else
	{
		gi.Printf(ev->GetString(1));
	}
}

void ScriptThread::PlayerGetIpEvent(Event * ev)
{
	//using namespace std;

	str ip = "";
	Entity *ent = NULL;

	ent = (Entity*)ev->GetEntity(1);

	if (ent != NULL && ent->client != NULL)
	{
		ip = Info_ValueForKey(ent->client->pers.userinfo, "ip");
	}
	//string uinfo = ent->client->pers.userinfo;
	//string ip = "";
	//smatch m;
	//regex e(R"(\\ip\\(\S+?)\:(\d+)\\)");//matches ip and port separately
	//if (regex_search(uinfo, m, e))
	//{
	//	ip = m[1].str() + ":" + m[2].str();//m[0] is whole match.
	//}

	ev->AddString(ip);
}


void ScriptThread::PlayerGetPingEvent(Event * ev)
{
	Entity *ent = NULL;
	str ping = "";

	ent = (Entity*)ev->GetEntity(1);

	if (ent != NULL && ent->client != NULL)
	{
		ping = ent->client->ping;
	}

	ev->AddString(ping);
}


void ScriptThread::PlayerGetClientNumEvent(Event * ev)
{
	Entity *ent = NULL;
	str clientnum = "";

	ent = (Entity*)ev->GetEntity(1);

	if (ent != NULL && ent->client != NULL)
	{
		clientnum = ent->client->ps.clientNum;
	}

	ev->AddString(clientnum);
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
		if (!ent)
		{
			gi.Printf("newpatchname SCRIPT ERROR: Entity not found!\n");
		}
		else
		{
			ev->AddEntity(ent);
		}
	}

}

void ScriptThread::GetTimeEvent(Event *ev)
{
	char buff[1024] = { 0 };

	time_t rawtime;
	struct tm * timeinfo;


	time(&rawtime);
	timeinfo = localtime(&rawtime);


	if (strftime(buff, 1024, "%H:%M:%S", timeinfo) == NULL)
	{
		gi.Printf("newpatchname SCRIPT ERROR: gettime: failed to create time string!\n");
	}
	else
	{
		ev->AddString(buff);
	}

}

void ScriptThread::GetTimeZoneEvent(Event *ev)
{
	int gmttime;
	int local;

	time_t rawtime;
	struct tm * timeinfo, *ptm;

	int timediff;
	int tmp;

	tmp = ev->GetInteger(1);

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	local = timeinfo->tm_hour;

	ptm = gmtime(&rawtime);

	gmttime = ptm->tm_hour;

	timediff = local - gmttime;

	ev->AddInteger(timediff);
}

void ScriptThread::GetDateEvent(Event *ev)
{
	char buff[1024];
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buff, 1024, "%d.%m.%Y", timeinfo);

	ev->AddString(buff);
}

void ScriptThread::GetDateFormattedEvent(Event *ev)
{
	char buff[1024] = {0};
	time_t rawtime;
	struct tm * timeinfo;

	if (ev->NumArgs() != 1)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for getdate!\n");
		return;
	}

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buff, 1024, ev->GetString(1).c_str(), timeinfo);

	ev->AddString(buff);
}

void ScriptThread::Md5Event(Event *ev)
{
	unsigned char md5sum[MD5_DIGEST_SIZE];
	char md5Str[MD5_DIGEST_SIZE * 2 + 1] = { 0 };
	str text;
	Md5 md5;

	if (ev->NumArgs() != 1)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for md5string!\n");
		return;
	}
	text = ev->GetString(1);
	wc_InitMd5(&md5);

	wc_Md5Update(&md5, (const unsigned char*)text.c_str(), text.length());

	wc_Md5Final(&md5, md5sum);


	for (int di = 0; di < MD5_DIGEST_SIZE; ++di)
		sprintf(md5Str + di * 2, "%02x", md5sum[di]);
	ev->AddString(md5Str);
}

void ScriptThread::Md5fileEvent(Event *ev)
{
	unsigned char md5sum[MD5_DIGEST_SIZE];
	char md5Str[MD5_DIGEST_SIZE * 2 + 1] = { 0 };
	char *buff;
	long filelen = 0, bytesread = 0;
	errno_t err;
	FILE *fp;
	str filename;
	Md5 md5;

	if (ev->NumArgs() != 1)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for md5file!\n");
		return;
	}
	filename = ev->GetString(1);
	err = fopen_s(&fp, filename.c_str(), "rb");
	if (err != 0)
	{
		gi.Printf("newpatchname SCRIPT ERROR: md5file: couldn't open file: %s error code: %i !\n", filename.c_str(), err);
		return;
	}

	fseek(fp, 0, SEEK_END);
	filelen = ftell(fp);
	rewind(fp);

	try
	{
		buff = new char[filelen+1];
	}
	catch (std::bad_alloc &e)
	{
		gi.Printf("newpatchname SCRIPT ERROR: md5file: couldn't load file: %s error: %s !\n", filename.c_str(), e.what());
		return;
	}

	buff[filelen] = '\0';


	bytesread = fread(buff, 1, filelen, fp);

	if (bytesread < filelen)
	{
		delete[] buff;
		fclose(fp); 
		gi.Printf("newpatchname SCRIPT ERROR: md5file: couldn't load file: %s error2: %i !\n", filename.c_str(), bytesread);
		return;
	}

	fclose(fp);

	wc_InitMd5(&md5);

	wc_Md5Update(&md5, (const unsigned char*)buff, filelen);

	wc_Md5Final(&md5, md5sum);


	for (int di = 0; di < MD5_DIGEST_SIZE; ++di)
		sprintf(md5Str + di * 2, "%02x", md5sum[di]);
	ev->AddString(md5Str);
}

void ScriptThread::TypeofEvent(Event *ev)
{
	int numargs = ev->NumArgs();
	if (numargs != 1)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for typeof!\n");
		return;
	}
	ScriptVariable& var = ev->GetValue(1);

	ev->AddString(var.GetTypeName());
}


void ScriptThread::TraceDetailsEvent(Event *ev)
{
	int numArgs = 0;
	int pass_entity = 0;
	int mask = 0x2000B01;
	trace_t trace;
	Vector vecStart, vecEnd, vecMins, vecMaxs;
	Entity *entity;

	ScriptVariable array;
	ScriptVariable allSolidIndex, allSolidValue;
	ScriptVariable startSolidIndex, startSolidValue;
	ScriptVariable fractionIndex, fractionValue;
	ScriptVariable endPosIndex, endPosValue;
	ScriptVariable surfaceFlagsIndex, surfaceFlagsValue;
	ScriptVariable shaderNumIndex, shaderNumValue;
	ScriptVariable contentsIndex, contentsValue;
	ScriptVariable entityNumIndex, entityNumValue;
	ScriptVariable locationIndex, locationValue;
	ScriptVariable entityIndex, entityValue;

	numArgs = ev->NumArgs();

	if (numArgs < 2 || numArgs > 6)
	{
		gi.Printf("newpatchname SCRIPT ERROR: Wrong number of arguments for traced!\n");
		return;
	}

	vecStart = ev->GetVector(1);
	vecEnd = ev->GetVector(2);

	if (numArgs >= 3) {
		pass_entity = ev->GetInteger(3);
	}

	if (numArgs >= 4) {
		vecMins = ev->GetVector(4);
	}

	if (numArgs >= 5) {
		vecMaxs = ev->GetVector(5);
	}

	if (numArgs == 6) {
		mask = ev->GetInteger(6);
	}

	gi.Trace(&trace, vecStart, vecMins, vecMaxs, vecEnd, pass_entity, mask, 0, 0);

	allSolidIndex.setStringValue("allSolid");
	startSolidIndex.setStringValue("startSolid");
	fractionIndex.setStringValue("fraction");
	endPosIndex.setStringValue("endpos");
	surfaceFlagsIndex.setStringValue("surfaceFlags");
	shaderNumIndex.setStringValue("shaderNum");
	contentsIndex.setStringValue("contents");
	entityNumIndex.setStringValue("entityNum");
	locationIndex.setStringValue("location");
	entityIndex.setStringValue("entity");

	allSolidValue.setIntValue(trace.allsolid);
	startSolidValue.setIntValue(trace.startsolid);
	fractionValue.setFloatValue(trace.fraction);
	endPosValue.setVectorValue(trace.endpos);
	surfaceFlagsValue.setIntValue(trace.surfaceFlags);
	shaderNumValue.setIntValue(trace.shaderNum);
	contentsValue.setIntValue(trace.contents);
	entityNumValue.setIntValue(trace.entityNum);
	locationValue.setIntValue(trace.location);

	entity = G_GetEntity(trace.entityNum);

	// Have to use G_GetEntity instead otherwise it won't work
	if (entity != NULL) {
		entityValue.setListenerValue(entity);
	}

	array.setArrayAtRef(allSolidIndex, allSolidValue);
	array.setArrayAtRef(startSolidIndex, startSolidValue);
	array.setArrayAtRef(fractionIndex, fractionValue);
	array.setArrayAtRef(endPosIndex, endPosValue);
	array.setArrayAtRef(surfaceFlagsIndex, surfaceFlagsValue);
	array.setArrayAtRef(shaderNumIndex, shaderNumValue);
	array.setArrayAtRef(contentsIndex, contentsValue);
	array.setArrayAtRef(entityNumIndex, entityNumValue);
	array.setArrayAtRef(locationIndex, locationValue);
	array.setArrayAtRef(entityIndex, entityValue);

	ev->AddValue(array);

}
