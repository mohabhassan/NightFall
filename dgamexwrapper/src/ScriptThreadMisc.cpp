#include <wolfssl/wolfcrypt/md5.h>
#include "ScriptThread.h"
#include "g_misc.h"
#include "misc.h"
#include <SQLiteCpp/Database.h>
#include "CustomCvar.h"
#include <regex>
#include "g_json.h"
#include "sv_misc.h"
#include <time.h>


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

	/*
	cerSet.AddEventResponse(new Event(
		"getdate",
		EV_DEFAULT,
		"i",
		"zero",
		"Gets current date in format: dd.mm.yyyy",
		EV_RETURN
	),
		&ScriptThread::GetDateEvent);
	*/
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

	cerSet.AddEventResponse(new Event(
		"setproperty",
		EV_DEFAULT,
		"ss",
		"key value",
		"Sets local storage property",
		EV_RETURN
	),
		&ScriptThread::SetPropertyEvent);

	cerSet.AddEventResponse(new Event(
		"getproperty",
		EV_DEFAULT,
		"s",
		"key",
		"Gets local storage property",
		EV_RETURN
	),
		&ScriptThread::GetPropertyEvent);

	cerSet.AddEventResponse(new Event(
		"constarray",
		EV_DEFAULT,
		"e",
		"array",
		"Cast hashtable array to const array.",
		EV_RETURN
	),
		&ScriptThread::CastConstArrayEvent);

	cerSet.AddEventResponse(new Event(
		"regex_parse",
		EV_DEFAULT,
		"ssi",
		"pattern string whole_match",
		"Perform a regular expression match.",
		EV_RETURN
	),
		&ScriptThread::RegexParseEvent);

	cerSet.AddEventResponse(new Event(
		"json_parse",
		EV_DEFAULT,
		"s",
		"string",
		"Parse string to json.",
		EV_RETURN
	),
		&ScriptThread::JsonParseEvent);

	cerSet.AddEventResponse(new Event(
		"json_stringify",
		EV_DEFAULT,
		"e",
		"var",
		"Convert object to json string.",
		EV_RETURN
	),
		&ScriptThread::JsonStringifyEvent);
}



void ScriptThread::PlayerNetNameEvent(Event * ev)
{
	Entity *ent = NULL;
	str netname("");

	ent = (Entity*)ev->GetEntity(1);

	if (ent != NULL && ent->client != NULL)
	{
		netname = ent->client->pers.netname;
	}

	ev->AddString(netname);
}

void ScriptThread::StuffSrvEvent(Event*ev)
{
	if (ev->NumArgs() < 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for stuffsrv!\n");
		return;
	}

	str cmdStr;
	for (size_t i = 1; i <= ev->NumArgs(); i++)
	{
		cmdStr += ev->GetString(i);
		cmdStr += " ";
	}

	cmdStr -= 1;//remove last space

	gi.SendConsoleCommand(cmdStr.c_str());
}


