#pragma once
#include "Event.h"
#include "ClassDef.h"
#include "Listener.h"
#include "CustomEventResponseSet.h"
class ScriptThread : public Listener
{
public:
	ScriptThread();
	~ScriptThread();
	static ResponseDef<ScriptThread>	*Responses;
	static CustomEventResponseSet<ScriptThread> cerSet;
	static vector<FILE*> scriptFiles;

	static void Init();
	static void Shutdown();

	static void		iHudDrawInit();

	void		iHudDrawAlignEvent(Event * ev);
	void		iHudDrawAlphaEvent(Event * ev);
	void		iHudDrawColorEvent(Event * ev);
	void		iHudDrawFontEvent(Event *ev);
	void		iHudDrawRectEvent(Event *ev);
	void		iHudDrawShaderEvent(Event *ev);
	void		iHudDrawStringEvent(Event *ev);
	void		iHudDrawVirtualSizeEvent(Event *ev);
	
	void		Test(Event*ev);

	static void		FileSystemInit();

	void		FOpenEvent(Event * ev);
	void		FCloseEvent(Event * ev);
	void		FEOFEvent(Event * ev);
	void		FSeekEvent(Event * ev);
	void		FTellEvent(Event * ev);
	void		FRewindEvent(Event * ev);
	void		FPutcEvent(Event * ev);
	void		FPutsEvent(Event * ev);
	void		FGetcEvent(Event * ev);
	void		FGetsEvent(Event * ev);
	void		FErrorEvent(Event * ev);
	void		FFlushEvent(Event * ev);
	void		FExistsEvent(Event * ev);
	void		FReadAllEvent(Event * ev);
	void		FSaveAllEvent(Event * ev);
	void		FRemoveEvent(Event * ev);
	void		FRenameEvent(Event * ev);
	void		FCopyEvent(Event * ev);
	void		FReadPakEvent(Event * ev);
	void		FListEvent(Event * ev);

	static void		MathsInit();

	void		MSinEvent(Event * ev);
	void		MCosEvent(Event * ev);
	void		MTanEvent(Event * ev);
	void		MASinEvent(Event * ev);
	void		MACosEvent(Event * ev);
	void		MATanEvent(Event * ev);
	void		MATan2Event(Event * ev);
	void		MSinhEvent(Event * ev);
	void		MCoshEvent(Event * ev);
	void		MTanhEvent(Event * ev);
	void		MExpEvent(Event * ev);
	void		MFrexpEvent(Event * ev);
	void		MLdexpEvent(Event * ev);
	void		MLogEvent(Event * ev);
	void		MLog10Event(Event * ev);
	void		MModfEvent(Event * ev);
	void		MPowEvent(Event * ev);
	void		MSqrtEvent(Event * ev);
	void		MCeilEvent(Event * ev);
	void		MFloorEvent(Event * ev);
	void		MFmodEvent(Event * ev);

	static void		MiscInit();

	void		PlayerNetNameEvent(Event * ev);
	void		StuffSrvEvent(Event * ev);
	void		ConprintfEvent(Event * ev);
	void		PlayerGetIpEvent(Event * ev);
	void		PlayerGetPingEvent(Event * ev);
	void		PlayerGetClientNumEvent(Event * ev);
	void		GetEntityEvent(Event * ev);
	void		GetTimeEvent(Event * ev);
	void		GetTimeZoneEvent(Event * ev);
	void		GetDateEvent(Event * ev);
	void		GetDateFormattedEvent(Event * ev);
	void		Md5Event(Event * ev);
	void		Md5fileEvent(Event * ev);
	void		TypeofEvent(Event * ev);
	void		TraceDetailsEvent(Event * ev);

	static void		ScriptedEventsInit();

	void		RegisterevEvent(Event * ev);
	void		UnregisterevEvent(Event * ev);
};