void ScriptThread::ConprintfEvent(Event *ev)
{
	if (ev->NumArgs() != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for conprintf!\n");
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
		ip = GetIPFromClient(GetClientByClientNum(ent->client->ps.clientNum)).c_str();
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
		ping = ent->client->ps.ping;
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
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Entity number %d out of scope!\n", entnum);
	}
	else
	{
		ent = G_GetEntity(entnum);
		if (!ent)
		{
			gi.Printf(PATCH_NAME " SCRIPT ERROR: Entity not found!\n");
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
		gi.Printf(PATCH_NAME " SCRIPT ERROR: gettime: failed to create time string!\n");
	}
	else
	{
		ev->AddString(buff);
	}

}

void ScriptThread::GetTimeZoneEvent(Event *ev)
{
	long timediff_secs;
	_tzset();
	errno_t err = _get_timezone(&timediff_secs);
	if (err)
	{

		char errStr[128] = { 0 };
		strerror_s(errStr, err);
		gi.Printf(PATCH_NAME " SCRIPT ERROR: gettimezone failed to get time zone: %s!\n", errStr);
		return;
	}

	ev->AddInteger(-timediff_secs / 3600);
}
/*
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
*/
void ScriptThread::GetDateFormattedEvent(Event *ev)
{
	char buff[512] = {0};
	time_t rawtime;
	struct tm * timeinfo;

	if (ev->NumArgs() != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for getdate!\n");
		return;
	}

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (ev->GetValue(1).GetType() == VARIABLE_INTEGER)
	{
		strftime(buff, 512, "%d.%m.%Y", timeinfo);
	}
	else
	{
		strftime(buff, 512, ev->GetString(1).c_str(), timeinfo);
	}

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
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for md5string!\n");
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
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for md5file!\n");
		return;
	}
	filename = ev->GetString(1);
	err = fopen_s(&fp, filename.c_str(), "rb");
	if (err != 0)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: md5file: couldn't open file: %s error code: %i !\n", filename.c_str(), err);
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
		gi.Printf(PATCH_NAME " SCRIPT ERROR: md5file: couldn't load file: %s error: %s !\n", filename.c_str(), e.what());
		return;
	}

	buff[filelen] = '\0';


	bytesread = fread(buff, 1, filelen, fp);

	if (bytesread < filelen)
	{
		delete[] buff;
		fclose(fp); 
		gi.Printf(PATCH_NAME " SCRIPT ERROR: md5file: couldn't load file: %s error2: %i !\n", filename.c_str(), bytesread);
		return;
	}

	fclose(fp);

	wc_InitMd5(&md5);

	wc_Md5Update(&md5, (const unsigned char*)buff, filelen);

	wc_Md5Final(&md5, md5sum);


	for (int di = 0; di < MD5_DIGEST_SIZE; ++di)
		sprintf(md5Str + di * 2, "%02x", md5sum[di]);
	ev->AddString(md5Str);
	delete[] buff;
}

void ScriptThread::TypeofEvent(Event *ev)
{
	int numargs = ev->NumArgs();
	if (numargs != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for typeof!\n");
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
	ScriptVariable resultArray;
	ScriptVariable index, value;

	numArgs = ev->NumArgs();

	if (numArgs < 2 || numArgs > 6)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for traced!\n");
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

	index.setStringValue("allSolid");
	value.setIntValue(trace.allsolid);
	resultArray.setArrayAtRef(index, value);

	index.setStringValue("startSolid");
	value.setIntValue(trace.startsolid);
	resultArray.setArrayAtRef(index, value);

	index.setStringValue("fraction");
	value.setFloatValue(trace.fraction);
	resultArray.setArrayAtRef(index, value);

	index.setStringValue("endpos");
	value.setVectorValue(trace.endpos);
	resultArray.setArrayAtRef(index, value);

	index.setStringValue("surfaceFlags");
	value.setIntValue(trace.surfaceFlags);
	resultArray.setArrayAtRef(index, value);

	index.setStringValue("shaderNum");
	value.setIntValue(trace.shaderNum);
	resultArray.setArrayAtRef(index, value);

	index.setStringValue("contents");
	value.setIntValue(trace.contents);
	resultArray.setArrayAtRef(index, value);

	index.setStringValue("entityNum");
	value.setIntValue(trace.entityNum);
	resultArray.setArrayAtRef(index, value);

	index.setStringValue("location");
	value.setIntValue(trace.location);
	resultArray.setArrayAtRef(index, value);


	entity = G_GetEntity(trace.entityNum);

	// Have to use G_GetEntity instead otherwise it won't work
	if (entity != NULL) {
		index.setStringValue("entity");
		value.setListenerValue(entity);
		resultArray.setArrayAtRef(index, value);

	}

	ev->AddValue(resultArray);

}

void ScriptThread::SetPropertyEvent(Event * ev)
{
	str key;
	str value;
	int numArgs = 0;
	numArgs = ev->NumArgs();

	if (numArgs != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for setproperty!\n");
		return;
	}

	key = ev->GetString(1);

	if (key == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL key - setproperty!\n");
		ev->AddInteger(-1);
		return;
	}

	value = ev->GetString(2);

	if (value == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL value - setproperty!\n");
		ev->AddInteger(-2);
		return;
	}

	try
	{
		CustomCvar sv_store("sv_store", MAIN_PATH"/store.bin", CVAR_ARCHIVE);
		const char *createIfNotExists = "CREATE TABLE IF NOT EXISTS localStorage (key TEXT PRIMARY KEY, value TEXT)";


		SQLite::Database    db(sv_store.GetStringValue(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		db.exec(createIfNotExists);
		SQLite::Statement query(db, "INSERT OR REPLACE INTO localStorage (key,value) VALUES (?,?)");

		query.bind(1, key.c_str());
		query.bind(2, value.c_str());

		query.executeStep();

		ev->AddInteger(0);
	}
	catch (const std::exception& e)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Error in setproperty! : %s\n", e.what());
		ev->AddInteger(-3);
		return;
	}
}

void ScriptThread::GetPropertyEvent(Event * ev)
{
	str key;
	int numArgs = 0;
	numArgs = ev->NumArgs();
	if (numArgs != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for getproperty!\n");
		return;
	}


	key = ev->GetString(1);

	if (key == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL key - getproperty!\n");
		ev->AddInteger(-1);
		return;
	}


	try
	{
		CustomCvar sv_store("sv_store", MAIN_PATH"/store.bin", CVAR_ARCHIVE);
		SQLite::Database    db(sv_store.GetStringValue(), SQLite::OPEN_READONLY);
		SQLite::Statement query(db, "SELECT value FROM localStorage WHERE key=?");

		query.bind(1, key.c_str());

		if (query.executeStep()) //SQLITE_ROW
		{
			const char *value = query.getColumn(0);
			ev->AddString(value);
		}
		else //SQLITE_DONE
		{
			ev->AddInteger(0);
		}
	}
	catch (const std::exception& e)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Error in getproperty! : %s\n", e.what());
		ev->AddInteger(-3);
		return;
	}
}

void ScriptThread::CastConstArrayEvent(Event * ev)
{
	int numArgs = ev->NumArgs();
	if (numArgs != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for constarray!\n");
		return;
	}
	ScriptVariable &arr = ev->GetValue(1);
	if (arr.GetType() != VARIABLE_ARRAY)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Invalid argument type for constarray, must be an array. Given %s instead!\n", arr.GetTypeName());
		return;
	}
	ScriptVariable ret;
	if (ret.CastConstArray(arr))
	{
		ev->AddValue(ret);
	}
	else
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: constarray: array passed cannot be converted to const array!\n");
		ev->AddNil();
	}
}

void ScriptThread::RegexParseEvent(Event * ev)
{
	int numArgs = ev->NumArgs();
	if (numArgs != 3)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for regex_parse!\n");
		return;
	}
	
	regex r(ev->GetString(1).c_str());
	smatch sm;
	bool whole_match = ev->GetInteger(3);
	bool good;
	string sTarget = ev->GetString(2).c_str();
	if (whole_match)
	{
		good = regex_match(sTarget, sm, r);
	}
	else
	{
		good = regex_search(sTarget, sm, r);
	}
	ScriptVariable arr;
	ScriptVariable index, value;
	index.setStringValue("success");
	value.setIntValue(good ? 1 : 0);
	arr.setArrayAtRef(index, value);
	if (good)
	{
		ScriptVariable arr2;
		for (int i = 0; i < sm.size(); i++)
		{
			index.setIntValue(i);
			value.setStringValue(sm[i].str().c_str());
			arr2.setArrayAtRef(index, value);
		}
		index.setStringValue("matches");
		arr.setArrayAtRef(index, arr2);
	}
	ev->AddValue(arr);
}

void ScriptThread::JsonParseEvent(Event * ev)
{
	int numArgs = ev->NumArgs();
	if (numArgs != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for json_parse!\n");
		return;
	}
	
	string json_str = ev->GetString(1);
	json j;
	try
	{
		j = json::parse(json_str);
	}
	catch (json::parse_error& e)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: json_parse failed!\n");
		gi.Printf("info:\n");
		gi.Printf("\tmessage: %s\n", e.what());
		gi.Printf("\texception id: %d\n", e.id);
		gi.Printf("\tbyte position of error: %zu\n", e.byte);
		ev->AddNil();
		return;
	}
	ScriptVariable var;
	JsonToGameVar(j, var);
	ev->AddValue(var);
}

void ScriptThread::JsonStringifyEvent(Event * ev)
{
	int numArgs = ev->NumArgs();
	if (numArgs != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for json_stringify!\n");
		return;
	}
	ScriptVariable var = ev->GetValue(1);

	json j;
	GameVarToJson(var, j);
	ev->AddString(j.dump().c_str());
}
