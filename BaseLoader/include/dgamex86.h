#pragma once


// windows and linux common includes
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include "vector.h"
#include "str.h"
#include "Version.h"
#include "GameVersion.h"
#include <variant>

#if defined(_WIN32) || defined(__MINGW32__)
	//  windows-only
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <windows.h>	//Windows header
	#include <process.h>
	#include <shlwapi.h>
	#define stristr StrStrIA
	#define NF_LIBCURL_CABUNDLENAME "cacert.pem"
	
#else
	//  linux-only
	#include <dlfcn.h>		//*Nix header
	#include <malloc.h>
	#include <signal.h>
	#include <sys/types.h>
	#include <execinfo.h>
	#include <sys/ucontext.h>

	typedef unsigned int	DWORD;
	typedef unsigned char	BYTE;
	#define stricmp strcasecmp
	#define stristr strcasestr
#endif

#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <signal.h>
//#include <pthread.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <errno.h>
//#include <netdb.h>
//#include <execinfo.h>
//#include <ucontext.h>

#include <filesystem>
namespace fs = std::filesystem;

typedef unsigned long solid_t;

#define	CVAR_ARCHIVE			1
#define	CVAR_USERINFO			2
#define	CVAR_SERVERINFO			4
#define	CVAR_SYSTEMINFO			8
#define	CVAR_INIT				16
#define	CVAR_LATCH				32
#define	CVAR_ROM				64
#define	CVAR_USERCREATED		128
#define	CVAR_TEMP				256
#define CVAR_CHEAT				512

#define MAX_MSGLEN				49152

#define PACKET_BACKUP			32

#define	SVF_NOCLIENT			0x00000001
#define SVF_CLIENTMASK			0x00000002
#define SVF_BOT					0x00000008
#define	SVF_BROADCAST			0x00000020
#define	SVF_PORTAL				0x00000040
#define	SVF_USE_CURRENT_ORIGIN	0x00000080
#define SVF_SINGLECLIENT		0x00000100
#define SVF_NOSERVERINFO		0x00000200
#define SVF_CAPSULE				0x00000400
#define SVF_NOTSINGLECLIENT		0x00000800

#define	RF_THIRD_PERSON			( 1<<0 )
#define	RF_FIRST_PERSON			( 1<<1 )
#define RF_DEPTHHACK			( 1<<2 )
#define RF_VIEWLENSFLARE		( 1<<3 )
#define	RF_FRAMELERP			( 1<<4 )
#define	RF_BEAM					( 1<<5 )
#define RF_DONTDRAW				( 1<<7 )
#define RF_LENSFLARE			( 1<<8 )
#define RF_EXTRALIGHT			( 1<<9 )
#define RF_DETAIL				( 1<<10 )
#define RF_SHADOW				( 1<<11 )
#define	RF_PORTALSURFACE		( 1<<12 )
#define	RF_SKYORIGIN			( 1<<13 )
#define	RF_SKYENTITY			( 1<<14 )
#define	RF_LIGHTOFFSET			( 1<<15 )
#define	RF_CUSTOMSHADERPASS		( 1<<16 )
#define	RF_MINLIGHT				( 1<<17 )
#define	RF_FULLBRIGHT			( 1<<18 )
#define RF_LIGHTINGORIGIN		( 1<<19 )
#define	RF_SHADOWPLANE			( 1<<20 )
#define	RF_WRAPFRAMES			( 1<<21 )
#define RF_PORTALENTITY			( 1<<22 )
#define RF_DUALENTITY			( 1<<23 )
#define RF_ADDITIVEDLIGHT		( 1<<24 )
#define RF_LIGHTSTYLEDLIGHT		( 1<<25 )
#define RF_SHADOWPRECISE		( 1<<26 )
#define RF_INVISIBLE			( 1<<27 )

#define BUTTON_GROUP_FIRE_PRIMARY   0x0001
#define BUTTON_GROUP_FIRE_SECONDARY 0x0002
#define BUTTON_GROUP_RUN            0x0004
#define BUTTON_GROUP_USE            0x0008
#define BUTTON_GROUP_LEAN_LEFT      0x0010
#define BUTTON_GROUP_LEAN_RIGHT     0x0020
#define BUTTON_GROUP_DROP_WEAPON    0x0780
#define BUTTON_GROUP_VIEW           0x4000
#define BUTTON_GROUP_MOVE           0xC000

#define EF_STAND				2
#define EF_CROUCHING			4
#define EF_PRONE				8
#define EF_TELEPORT				32
#define EF_ALLIES				128
#define EF_AXIS					256
#define EF_DEAD					512

#define MAX_ACTIVESNAPSHOTS		2
#define MAX_BONECONTROLLERS		5
#define MAX_DOWNLOADWINDOW		8
#define MAX_COLORRANGES			10
#define MAX_PREDICTEDEVENTS		16
#define MAX_FRAMEINFOS			16
#define MAX_ANIMLAST			16
#define MAX_WEAPONS				16
#define MAX_SOUNDBUFFER			20
#define MAX_OBJECTIVES			20
#define MAX_PLAYERSTATS			32
#define MAX_NAMELENGTH			32
#define MAX_MAPAREABYTES		32
#define MAX_SURFACES			32
#define MAX_QPATH				64
#define MAX_CLIENTS				64
#define MAX_LOCATIONS			64
#define MAX_SERVERSOUNDS		64
#define	MAX_STRINGTOKENS		256
#define	MAX_OSPATH				256
#define MAX_SOUNDS				64
#define MAX_RELIABLECOMMANDS	512
#define MAX_MODELS				1024
#define MAX_ENTITIESINSNAPSHOT	1024
#define MAX_INFOSTRING			1350
#define MAX_STRINGCHARS			2048
#define MAX_CONFIGSTRINGS		2736
#define MAX_EXTSTRINGCHARS		4096
#define MAX_GAMESTATECHARS		32000

#define CS_MAXSOUNDS_BITS		8
#define CS_MAXLIGHTSTYLES		32
#define CS_MAXAMMOCOUNT			32
#define CS_MAXACTIVEITEMS		32
#define CS_MAXINVENTORY			32
#define CS_MAXAMMO				32
#define CS_MAXLOCATIONS			64
#define CS_MAXIMAGES			64
#define	CS_MAXMODELS			384

#define	CS_MAXSOUNDS			( 1<<MAX_SOUNDS_BITS )
#define CS_MAXITEMS				( CS_MAXINVENTORY + CS_MAXAMMO )

#define	CS_SERVERINFO			0
#define	CS_SYSTEMINFO			1
#define	CS_NAME					2
#define	CS_SOUNDTRACK			8
#define CS_FOGINFO				9
#define CS_SKYINFO				10
#define	CS_GAMEVERSION			11
#define	CS_LEVELSTARTTIME		12
#define	CS_MODELS				32
#define	CS_PLAYERS				1684

#define	CS_SOUNDS				( CS_MODELS + CS_MAXMODELS )
#define CS_IMAGES				( CS_SOUNDS + CS_MAXSOUNDS )
#define CS_LIGHTSTYLES			( CS_IMAGES + CS_MAXIMAGES )
#define CS_AMMO					( CS_PLAYERS + MAX_CLIENTS )
#define CS_LOCATIONS			( CS_AMMO + CS_MAXAMMO )

#define CONTENTS_SOLID			0x1
#define CONTENTS_LAVA			0x8
#define CONTENTS_SLIME			0x10
#define CONTENTS_WATER			0x20
#define CONTENTS_FOG			0x40
#define CONTENTS_AREAPORTAL		0x8000
#define CONTENTS_PLAYERCLIP		0x10000
#define CONTENTS_MONSTERCLIP	0x20000
#define CONTENTS_WEAPONCLIP		0x40000
#define CONTENTS_SHOOTABLEONLY	0x100000
#define CONTENTS_ORIGIN			0x1000000
#define CONTENTS_BODY			0x2000000
#define CONTENTS_CORPSE			0x4000000
#define CONTENTS_DETAIL			0x8000000
#define CONTENTS_STRUCTURAL		0x10000000
#define CONTENTS_TRANSLUCENT	0x20000000
#define CONTENTS_TRIGGER        0x40000000
#define CONTENTS_NODROP         0x80000000

#define MASK_ALL                ( -1 )
#define MASK_SOLID				( CONTENTS_SOLID )

#define HUD_MESSAGE_YELLOW			"\x01"
#define HUD_MESSAGE_WHITE			"\x03"
#define HUD_MESSAGE_CHAT_WHITE		"\x02"
#define HUD_MESSAGE_CHAT_RED		"\x04"

typedef void ( *xcommand_t )( );
static char *LaunchAppName;

#define qfalse 0
#define qtrue 1

typedef int qhandle_t;
typedef int sfxHandle_t;
typedef int clipHandle_t;
typedef int cvarHandle_t;
typedef int fileHandle_t;
typedef int qboolean;
typedef unsigned char uchar;

typedef enum soundChannel_s
{
	CHAN_AUTO,
	CHAN_BODY,
	CHAN_ITEM,
	CHAN_WEAPONIDLE,
	CHAN_VOICE,
	CHAN_LOCAL,
	CHAN_WEAPON,
	CHAN_DIALOG_SECONDARY,
	CHAN_DIALOG,
	CHAN_MENU,
	CHAN_MAX

} soundChannel_t;

typedef enum connstate_s
{
	CA_UNINITIALIZED,
	CA_DISCONNECTED,
	CA_AUTHORIZING,
	CA_CONNECTING,
	CA_CHALLENGING,
	CA_CONNECTED,
	CA_LOADING,
	CA_PRIMED,
	CA_ACTIVE,
	CA_CINEMATIC

} connstate_t;

typedef enum soundArgsType_s
{
	CHANARGS_NONE,
	CHANARGS_MOD,
	CHANARGS_OVERRIDE

} soundArgsType_t;

typedef enum SkelVec_Axis_s
{
	svX,
	svY,
	svZ,
	svW

} SkelVec_Axis_t;

typedef enum YPR_Axes_s
{
	Vec3YAW,
	Vec3PITCH,
	Vec3ROLL

} YPR_Axes_t;

typedef enum damage_s
{
	DAMAGE_NO,
	DAMAGE_YES,
	DAMAGE_AIM

} damage_t;

typedef enum movecontrol_s
{
	MOVECONTROL_NONE,
	MOVECONTROL_USER,
	MOVECONTROL_LEGS,
	MOVECONTROL_USER_MOVEANIM,
	MOVECONTROL_ANIM,
	MOVECONTROL_ABSOLUTE,
	MOVECONTROL_HANGING,
	MOVECONTROL_ROPE_GRAB,
	MOVECONTROL_ROPE_RELEASE,
	MOVECONTROL_ROPE_MOVE,
	MOVECONTROL_PICKUPENEMY,
	MOVECONTROL_PUSH,
	MOVECONTROL_CLIMBWALL,
	MOVECONTROL_USEANIM,
	MOVECONTROL_CROUCH,
	MOVECONTROL_LOOPUSEANIM,
	MOVECONTROL_USEOBJECT,
	MOVECONTROL_COOLOBJECT

} movecontrol_t;

typedef enum music_mood_s
{
	mood_none,
	mood_normal,
	mood_action,
	mood_suspense,
	mood_mystery,
	mood_success,
	mood_failure,
	mood_surprise,
	mood_special,
	mood_aux1,
	mood_aux2,
	mood_aux3,
	mood_aux4,
	mood_aux5,
	mood_aux6,
	mood_aux7,
	mood_totalnumber

} music_mood_t;

typedef enum painDirection_s
{
	PAIN_NONE,
	PAIN_FRONT,
	PAIN_LEFT,
	PAIN_RIGHT,
	PAIN_REAR

} painDirection_t;

typedef enum eax_mode_s
{
	eax_generic,
	eax_paddedcell,
	eax_room,
	eax_bathroom,
	eax_livingroom,
	eax_stoneroom,
	eax_auditorium,
	eax_concerthall,
	eax_cave,
	eax_arena,
	eax_hangar,
	eax_carpetedhallway,
	eax_hallway,
	eax_stonecorridor,
	eax_alley,
	eax_forest,
	eax_city,
	eax_mountains,
	eax_quarry,
	eax_plain,
	eax_parkinglot,
	eax_sewerpipe,
	eax_underwater,
	eax_drugged,
	eax_dizzy,
	eax_psychotic,
	eax_totalnumber

} eax_mode_t;

typedef enum emittype_s
{
	emit_point,
	emit_area,
	emit_spotlight,
	emit_sun
} emittype_t;

typedef enum errorParm_e
{
	ERR_FATAL,
	ERR_DROP,
	ERR_DISCONNECT,
	ERR_NEEDCD

} errorParm_t;

typedef enum fsMode_e
{
	FS_READ,
	FS_WRITE,
	FS_APPEND,
	FS_APPENDSYNC

} fsMode_t;

typedef enum cbufExec_e
{
	EXEC_NOW,
	EXEC_INSERT,
	EXEC_APPEND

} cbufExec_t;

typedef enum
{
	PRINT_ALL,
	PRINT_DEVELOPER,
	PRINT_DEVELOPER_2,
	PRINT_WARNING,
	PRINT_ERROR

} printParm_t;

typedef enum fsOrigin_e
{
	FS_SEEKCUR,
	FS_SEEKEND,
	FS_SEEKSET

} fsOrigin_t;

typedef enum firetype_s
{
	FT_NONE,
	FT_BULLET,
	FT_FAKEBULLET,
	FT_PROJECTILE,
	FT_MELEE,
	FT_SPECIAL_PROJECTILE,
	FT_CLICKITEM,
	FT_HEAVY

} firetype_t;

typedef enum voicetype_s
{
	PVT_NONE_SET,
	PVT_ALLIED_START,
	PVT_ALLIED_AIRBORNE,
	PVT_ALLIED_MANON,
	PVT_ALLIED_SAS,
	PVT_ALLIED_PILOT,
	PVY_ALLIED_ARMY,
	PVT_ALLIED_RANGER,
	PVT_ALLIED_END,
	PVT_AXIS_START,
	PVT_AXIS_AXIS1,
	PVT_AXIS_AXIS2,
	PVT_AXIS_AXIS3,
	PVT_AXIS_AXIS4,
	PVT_AXIS_AXIS5,
	PVT_AXIS_END

} voicetype_t;

typedef enum bodypart_s
{
	legs,
	torso

} bodypart_t;

typedef enum weaponstate_s
{
	WEAPON_READY,		// HOLSTERED
	WEAPON_FIRING,		// READY
	WEAPON_LOWERING,	//
	WEAPON_RAISING,		//
	WEAPON_HOLSTERED,	//
	WEAPON_RELOADING,	//
	WEAPON_CHANGING		//

} weaponstate_t;

typedef enum cameratype_s
{
	CAMERA_TOPDOWN,
	CAMERA_BEHIND,
	CAMERA_FRONT,
	CAMERA_SIDE,
	CAMERA_BEHIND_FIXED,
	CAMERA_SIDE_LEFT,
	CAMERA_SIDE_RIGHT,
	CAMERA_BEHIND_NOPITCH

} cameratype_t;

typedef enum AIRanges_s
{
	RANGE_SHORT,
	RANGE_MEDIUM,
	RANGE_LONG,
	RANGE_SNIPER,
	RANGE_NUM_RANGES

} AIRanges_t;

typedef enum keyNum_e
{
	K_TAB=9,
	K_ENTER=13,
	K_ESCAPE=27,
	K_SPACE=32,

	K_BACKSPACE=127,
	K_COMMAND,
	K_CAPSLOCK,
	K_POWER,
	K_PAUSE,
	K_UPARROW,
	K_DOWNARROW,
	K_LEFTARROW,
	K_RIGHTARROW,
	K_LALT,
	K_LCTRL,
	K_LSHIFT,
	K_RALT,
	K_RCTRL,
	K_RSHIFT,
	K_INS,
	K_DEL,
	K_PGDN,
	K_PGUP,
	K_HOME,
	K_END,
	K_F1,
	K_F2,
	K_F3,
	K_F4,
	K_F5,
	K_F6,
	K_F7,
	K_F8,
	K_F9,
	K_F10,
	K_F11,
	K_F12,
	K_F13,
	K_F14,
	K_F15,
	K_KPHOME,
	K_KPUPARROW,
	K_KPPGUP,
	K_KPLEFTARROW,
	K_KP5,
	K_KPRIGHTARROW,
	K_KPEND,
	K_KPDOWNARROW,
	K_KPPGDN,
	K_KPENTER,
	K_KPINS,
	K_KPDEL,
	K_KPSLASH,
	K_KPMINUS,
	K_KPPLUS,
	K_KPNUMLOCK,
	K_KPSTAR,
	K_KPEQUALS,
	K_MOUSE1,
	K_MOUSE2,
	K_MOUSE3,
	K_MOUSE4,
	K_MOUSE5,
	K_MWHEELDOWN,
	K_MWHEELUP,
	K_JOY1,
	K_JOY2,
	K_JOY3,
	K_JOY4,
	K_JOY5,
	K_JOY6,
	K_JOY7,
	K_JOY8,
	K_JOY9,
	K_JOY10,
	K_JOY11,
	K_JOY12,
	K_JOY13,
	K_JOY14,
	K_JOY15,
	K_JOY16,
	K_JOY17,
	K_JOY18,
	K_JOY19,
	K_JOY20,
	K_JOY21,
	K_JOY22,
	K_JOY23,
	K_JOY24,
	K_JOY25,
	K_JOY26,
	K_JOY27,
	K_JOY28,
	K_JOY29,
	K_JOY30,
	K_JOY31,
	K_JOY32,
	K_AUX1,
	K_AUX2,
	K_AUX3,
	K_AUX4,
	K_AUX5,
	K_AUX6,
	K_AUX7,
	K_AUX8,
	K_AUX9,
	K_AUX10,
	K_AUX11,
	K_AUX12,
	K_AUX13,
	K_AUX14,
	K_AUX15,
	K_AUX16,
	K_LWINKEY,
	K_RWINKEY,
	K_MENUKEY,
	K_LASTKEY

} keyNum_t;

typedef enum
{
	NA_BOT,
	NA_BAD,
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
	NA_IPX,
	NA_BROADCAST_IPX

} netAdrType_t;

typedef enum
{
	NS_CLIENT,
	NS_SERVER

} netSrc_t;

typedef enum glDriverType_e
{
	GLDRV_ICD,
	GLDRV_STANDALONE,
	GLDRV_VOODOO

} glDriverType_t;

typedef enum textureCompression_s
{
	TC_NONE,
	TC_S3TC

} textureCompression_t;

typedef enum boneType_s
{
	SKELBONE_ROTATION,
	SKELBONE_POSROT,
	SKELBONE_IKSHOULDER,
	SKELBONE_IKELBOW,
	SKELBONE_IKWRIST,
	SKELBONE_HOSEROT,
	SKELBONE_AVROT,
	SKELBONE_ZERO,
	SKELBONE_NUMBONETYPES,
	SKELBONE_WORLD,
	SKELBONE_HOSEROTBOTH,
	SKELBONE_HOSEROTPARENT

} boneType_t;

typedef enum hoseRotType_s
{
	HRTYPE_PLAIN,
	HRTYPE_ROTATEPARENT180Y,
	HRTYPE_ROTATEBOTH180Y

} hoseRotType_t;

typedef enum glHardwareType_e
{
	GLHW_GENERIC,
	GLHW_3DFX2D3D,
	GLHW_ATI,
	GLHW_TNT,
	GLHW_TNT2,
	GLHW_GEFORCE,
	GLHW_GEFORCE2,
	GLHW_GEFORCE3,
	GLHW_KYRO

} glHardwareType_t;

typedef enum musicMood_e
{
	MOOD_NONE,
	MOOD_NORMAL,
	MOOD_ACTION,
	MOOD_SUSPENSE,
	MOOD_MYSTERY,
	MOOD_SUCCESS,
	MOOD_FAILURE,
	MOOD_SURPRISE,
	MOOD_SPECIAL,
	MOOD_AUX1,
	MOOD_AUX2,
	MOOD_AUX3,
	MOOD_AUX4,
	MOOD_AUX5,
	MOOD_AUX6,
	MOOD_AUX7,

} musicMood_t;

typedef enum dlightType_e
{
	LENSFLARE=1,
	VIEWLENSFLARE,
	ADDITIVE=4

} dlightType_t;

typedef enum stereoFrame_e
{
	STEREO_CENTER,
	STEREO_LEFT,
	STEREO_RIGHT

} stereoFrame_t;

typedef enum mapSurfaceType_s
{
	MST_BAD,
	MST_PLANAR,
	MST_PATCH,
	MST_TRIANGLE_SOUP,
	MST_FLARE,
	MST_TERRAIN

} mapSurfaceType_t;

typedef enum moveAnimType_s
{
	MOVEANIMTYPE_USEACTION,
	MOVEANIMTYPE_STAND_IDLE = 0,
	MOVEANIMTYPE_STAND_WALK,
	MOVEANIMTYPE_STAND_RUN,
	MOVEANIMTYPE_CROUCH_IDLE,
	MOVEANIMTYPE_CROUCH_WALK,
	MOVEANIMTYPE_CROUCH_RUN,
	MOVEANIMTYPE_PRONE_IDLE,
	MOVEANIMTYPE_PRONE_WALK,
	MOVEANIMTYPE_PRONE_ROLL,
	NUM_MOVEANIMTYPES

} moveAnimType_t;

typedef enum healthType_s
{
	HEALTHTYPE_NONE,
	HEALTHTYPE_GOOD,
	HEALTHTYPE_BAD

} healthType_t;

typedef enum skelType_s
{
	SKELTYPE_HUMAN,
	SKELTYPE_STATIC

} skelType_t;

typedef enum playerStat_e
{
	STAT_HEALTH,
	STAT_MAXHEALTH,
	STAT_WEAPONS,
	STAT_EQUIPPEDWEAPON,
	STAT_AMMO,
	STAT_MAXAMMO,
	STAT_CLIPAMMO,
	STAT_MAXCLIPAMMO,
	STAT_INZOOM,
	STAT_CROSSHAIR,
	STAT_LASTPAIN,

	STAT_BOSSHEALTH=12,
	STAT_CINEMATIC,
	STAT_ADDFADE,
	STAT_LETTERBOX,
	STAT_COMPASSNORTH,
	STAT_OBJECTIVELEFT,
	STAT_OBJECTIVERIGHT,
	STAT_OBJECTIVECENTER,
	STAT_TEAM,
	STAT_KILLS,
	STAT_DEATHS,

	STAT_HIGHESTSCORE=25,
	STAT_ATTACKERCLIENT,
	STAT_INFOCLIENT,
	STAT_INFOCLIENTHEALTH,
	STAT_DAMAGEDIR,
	STAT_LASTSTAT,

} playerStat_t;

typedef enum gameType_e
{
	GT_SINGLEPLAYER,
	GT_FREEFORALL,
	GT_TEAMDEATHMATCH,
	GT_TEAMROUNDS,
	GT_OBJECTIVE,

} gameType_t;

typedef enum refEntityType_e
{
	RT_MODEL,
	RT_SPRITE,
	RT_BEAM,
	RT_PORTALSURFACE,

} refEntityType_t;

typedef enum persEnum_s
{
	PERS_SCORE,
	PERS_TEAM

} persEnum_t;

typedef enum meansOfDeath_s
{
	MOD_NONE,
	MOD_SUICIDE,
	MOD_CRUSH,
	MOD_CRUSH_EVERY_FRAME,
	MOD_TELEFRAG,
	MOD_LAVA,
	MOD_SLIME,
	MOD_FALLING,
	MOD_LAST_SELF_INFLICTED,
	MOD_EXPLOSION,
	MOD_EXPLODEWALL,
	MOD_ELECTRIC,
	MOD_ELECTRICWATER,
	MOD_THROWNOBJECT,
	MOD_GRENADE,
	MOD_BEAM,
	MOD_ROCKET,
	MOD_IMPACT,
	MOD_BULLET,
	MOD_FAST_BULLET,
	MOD_VEHICLE,
	MOD_FIRE,
	MOD_FLASHBANG,
	MOD_ON_FIRE,
	MOD_GIB,
	MOD_IMPALE,
	MOD_BASH,
	MOD_SHOTGUN,
	MOD_TOTAL_NUMBER

} meansOfDeath_t;

typedef enum entityType_e
{
	ET_MODELANIMSKEL,
	ET_MODELANIM,
	ET_VEHICLE,
	ET_PLAYER,
	ET_ITEM,
	ET_GENERAL,
	ET_MISSILE,
	ET_MOVER,
	ET_BEAM,
	ET_MULTIBEAM,
	ET_PORTAL,
	ET_EVENTONLY,
	ET_RAIN,
	ET_LEAF,
	ET_SPEAKER,
	ET_PUSH_TRIGGER,
	ET_TELEPORTTRIGGER,
	ET_DECAL,
	ET_EMITTER,
	ET_ROPE,
	ET_EVENTS,
	ET_EXECCOMMANDS

} entityType_t;

typedef enum teamType_e
{
	TEAM_NONE,
	TEAM_SPECTATOR,
	TEAM_FREEFORALL,
	TEAM_ALLIES,
	TEAM_AXIS

} teamType_t;

typedef enum svc_ops_e_s
{
	svc_bad,
	svc_nop,
	svc_gamestate,
	svc_configstring,
	svc_baseline,
	svc_serverCommand,
	svc_download,
	svc_snapshot,
	svc_centerprint,
	svc_locprint,
	svc_cgameMessage,
	svc_EOF

} svc_ops_e_t;

typedef enum clc_ops_e_t
{
	clc_bad,
	clc_nop,
	clc_move,
	clc_moveNoDelta,
	clc_clientCommand,
	clc_EOF

} clc_ops_e_s;

typedef enum memtag_s
{
	TAG_FREE,
	TAG_CONST,
	TAG_GENERAL,
	TAG_BOTLIB,
	TAG_RENDERER,
	TAG_GAME,
	TAG_CGAME,
	TAG_CLIENT,
	TAG_TIKI,
	TAG_STRINGS_AND_COMMANDS,
	TAG_SOUND,
	TAG_STATIC,
	TAG_STATIC_RENDERER,
	TAG_SKEL,
	TAG_TEMP,
	TAG_EXE,
	TAG_NUM_TOTAL_TAGS

} memtag_t;

typedef enum joystickAxis_s
{
	AXIS_SIDE,
	AXIS_FORWARD,
	AXIS_UP,
	AXIS_ROLL,
	AXIS_YAW,
	AXIS_PITCH,
	MAX_JOYSTICK_AXIS

} joystickAxis_t;

typedef enum
{
	CS_FREE,
	CS_ZOMBIE,
	CS_CONNECTED,
	CS_PRIMED,
	CS_ACTIVE

} clientState_t;

typedef enum sysEventType_s
{
	SE_NONE,
	SE_KEY,
	SE_CHAR,
	SE_MOUSE,
	SE_JOYSTICK_AXIS,
	SE_CONSOLE,
	SE_PACKET

} sysEventType_t;

typedef enum viewmodelanim_s
{
	VMA_IDLE,
	VMA_CHARGE,
	VMA_FIRE,
	VMA_FIRE_SECONDARY,
	VMA_RECHAMBER,
	VMA_RELOAD,
	VMA_RELOAD_SINGLE,
	VMA_RELOAD_END,
	VMA_PULLOUT,
	VMA_PUTAWAY,
	VMA_LADDERSTEP,
	VMA_NUMANIMATIONS

} viewmodelanim_t;

typedef enum const_str_s
{
	STRING_EMPTY = 1,
	STRING_TOUCH,
	STRING_BLOCK,
	STRING_TRIGGER,
	STRING_USE,
	STRING_DAMAGE,
	STRING_LOCATION,
	STRING_SAY,
	STRING_FAIL,
	STRING_BUMP,
	STRING_DEFAULT,
	STRING_ALL,
	STRING_MOVE_ACTION,
	STRING_RESUME,
	STRING_OPEN,
	STRING_CLOSE,
	STRING_PICKUP,
	STRING_REACH,
	STRING_START,
	STRING_TELEPORT,
	STRING_MOVE,
	STRING_MOVE_END,
	STRING_MOVETO,
	STRING_WALKTO,
	STRING_RUNTO,
	STRING_CROUCHTO,
	STRING_CRAWLTO,
	STRING_STOP,
	STRING_RESET,
	STRING_PRESPAWN,
	STRING_SPAWN,
	STRING_PLAYERSPAWN,
	STRING_SKIP,
	STRING_ROUNDSTART,
	STRING_VISIBLE,
	STRING_NOT_VISIBLE,
	STRING_DONE,
	STRING_ANIMDONE,
	STRING_UPPERANIMDONE,
	STRING_SAYDONE,
	STRING_FLAGGEDANIMDONE,
	STRING_IDLE,
	STRING_WALK,
	STRING_SHUFFLE,
	STRING_ANIM_CROUCH_SCR,
	STRING_FORGOT,
	STRING_JOG_HUNCH,
	STRING_JOG_HUNCH_RIFLE,
	STRING_KILLED,
	STRING_ALARM,
	STRING_SCRIPTCLASS,
	STRING_FACT_SCRIPT_FACTORY,
	STRING_DEATH, STRING_DEATH_FALL_TO_KNEES, STRING_ENEMY, STRING_DEAD, STRING_MOOD, STRING_PATROL, STRING_RUNNER, STRING_FOLLOW, STRING_ACTION, STRING_MOVE_BEGIN, STRING_ACTION_BEGIN, STRING_ACTION_END, STRING_SUCCESS, STRING_ENTRY, STRING_EXIT, STRING_PATH, STRING_NODE, STRING_ASK_COUNT, STRING_ATTACKER, STRING_USECOVER, STRING_WAITCOVER, STRING_VOID, STRING_END, STRING_ATTACK, STRING_NEAR, STRING_PAPERS, STRING_CHECK_PAPERS, STRING_TIMEOUT, STRING_HOSTILE, STRING_LEADER, STRING_GAMEMAP, STRING_BORED, STRING_NERVOUS, STRING_CURIOUS, STRING_ALERT, STRING_GREET, STRING_DEFEND, STRING_ANIM, STRING_ANIM_SCRIPTED, STRING_ANIM_CURIOUS, STRING_ANIMLOOP, STRING_UNDEFINED, STRING_NOTSET, STRING_INCREMENT, STRING_DECREMENT, STRING_TOGGLE, STRING_NORMAL, STRING_SUSPENSE, STRING_MYSTERY, STRING_SURPRISE, STRING_ANIM_CROUCH_RUN_SCR, STRING_ANIM_AIM_SCR, STRING_ANIM_SHOOT_SCR, STRING_ANIM_MG42_SHOOT_SCR, STRING_ANIM_MG42_IDLE_SCR, STRING_ANIM_MG42_RELOAD_SCR, STRING_DRIVE, STRING_GLOBAL_WEAPON_SCR, STRING_GLOBAL_MOVETO_SCR, STRING_GLOBAL_ANIM_SCR, STRING_GLOBAL_ANIM_SCRIPTED_SCR, STRING_GLOBAL_ANIM_NOCLIP_SCR, STRING_GLOBAL_WALKTO_SCR, STRING_GLOBAL_RUNTO_SCR, STRING_AIMAT,
	STRING_GLOBAL_DISABLE_AI_SCR,
 STRING_GLOBAL_CROUCHTO_SCR, STRING_GLOBAL_CRAWLTO_SCR, STRING_GLOBAL_KILLED_SCR, STRING_GLOBAL_PAIN_SCR, STRING_PAIN, STRING_TRACK, STRING_HASENEMY, STRING_ANIM_COWER_SCR, STRING_ANIM_STAND_SCR, STRING_ANIM_IDLE_SCR, STRING_ANIM_SURPRISE_SCR, STRING_ANIM_STANDSHOCK_SCR, STRING_ANIM_STANDIDENTIFY_SCR, STRING_ANIM_STANDFLINCH_SCR, STRING_ANIM_DOG_IDLE_SCR, STRING_ANIM_DOG_ATTACK_SCR, STRING_ANIM_DOG_CURIOUS_SCR, STRING_ANIM_DOG_CHASE_SCR, STRING_CANNON, STRING_GRENADE, STRING_HEAVY, STRING_ITEM, STRING_ITEMS, STRING_ITEM1, STRING_ITEM2, STRING_ITEM3, STRING_ITEM4, STRING_STAND, STRING_MG, STRING_PISTOL, STRING_RIFLE, STRING_SMG, STRING_TURNTO, STRING_STANDING, STRING_CROUCHING, STRING_PRONE, STRING_OFFGROUND, STRING_WALKING, STRING_RUNNING, STRING_FALLING, STRING_ANIM_NOTHING, STRING_ANIM_DIRECT, STRING_ANIM_PATH, STRING_ANIM_WAYPOINT, STRING_ANIM_DIRECT_NOGRAVITY, STRING_EMOTION_NONE, STRING_EMOTION_NEUTRAL, STRING_EMOTION_WORRY, STRING_EMOTION_PANIC, STRING_EMOTION_FEAR, STRING_EMOTION_DISGUST, STRING_EMOTION_ANGER, STRING_EMOTION_AIMING, STRING_EMOTION_DETERMINED, STRING_EMOTION_DEAD, STRING_EMOTION_CURIOUS, STRING_ANIM_EMOTION_SCR, STRING_FORCEANIM, STRING_FORCEANIM_SCRIPTED, STRING_TURRET, STRING_COVER, STRING_ANIM_PAIN_SCR, STRING_ANIM_KILLED_SCR, STRING_ANIM_ATTACK_SCR, STRING_ANIM_SNIPER_SCR, STRING_KNEES, STRING_CRAWL, STRING_FLOOR, STRING_ANIM_PATROL_SCR, STRING_ANIM_RUN_SCR, STRING_CROUCH, STRING_CROUCHWALK, STRING_CROUCHRUN, STRING_ANIM_CROUCH_WALK_SCR, STRING_ANIM_WALK_SCR, STRING_ANIM_PRONE_SCR, STRING_ANIM_RUNAWAYFIRING_SCR, STRING_ANIM_RUN_SHOOT_SCR, STRING_ANIM_RUNTO_ALARM_SCR, STRING_ANIM_RUNTO_CASUAL_SCR, STRING_ANIM_RUNTO_COVER_SCR, STRING_ANIM_RUNTO_DANGER_SCR, STRING_ANIM_RUNTO_DIVE_SCR, STRING_ANIM_RUNTO_FLEE_SCR, STRING_ANIM_RUNTO_INOPEN_SCR, STRING_ANIM_DISGUISE_SALUTE_SCR, STRING_ANIM_DISGUISE_WAIT_SCR, STRING_ANIM_DISGUISE_PAPERS_SCR, STRING_ANIM_DISGUISE_ENEMY_SCR, STRING_ANIM_DISGUISE_HALT_SCR, STRING_ANIM_DISGUISE_ACCEPT_SCR, STRING_ANIM_DISGUISE_DENY_SCR,
 STRING_ANIM_CORNERLEFT_SCR,
STRING_ANIM_CORNERRIGHT_SCR, STRING_ANIM_OVERATTACK_SCR, STRING_ANIM_CONTINUE_LAST_ANIM_SCR, STRING_FLAGGED, STRING_ANIM_FULLBODY_SCR, STRING_INTERNAL, STRING_DISGUISE_SALUTE, STRING_DISGUISE_SENTRY, STRING_DISGUISE_OFFICER, STRING_DISGUISE_ROVER, STRING_DISGUISE_NONE, STRING_MACHINEGUNNER, STRING_DISGUISE, STRING_DOG_IDLE, STRING_DOG_ATTACK, STRING_DOG_CURIOUS, STRING_DOG_GRENADE, STRING_ANIM_GRENADERETURN_SCR, STRING_ANIM_GRENADEKICK_SCR, STRING_ANIM_GRENADETHROW_SCR, STRING_ANIM_GRENADETOSS_SCR, STRING_ANIM_GRENADEMARTYR_SCR, STRING_MOVEDONE, STRING_AIM, STRING_ONTARGET, STRING_UNARMED, STRING_BALCONY_IDLE, STRING_BALCONY_CURIOUS, STRING_BALCONY_ATTACK, STRING_BALCONY_DISGUISE, STRING_BALCONY_GRENADE, STRING_BALCONY_PAIN, STRING_BALCONY_KILLED, STRING_WEAPONLESS, STRING_DEATH_BALCONY_INTRO, STRING_DEATH_BALCONY_LOOP, STRING_DEATH_BALCONY_OUTTRO, STRING_SOUNDDONE, STRING_NOCLIP, STRING_GERMAN, STRING_AMERICAN, STRING_SPECTATOR, STRING_FREEFORALL, STRING_ALLIES, STRING_AXIS, STRING_DRAW, STRING_KILLS, STRING_ALLIESWIN, STRING_AXISWIN, STRING_ANIM_SAY_CURIOUS_SIGHT_SCR, STRING_ANIM_SAY_CURIOUS_SOUND_SCR, STRING_ANIM_SAY_GRENADE_SIGHTED_SCR, STRING_ANIM_SAY_KILL_SCR, STRING_ANIM_SAY_MANDOWN_SCR, STRING_ANIM_SAY_SIGHTED_SCR, STRING_VEHICLEANIMDONE, STRING_POSTTHINK, STRING_TURNDONE, STRING_ANIM_NO_KILLED_SCR, STRING_MG42, STRING_MP40, STRING_LENGTH_

} const_str_t;

typedef enum weaponhand_s
{
	WEAPON_MAIN,
	WEAPON_OFFHAND,
	WEAPON_ERROR

} weaponhand_t;

typedef enum firemode_s
{
	FIRE_PRIMARY,
	FIRE_SECONDARY,
	MAX_FIREMODES,
	FIRE_ERROR

} firemode_t;

typedef enum entity_event_s
{
	EV_NONE,
	EV_FALL_SHORT,
	EV_FALL_MEDIUM,
	EV_FALL_FAR,
	EV_FALL_FATAL,
	EV_TERMINAL_VELOCITY,
	EV_WATER_TOUCH,
	EV_WATER_LEAVE,
	EV_WATER_UNDER,
	EV_WATER_CLEAR,
	EV_LAST_PREDICTED

} entity_event_t;

typedef enum pmType_e
{
	PM_NORMAL,
	PM_CLIMBWALL,
	PM_NOCLIP,
	PM_DEAD

} pmType_t;

typedef struct sysEvent_s
{
  int evTime;
  sysEventType_t evType;
  int evValue;
  int evValue2;
  int evPtrLength;
  void *evPtr;

} sysEvent_t;

typedef struct nodetype
{
	struct	nodetype *left, *right, *parent;
	struct	nodetype *next, *prev;
	struct	nodetype **head;
	int		weight;
	int		symbol;

} node_t;

#define HMAX 256

typedef struct
{
	int			blocNode;
	int			blocPtrs;
	node_t*		tree;
	node_t*		lhead;
	node_t*		ltail;
	node_t*		loc[HMAX+1];
	node_t**	freelist;
	node_t		nodeList[768];
	node_t*		nodePtrs[768];

} huff_t;

typedef struct
{
	huff_t		compressor;
	huff_t		decompressor;

} huffman_t;

typedef struct polyVert_s
{
  float xyz[3];
  float st[2];
  unsigned char modulate[4];

} polyVert_t;

typedef struct poly_s
{

  qhandle_t hShader;
  int numVerts;
  polyVert_t *verts;

} poly_t;

typedef struct cmd_function_s
{
	struct cmd_function_s	*next;
	const char				*name;
	xcommand_t				function;
} cmd_function_t;

typedef struct client_persistant_s
{
	char userinfo[MAX_INFOSTRING];
	char netname[32];
	char playermodel[64];
	char playergermanmodel[64];
	char weapon[64];
	clientState_t connectionState;
	teamType_t team;
	int kills;

} client_persistant_t;

typedef struct cplane_s
{
	vec3_t normal;
	float dist;
	BYTE type;
	BYTE signBits;
	BYTE pad[2];

} cplane_t;

typedef struct userEyes_s
{
	signed char ofs[3];
	float angles[2];

} userEyes_t;

typedef struct outPacket_s
{
  int p_cmdNumber;
  int p_serverTime;
  int p_realtime;
  userEyes_t p_eyeinfo;

} outPacket_t;

// a trace is returned when a box is swept through the world
typedef struct {
	qboolean	allsolid;	// if true, plane is not valid
	qboolean	startsolid;	// if true, the initial point was in a solid area
	float		fraction;	// time completed, 1.0 = didn't hit anything
	vec3_t		endpos;		// final position
	cplane_t	plane;		// surface normal at impact, transformed to world space
	int			surfaceFlags;	// surface hit
	int			shaderNum;
	int			contents;	// contents on other side of surface hit
	int			entityNum;	// entity the contacted surface is a part of

	int			location;
	struct gentity_s *ent;
} trace_t;

typedef struct playerStateAA_s
{
	int commandTime;//4 - 0
	pmType_t pmType;//4 - 4
	int bobCycle;//4 - 8
	int pmFlags;//4 - 12
	int pmRunTime; //removed in bt ////////////bt
	vec3_t origin;//12 - 16
	vec3_t velocity;//12 - 28
	int gravity;//4 - 40
	int speed;//4 - 44
	int deltaAngles[3];//12 - 48
	int groundEntityNum;//4 - 60
	qboolean walking;//4 - 64
	qboolean groundPlane;//4 - 68
	int feetFalling;//4 - 72
	vec3_t fallDir;//12 - 76
	trace_t groundTrace;//68 - 88
	int clientNum;//4 - 156
	vec3_t viewAngles;//12 - 160
	int viewHeight;//4 - 172
	float leanAngle;//4 - 176
	int viewModelAnim;//4 - 180
	int viewModelAnimChanged;//4 - 184
	int stats[MAX_PLAYERSTATS];//128 - 188
	int activeItems[8];//32 - 316
	int ammoNameIndex[MAX_WEAPONS];//64 - 348
	int ammoAmount[MAX_WEAPONS];//64 - 412
	int maxAmmoAmount[MAX_WEAPONS];//64 - 476
	musicMood_t currentMusicMood;//4 - 540
	musicMood_t fallbackMusicMood;//4 - 544
	float musicVolume;//4 - 548
	float musicVolumeFadeTime;//4 - 552
	int reverbType;//4 - 556
	float reverbLevel;//4 - 560
	vec4_t blend;//16 - 564
	float fov;//4 - 580
	vec3_t cameraOrigin;//12 - 584
	vec3_t cameraAngles;//12 - 596
	float cameraTime;//4 - 608
	vec3_t cameraOffset;//12 - 612
	vec3_t cameraPosOfs;//12 - 624
	int cameraFlags;//4 - 636
	vec3_t damageAngles;//12 - 640
	int ping;//4 - 660
	vec3_t eyePos;//12 - 664
	//?? - 676
} playerStateAA_t;

typedef struct playerStateDSH_s
{
	int commandTime;//4 - 0
	pmType_t pmType;//4 - 4
	int bobCycle;//4 - 8
	int pmFlags;//4 - 12
	vec3_t origin;//12 - 16
	vec3_t velocity;//12 - 28
	int gravity;//4 - 40
	int speed;//4 - 44
	int deltaAngles[3];//12 - 48
	int groundEntityNum;//4 - 60
	qboolean walking;//4 - 64
	qboolean groundPlane;//4 - 68
	int feetFalling;//4 - 72
	vec3_t fallDir;//12 - 76
	trace_t groundTrace;//68 - 88
	int clientNum;//4 - 156
	vec3_t viewAngles;//12 - 160
	int viewHeight;//4 - 172
	float leanAngle;//4 - 176
	int viewModelAnim;//4 - 180
	int viewModelAnimChanged;//4 - 184
	int stats[MAX_PLAYERSTATS];//128 - 188
	int activeItems[8];//32 - 316
	int ammoNameIndex[MAX_WEAPONS];//64 - 348
	int ammoAmount[MAX_WEAPONS];//64 - 412
	int maxAmmoAmount[MAX_WEAPONS];//64 - 476
	musicMood_t currentMusicMood;//4 - 540
	musicMood_t fallbackMusicMood;//4 - 544
	float musicVolume;//4 - 548
	float musicVolumeFadeTime;//4 - 552
	int reverbType;//4 - 556
	float reverbLevel;//4 - 560
	vec4_t blend;//16 - 564
	float fov;//4 - 580
	vec3_t cameraOrigin;//12 - 584
	vec3_t cameraAngles;//12 - 596
	float cameraTime;//4 - 608
	vec3_t cameraOffset;//12 - 612
	vec3_t cameraPosOfs;//12 - 624
	int cameraFlags;//4 - 636
	vec3_t damageAngles;//12 - 640
	unsigned char filler1[8];//8 - 652  ////////////bt
	int ping;//4 - 660
	vec3_t eyePos;//12 - 664
	//?? - 676
} playerStateDSH_t;

typedef playerStateDSH_t playerStateDBT_t;

typedef struct gclientAA_s
{
  playerStateAA_t ps;
  int ping;
  client_persistant_t pers;
  float cmd_angles[3];
  int lastActiveTime;
  int activeWarning;

} gclientAA_t;

typedef struct gclientDSH_s
{
	playerStateDSH_t ps;
	int ping;
	client_persistant_t pers;
	float cmd_angles[3];
	int lastActiveTime;
	int activeWarning;

} gclientDSH_t;

class GClient
{
	union GClientType
	{
		gclientAA_t clientAA;
		gclientDSH_t clientDSH;
	};
	GClientType* realGClient;
	client_persistant_t& initPers()
	{
		if (gameInfo.GetExpansion() == gameInfo.AA)
			return realGClient->clientAA.pers;
		else
			return realGClient->clientDSH.pers;
	}
public:
	client_persistant_t& pers;
	GClient(void* gclient)
		: realGClient((GClientType*)gclient), pers(initPers())
	{

	}


	GClient* operator ->()
	{
		return this;
	}
};

typedef struct server_sound_s
{
  float origin[3];
  int entity_number;
  int channel;
  short int sound_index;
  float volume;
  float min_dist;
  float maxDist;
  float pitch;
  qboolean stop_flag;
  qboolean streamed;

} server_sound_t;

/*
typedef struct clSnapshot_s
{
  qboolean valid;
  int snapFlags;
  int serverTime;
  int serverTimeResidual;
  int messageNum;
  int deltaNum;
  int ping;
  unsigned char areamask[32];
  int cmdNum;
  playerState_t ps;
  int numEntities;
  int parseEntitiesNum;
  int serverCommandNum;
  int number_of_sounds;
  server_sound_t sounds[64];

} clSnapshot_t;
*/
typedef struct qtime_s
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;

} qtime_t;

typedef struct random_data_s
{
  int *fptr;
  int *rptr;
  int *state;
  int rand_type;
  int rand_deg;
  int rand_sep;
  int *end_ptr;

} random_data_s;

typedef struct drand48_data_s
{
  short unsigned int x[3];
  short unsigned int a[3];
  short unsigned int c;
  short unsigned int old_x[3];
  int init;

} drand48_data_t;

typedef struct aliasListNode_s
{
	char aliasName[40];
	char realName[128];
	float weight;
	BYTE stopFlag;
	struct AliasListNode_s *next;
	float pitch;
	float volume;
	float pitchMod;
	float volumeMod;
	float dist;
	float maxDist;
	int channel;
	int streamed;
	char *subtitle;

} aliasListNode_t;

typedef struct aliasList_s
{
	char name[40];
	qboolean dirty;
	int numInList;
	aliasListNode_t **sortedList;
	aliasListNode_t *dataList;

} aliasList_t;

typedef struct usercmd_s
{
	int serverTime;
	BYTE msec;
	short unsigned int buttons;
	short int angles[3];
	signed char forwardmove;
	signed char rightmove;
	signed char upmove;

} userCmd_t;

/*
typedef struct pmove_s
{
  playerState_t *ps;
  userCmd_t cmd;
  int tracemask;
  qboolean noFootsteps;
  int framecount;
  int numtouch;
  int touchents[32];
  int moveresult;
  qboolean stepped;
  int pmoveEvent;
  float mins[3];
  float maxs[3];
  int watertype;
  int waterlevel;
  int pmove_fixed;
  int pmove_msec;
  void (*trace) ();
  int (*pointcontents) ();

} pmove_t;
*/

typedef struct trajectory_s
{
	int trTime;
	vec3_t trDelta;

} trajectory_t;

typedef struct frameInfo_s
{
	int index;
	float time;
	float weight;

} frameInfo_t;

typedef struct gameState_s
{
	int stringOffsets[MAX_CONFIGSTRINGS];
	char stringData[MAX_GAMESTATECHARS];
	int dataCount;

} gameState_t;

typedef struct entityState_s
{
	int number;
	entityType_t eType;
	int eFlags;
	trajectory_t pos;
	vec3_t netOrigin;
	vec3_t origin;
	vec3_t origin2;
	vec3_t netAngles;
	vec3_t angles;
	int constantLight;
	int loopSound;
	float loopSoundVolume;
	float loopSoundMinDist;
	float loopSoundMaxDist;
	float loopSoundPitch;
	int loopSoundFlags;
	int parent;
	int tagNum;
	qboolean attachUseAngles;
	vec3_t attachOffset;
	int beamEntNum;
	int modelIndex;
	int usageIndex;
	int skinNum;
	int wasFrame;
	frameInfo_t frameInfo[MAX_FRAMEINFOS];
	float actionWeight;
	int boneTag[MAX_BONECONTROLLERS];
	vec3_t boneAngles[MAX_BONECONTROLLERS];
	vec4_t boneQuat[MAX_BONECONTROLLERS];
	BYTE surfaces[MAX_SURFACES];
	int clientNum;
	int groundEntityNum;
	int solid;
	float scale;
	float alpha;
	int renderFx;
	float shaderData[2];
	float shaderTime;
	vec4_t quat;
	vec3_t eyeVector;

} entityState_t;

typedef struct
{
	entityState_t s;
	qboolean linked;
	int	linkcount;
	int svFlags;
	int	singleClient;
	qboolean bmodel;
	vec3_t mins, maxs;
	int	contents;
	vec3_t absmin, absmax;
	vec3_t currentOrigin;
	vec3_t currentAngles;
	int	ownerNum;

} entityShared_t;
/*
typedef struct clientActive_s
{
  int timeoutcount;
  clSnapshot_t snap;
  int serverTime;
  int oldServerTime;
  int serverStartTime;
  int oldFrameServerTime;
  int serverTimeDelta;
  qboolean extrapolatedSnapshot;
  qboolean newSnapshots;
  gameState_t gameState;
  char mapname[64];
  int parseEntitiesNum;
  int mouseDx[2];
  int mouseDy[2];
  int mouseIndex;
  int mousex;
  int mousey;
  unsigned int mouseButtons;
  int joystickAxis[6];
  userCmd_t cmds[128];
  int cmdNumber;
  outPacket_t outPackets[32];
  vec3_t viewangles;
  int serverId;
  clSnapshot_t snapshots[32];
  entityState_t entityBaselines[1024];
  entityState_t parseEntities[2048];

} clientActive_t; */

typedef struct netAdr_s
{
	netAdrType_t type;
	BYTE ip[4];
	BYTE ipx[10];
	short unsigned int port;

} netAdr_t;

typedef struct clientConnection_s
{
	int			clientNum;
	int			lastPacketSentTime;
	int			lastPacketTime;
	netAdr_t	serverAddress;
	int			z_unknown1;
	int			connectTime;				// for connection retransmits
	int			connectPacketCount;			// for display on connection dialog
	char		serverMessage[MAX_STRINGTOKENS];	// for display on connection dialog
	int			challenge;					// from the server to use for connecting
	int			checksumFeed;				// from the server for checksum calculations
	int			reliableSequence;
	int			reliableAcknowledge;		// the last one the server has executed
	char		reliableCommands[MAX_RELIABLECOMMANDS][MAX_STRINGCHARS/2];
	int			serverMessageSequence;
	char		serverCommands[MAX_RELIABLECOMMANDS][MAX_STRINGCHARS/2];
	int			serverCommandSequence;
	fileHandle_t download;
	char		downloadTempName[MAX_OSPATH];
	char		downloadName[MAX_OSPATH];
	int			downloadNumber;
	int			downloadBlock;	// block we are waiting for
	int			downloadCount;	// how many bytes we got
	int			downloadSize;	// how many bytes we got
	char		downloadList[MAX_INFOSTRING]; // list of paks we need to download
	qboolean	downloadRestart;	// if true, we need to do another FS_Restart because we downloaded a pak
	char		demoName[MAX_QPATH];
	qboolean	demorecording;
	qboolean	demoplaying;
	qboolean	demowaiting;	// don't record until a non-delta message is received
	qboolean	firstDemoFrameSkipped;
	fileHandle_t	demofile;
	int			timeDemoFrames;		// counter of rendered frames
	int			timeDemoStart;		// cls.realtime before first frame
	int			timeDemoBaseTime;	// 0x00FDA880 - each frame will be at this time + frameNum * 50

	BYTE		z_unknown2[0x1803C]; //-- netchan_t struct

} clientConnection_t;

typedef struct
{
  float x;
  float y;
  float w;
  float h;

} rectDef_t;

typedef rectDef_t Rectangles;

// FIXME: do something to separate text vs window stuff
typedef struct
{
  Rectangles rect;                 // client coord rectangle
  Rectangles rectClient;           // screen coord rectangle
  const char *name;               //
  const char *group;              // if it belongs to a group
  const char *cinematicName;		  // cinematic name
  int cinematic;								  // cinematic handle
  int style;                      //
  int border;                     //
  int ownerDraw;									// ownerDraw style
	int ownerDrawFlags;							// show flags for ownerdraw items
  float borderSize;               //
  int flags;                      // visible, focus, mouseover, cursor
  Rectangles rectEffects;          // for various effects
  Rectangles rectEffects2;         // for various effects
  int offsetTime;                 // time based value for various effects
  int nextTime;                   // time next effect should cycle
  vec4_t foreColor;               // text color
  vec4_t backColor;               // border color
  vec4_t borderColor;             // border color
  vec4_t outlineColor;            // border color
  qhandle_t background;           // background asset

} windowDef_t;

typedef windowDef_t Window;

typedef struct
{
	vec4_t	color;
	float	low;
	float	high;

} colorRangeDef_t;

typedef struct itemDef_s
{
  Window window;
  Rectangles textRect;
  int type;
  int alignment;
  int textalignment;
  float textalignx;
  float textaligny;
  float textscale;
  int textStyle;
  const char *text;
  void *parent;
  qhandle_t asset;
  const char *mouseEnterText;
  const char *mouseExitText;
  const char *mouseEnter;
  const char *mouseExit;
  const char *action;
  const char *onFocus;
  const char *leaveFocus;
  const char *cvar;
  const char *cvarTest;
  const char *enableCvar;
  int cvarFlags;
  sfxHandle_t clickSound;
  sfxHandle_t stopSound;
  int numColors;
  colorRangeDef_t colorRanges[MAX_COLORRANGES];
  float special;
  int cursorPos;
  void *typeData;

} itemDef_t;


typedef struct cvar_s
{
	char *name;
	char *string;
	char *resetString;
	char *latchedString;
	int flags;
	qboolean modified;
	int modificationCount;
	float value;
	int integer;
	struct cvar_s *next;
	struct cvar_s *hashNext;

} cvar_t;

typedef struct {
	cvar_t		**cvar;
	const char	*name;
	const char	*value;
	int			flags;
} regCvar_t;

typedef struct vmCvar_s
{
	cvarHandle_t handle;
	int modificationCount;
	float value;
	int integer;
	char string[256];

} vmCvar_t;

typedef struct letterLoc_s
{
	vec2_t pos;
	vec2_t size;

} letterLoc_t;

typedef struct fontHeader_s
{
	int indirection[256];
	letterLoc_t locations[256];
	char name[MAX_QPATH];
	float height;
	float aspectRatio;
	void *shader;
	int trHandle;

} fontHeader_t;

typedef struct hdElement_s
{
	qhandle_t shader;
	char shaderName[MAX_QPATH];
	int x;
	int y;
	int width;
	int height;
	vec4_t color;
	int horizontalAlign;
	int verticalAlign;
	qboolean virtualScreen;
	char string[MAX_STRINGCHARS];
	char fontName[MAX_QPATH];
	fontHeader_t *font;

} hdElement_t;

typedef struct clientAnim_s
{
	frameInfo_t vmFrameInfo[MAX_FRAMEINFOS];
	int lastVMAnim;
	int lastVMAnimChanged;
	int currentVMAnimSlot;
	int currentVMDuration;
	qboolean crossBlending;
	int lastEquippedWeaponStat;
	char lastActiveItem[80];
	int lastAnimPrefixIndex;
	vec3_t currentVMPosOffset;

} clientAnim_t;

typedef struct stopWatch_s
{
	int startTime;
	int endTime;

} stopWatch_t;

/*
typedef struct sigset_s
{
  long unsigned int __val[32];

} sigset_t;
*/

typedef struct sigvec_s
{
  int sv_mask;
  int sv_flags;

} sigvec_t;

typedef struct timespec_s
{
  long int tv_sec;
  long int tv_nsec;

} timespec_t;

typedef struct orientation_s
{
	vec3_t origin;
	vec3_t axis[3];

} orientation_t;

typedef struct savegamestruct_s
{
	int version;
	int time;
	int mapTime;
	char comment[64];
	char mapName[64];
	char saveName[64];
	char tm_filename[64];
	int tm_loopcount;
	int tm_offset;

} savegamestruct_t;

typedef struct media_s
{
	qhandle_t backTileShader;
	qhandle_t lagometerShader;
	qhandle_t shadowMarkShader;
	qhandle_t footShadowMarkShader;
	qhandle_t wakeMarkShader;
	qhandle_t pausedShader;
	qhandle_t levelExitShader;
	qhandle_t zoomOverlayShader;
	qhandle_t kar98TopOverlayShader;
	qhandle_t kar98BottomOverlayShader;
	qhandle_t binocularsOverlayShader;
	fontHeader_t *hudDrawFont;
	fontHeader_t *attackerFont;
	fontHeader_t *objectiveFont;
	qhandle_t objectivesBackShader;
	qhandle_t checkedBoxShader;
	qhandle_t uncheckedBoxShader;

} media_t;

typedef struct glConfig_s
{
	char rendererString[MAX_STRINGCHARS];
	char vendorString[MAX_STRINGCHARS];
	char versionString[MAX_STRINGCHARS];
	char extensionsString[MAX_EXTSTRINGCHARS];
	int maxTextureSize;
	int maxActiveTextures;
	int colorBits;
	int depthBits;
	int stencilBits;
	glDriverType_t driverType;
	glHardwareType_t hardwareType;
	qboolean deviceSupportsGamma;
	int textureCompression;
	qboolean textureEnvAddAvailable;
	int vidWidth;
	int vidHeight;
	float windowAspect;
	int displayFrequency;
	qboolean isFullscreen;
	qboolean stereoEnabled;
	qboolean smpActive;
	int registerCombinerAvailable;
	qboolean secondaryColorAvailable;
	qboolean var;
	qboolean fence;

} glConfig_t;

typedef struct pcx_t
{
  char manufacturer;
  char version;
  char encoding;
  char bits_per_pixel;
  short unsigned int xmin;
  short unsigned int ymin;
  short unsigned int xmax;
  short unsigned int ymax;
  short unsigned int hres;
  short unsigned int vres;
  unsigned char palette[48];
  char reserved;
  char color_planes;
  short unsigned int bytes_per_line;
  short unsigned int palette_type;
  char filler[58];
  unsigned char data;

} pcx_t;

typedef struct TargaHeader_s
{
  unsigned char id_length;
  unsigned char colormap_type;
  unsigned char image_type;
  short unsigned int colormap_index;
  short unsigned int colormap_length;
  unsigned char colormap_size;
  short unsigned int x_origin;
  short unsigned int y_origin;
  short unsigned int width;
  short unsigned int height;
  unsigned char pixel_size;
  unsigned char attributes;

} TargaHeadet;

typedef struct skelChannelList_s
{
	short int numChannels;
	short int numLocalFromGlobal;
	short int *chanLocalFromGlobal;
	short int chanGlobalFromLocal[200];

} skelChannelList_t;

typedef struct skelAnimTime_s
{
	float seconds;

} skelAnimTime_t;

typedef struct skelAnimFrame_s
{
	float radius;
	vec3_t bounds[2];
	vec3_t bones[4];

} skelAnimFrame_t;

typedef struct ftx_s
{
  int width;
  int height;
  int has_alpha;
} ftx_s;

typedef struct fcm_s
{
  int iWidth;
  int iHeight;

} fcm_t;

typedef struct varnode_s
{
  short unsigned int flags;

} varnode_t;

typedef struct cTerraPatch_s
{
  BYTE flags;
  BYTE lmapScale;
  BYTE s;
  BYTE t;
  float texCoord[2][2][2];
  char x;
  char y;
  short int iBaseHeight;
  short unsigned int iShader;
  short unsigned int iLightMap;
  short int iNorth;
  short int iEast;
  short int iSouth;
  short int iWest;
  varnode_t varTree[2][63];
  unsigned char heightmap[81];

} cTerraPatch_t;

typedef struct cStaticModel_s
{
  char model[128];
  float origin[3];
  float angles[3];
  float scale;
  int firstVertexData;
  int numVertexData;

} cStaticModel_t;

typedef struct gamelump_s
{
  void *buffer;
  int length;

} gamelump_t;

typedef struct lump_s
{
  int fileofs;
  int filelen;

} lump_t;

typedef struct dheader_s
{
  int ident;
  int version;
  int checksum;
  lump_t lumps[28];

} dheader_t;

typedef struct dmodel_s
{
  float mins[3];
  float maxs[3];
  int firstSurface;
  int numSurfaces;
  int firstBrush;
  int numBrushes;

} dmodel_t;

typedef struct dshader_s
{
  char shader[64];
  int surfaceFlags;
  int contentFlags;
  int subdivisions;
  char fenceMaskImage[64];

} dshader_t;

typedef struct dplane_s
{
  float normal[3];
  float dist;

} dplane_t;

typedef struct dnode_s
{
  int planeNum;
  int children[2];
  int mins[3];
  int maxs[3];

} dnode_t;

typedef struct dleaf_s
{
  int cluster;
  int area;
  int mins[3];
  int maxs[3];
  int firstLeafSurface;
  int numLeafSurfaces;
  int firstLeafBrush;
  int numLeafBrushes;
  int firstTerraPatch;
  int numTerraPatches;
  int firstStaticModel;
  int numStaticModels;

} dleaf_t;

typedef struct dsideequation_s
{
  float fSeq[4];
  float fTeq[4];

} dsideequation_t;

typedef struct dbrushside_s
{
  int planeNum;
  int shaderNum;
  int equationNum;

} dbrushside_t;

typedef struct dbrush_s
{
  int firstSide;
  int numSides;
  int shaderNum;

} dbrush_t;

typedef struct dfog_s
{
  char shader[64];
  int brushNum;
  int visibleSide;

} dfog_t;

typedef struct drawVert_s
{
  float xyz[3];
  float st[2];
  float lightmap[2];
  float normal[3];
  unsigned char color[4];

} drawVert_t;

typedef struct drawSoupVert_s
{
  float xyz[3];
  float st[2];
  int collapseMap;
  float lodExtra;
  float normal[3];
  unsigned char color[4];

} drawSoupVert_t;

typedef struct dsurface_s
{
  int shaderNum;
  int fogNum;
  int surfaceType;
  int firstVert;
  int numVerts;
  int firstIndex;
  int numIndexes;
  int lightmapNum;
  int lightmapX;
  int lightmapY;
  int lightmapWidth;
  int lightmapHeight;
  float lightmapOrigin[3];
  float lightmapVecs[3][3];
  int patchWidth;
  int patchHeight;
  float subdivisions;

} dsurface_t;

typedef struct dlightGrid_s
{
  float origin[3];
  float axis[3];
  int bounds[3];

} dlightGrid_t;

typedef struct dlightdef_s
{
  int lightIntensity;
  int lightAngle;
  int lightmapResolution;
  qboolean twoSided;
  qboolean lightLinear;
  float lightColor[3];
  float lightFalloff;
  float backsplashFraction;
  float backsplashDistance;
  float lightSubdivide;
  qboolean autosprite;

} dlightdef_t;

typedef struct mapspherel_s
{
  float origin[3];
  float color[3];
  float intensity;
  int leaf;
  qboolean needs_trace;
  qboolean spot_light;
  float spot_dir[3];
  float spot_radiusbydistance;

} mapspherel_t;

typedef struct miptex_s
{
  char name[32];
  unsigned int width;
  unsigned int height;
  unsigned int offsets[4];
  char animname[32];
  int flags;
  int contents;
  int value;

} miptex_t;

typedef struct gridrow_s
{
  BYTE size;
  BYTE *data;

} gridrow_t;

typedef struct msg_s
{
  qboolean allowoverflow;
  qboolean overflowed;
  qboolean oob;
  BYTE *data;
  int maxsize;
  int cursize;
  int readcount;
  int bit;

} msg_t;

typedef struct tiki_singlecmd_s
{
  int num_args;
  char **args;

} tiki_singlecmd_t;

typedef struct tiki_cmd_s
{
  int num_cmds;
  tiki_singlecmd_t cmds[128];

} tiki_cmd_t;

typedef struct dtikicmd_s
{
	int frame_num;
	int num_args;
	char **args;

} dtikicmd_t;

typedef struct dtikianimdef_s
{
	char alias[48];
	float weight;
	float blendtime;
	int flags;
	int num_client_cmds;
	dtikicmd_t *client_cmds;
	int num_server_cmds;
	dtikicmd_t *server_cmds;

} dtikianimdef_t;

typedef struct dtikianim_s
{
	char *name;
	int num_anims;
	void *alias_list;
	int num_client_initcmds;
	dtikicmd_t *client_initcmds;
	int num_server_initcmds;
	dtikicmd_t *server_initcmds;
	BYTE *modelData;
	int modelDataSize;
	vec3_t mins;
	vec3_t maxs;
	short int *m_aliases;
	char *headmodels;
	char *headskins;
	qboolean bIsCharacter;
	dtikianimdef_t *animdefs[1];

} dtikianim_t;

typedef struct dtikiSurface_s
{
  char name[64];
  char shader[4][64];
  int hShader[4];
  int numskins;
  int flags;
  float damage_multiplier;

} dtikiSurface_t;

typedef struct skelHeader_s
{
  int ident;
  int version;
  char name[64];
  int numSurfaces;
  int numBones;
  int ofsBones;
  int ofsSurfaces;
  int ofsEnd;
  int lodIndex[10];
  int numBoxes;
  int ofsBoxes;
  int numMorphTargets;
  int ofsMorphTargets;

} skelHeader_t;

typedef struct skelBoneName_s
{
  short int parent;
  short int boxIndex;
  int flags;
  char name[64];

} skelBoneName_t;

typedef struct skelSurface_s
{
  int ident;
  char name[64];
  int numTriangles;
  int numVerts;
  int staticSurfProcessed;
  int ofsTriangles;
  int ofsVerts;
  int ofsCollapse;
  int ofsEnd;
  int ofsCollapseIndex;

} skelSurface_t;

typedef short int skelIndex_t;

typedef struct skelWeight_s
{
  int boneIndex;
  float boneWeight;
  float offset[3];

} skelWeight_t;

typedef struct skelVertex_s
{
  float normal[3];
  float texCoords[2];
  int numWeights;
  skelWeight_t weights[1];

} skelVertex_t;

typedef struct skeletorVertex_s
{
  float normal[3];
  float texCoords[2];
  int numWeights;
  int numMorphs;

} skeletorVertex_t;

typedef struct skelSurfaceGame_s
{
  int ident;
  char name[64];
  int numTriangles;
  int numVerts;
  float (*pStaticXyz)[4];
  float (*pStaticNormal)[4];
  float (*pStaticTexCoords)[2][2];
  skelIndex_t *pTriangles;
  skeletorVertex_t *pVerts;
  skelIndex_t *pCollapse;
  struct skelSurfaceGame_s *pNext;
  skelIndex_t *pCollapseIndex;

} skelSurfaceGame_t;

typedef struct boneData_s
{
  short int channel;
  boneType_t boneType;
  short int parent;
  short int numChannels;
  short int numRefs;
  short int channelIndex[2];
  short int refIndex[2];
  float offset[3];
  float length;
  float weight;
  float bendRatio;
  float bendMax;
  float spinRatio;

} boneData_t;

typedef struct skelHitBox_s
{
  int boneIndex;

} skelHitBox_t;

typedef struct lodCurvePoint_s
{
  float pos;
  float val;

} lodCurvePoint_t;

typedef struct lodCurvePointConstants_s
{
  float base;
  float scale;
  float cutoff;

} lodCurvePointConstants_t;

typedef struct lodControl_s
{
  float minMetric;
  float maxMetric;
  lodCurvePoint_t curve[5];
  lodCurvePointConstants_t consts[4];

} lodControl_t;

typedef struct skelHeaderGame_s
{
  int version;
  char name[64];
  int numSurfaces;
  int numBones;
  boneData_t *pBones;
  skelSurfaceGame_t *pSurfaces;
  int lodIndex[10];
  int numBoxes;
  skelHitBox_t *pBoxes;
  lodControl_t *pLOD;
  int numMorphTargets;
  char *pMorphTargets;

} skelHeaderGame_t;

typedef struct tikiSurface_s
{
  int ident;
  char name[64];
  int numFrames;
  int numVerts;
  int minLod;
  int numTriangles;
  int ofsTriangles;
  int ofsCollapseMap;
  int ofsSt;
  int ofsXyzNormals;
  int ofsEnd;

} tikiSurface_t;

typedef struct tiki_tess_data_s
{
  int ident;
  tikiSurface_t *newsurface;
  tikiSurface_t *oldsurface;

} tiki_tess_data_t;

typedef struct skeletorVertexGame_s
{
  float normal[3];
  float texCoords[2];
  int numWeights;
  int numMorphs;

} skeletorVertexGame_s;

typedef struct staticSurface_s
{
  int ident;
  int ofsStaticData;
  skelSurfaceGame_t *surface;
  int meshNum;

} staticSurface_t;

typedef struct skeletorMorph_s
{
  int morphIndex;
  float offset[3];

} skeletorMorph_t;

typedef struct skelBone_s
{
  short int shortQuat[4];
  short int shortOffset[3];
  short int pad;

} skelBone_t;

typedef struct skelFrame_s
{
  float bounds[2][3];
  float radius;
  float delta[3];
  skelBone_t bones[1];

} skelFrame_t;

typedef struct skelAnimHeader_s
{
  int ident;
  int version;
  char name[64];
  int type;
  int numFrames;
  int numbones;
  float totaltime;
  float frametime;
  float totaldelta[3];
  int ofsFrames;

} skelAnimHeader_t;

typedef struct skelBoneCache_s
{
  float offset[4];
  float matrix[3][4];

} skelBoneCache_t;

typedef struct skelcache_s
{
  char path[96];
  skelHeaderGame_t *skel;
  int size;
  int numuses;

} skelcache_t;

typedef struct boneFileData_s
{
  char name[32];
  char parent[32];
  boneType_t boneType;
  int ofsBaseData;
  int ofsChannelNames;
  int ofsBoneNames;
  int ofsEnd;

} boneFileData_t;

typedef struct tikiSingleCmd_s
{
	int numArgs;
	char **args;

} tikiSingleCmd_t;

typedef struct tikiCmd_s
{
	int numCmds;
	tikiSingleCmd_t cmds[128];

} tikiCmd_t;

typedef struct dtikiAnimDef_s
{
	char alias[48];
	float weight;
	float blendTime;
	int flags;
	int numClientCmds;
	dtikicmd_t *clientCmds;
	int numServerCmds;
	dtikicmd_t *serverCmds;

} dtikiAnimDef_t;

typedef struct dtikiAnim_s
{
	char *name;
	int numAnims;
	void *aliasList;
	int numClientInitCmds;
	dtikicmd_t *clientInitCmds;
	int numServerInitCmds;
	dtikicmd_t *serverInitCmds;
	BYTE *modelData;
	int modelDataSize;
	vec3_t mins;
	vec3_t maxs;
	short int *aliases;
	char *headModels;
	char *headSkins;
	qboolean isCharacter;
	dtikianimdef_t *animDefs[1];

} dtikiAnim_t;

typedef struct tikiFrame_s
{
	vec3_t bounds[2];
	vec3_t scale;
	vec3_t offset;
	vec3_t delta;
	float radius;
	float frameTime;

} tikiFrame_t;

typedef struct dtiki_s
{
	char *name;
	dtikiAnim_t *a;
	void *skeletor;
	int numSurfaces;
	dtikiSurface_t *surfaces;
	float loadScale;
	float lodScale;
	float lodBias;
	vec3_t lightOffset;
	vec3_t loadOrigin;
	float radius;
	skelChannelList_t boneList;
	int numMeshes;
	short int mesh[1];

} dtiki_t;



/* ==============================================================================================================*/
typedef struct gentityAA_s
{
	entityState_t s;
	gclientAA_t *client;
	qboolean inuse;
	qboolean linked;
	int linkcount;
	int svflags;
	int singleClient;
	int lastNetTime;
	qboolean bmodel;
	vec3_t mins, maxs;
	int	contents;
	vec3_t absmin, absmax;
	float radius;
	vec3_t centroid;
	int areanum;
	vec3_t currentAngles;
	int ownerNum;
	solid_t solid;
	struct dtiki_s* tiki;
	float mat[3][3];
	void* /*struct Entity_s* */ entity;
	float freetime;
	float spawntime;
	float radius2;
	char entname[64];
	int clipmask;
	struct gentityAA_s *next;
	struct gentityAA_s *prev;

} gentityAA_t;

typedef struct gentityDSH_s
{
	entityState_t s;
	gclientAA_t* client;
	qboolean inuse;
	qboolean linked;
	int linkcount;
	int svflags;
	int singleClient;
	int lastNetTime;
	qboolean bmodel;
	vec3_t mins, maxs;
	int	contents;
	vec3_t absmin, absmax;
	float radius;
	vec3_t centroid;
	int areanum;
	vec3_t currentAngles;
	int ownerNum;
	solid_t solid;
	struct dtiki_s* tiki;
	float mat[3][3];
	void* /*struct Entity_s* */ entity;
	float freetime;
	float spawntime;
	float radius2;
	char entname[64];
	int clipmask;
	struct gentityDSH_s* next;
	struct gentityDSH_s* prev;

} gentityDSH_t;

typedef gentityDSH_t gentityDBT_t;
//DO NOT USE AS DATA MEMBER.
class GEntity
{
	union realGentityType
	{
		gentityAA_t gentAA;
		gentityDSH_t gentDSH;
		gentityDBT_t gentDBT;
	};
	realGentityType* realGent;
public:
	GClient *client;
	GEntity(void* gent)
		: realGent((realGentityType*)gent)
	{
		if (gameInfo.GetExpansion() == gameInfo.AA)
		{
			client = (GClient *)realGent->gentAA.client;
		}
		else if(gameInfo.GetExpansion() == gameInfo.SH)
		{
			client = (GClient*)realGent->gentDSH.client;
		}
		else if (gameInfo.GetExpansion() == gameInfo.BT)
		{
			client = (GClient*)realGent->gentDBT.client;
		}
	}
	
	operator void* ()
	{
		return (void*)realGent;
	}

	GEntity* operator ->()
	{
		return this;
	}
};

typedef struct treadMark_s
{
	int referenceNumber;
	int lastTime;
	qhandle_t treadShader;
	int state;
	float width;
	vec3_t startDir;
	vec3_t startVerts[2];
	float startTexCoord;
	float startAlpha;
	vec3_t midPos;
	vec3_t midVerts[2];
	float midTexCoord;
	float midAlpha;
	vec3_t endPos;
	vec3_t endVerts[2];
	float endTexCoord;
	float endAlpha;

} treadMark_t;

typedef struct markFragment_s
{
	int firstPoint;
	int numPoints;
	int index;

} markFragment_t;

typedef struct baseShader_s
{
	char shader[MAX_QPATH];
	int surfaceFlags;
	int contentFlags;

} baseShader_t;

typedef struct clientInfo_s
{
	teamType_t team;

} clientInfo_t;

typedef struct objective_s
{
	char text[MAX_STRINGCHARS];
	int flags;

} objective_t;

typedef struct rain_s
{
	float density;
	float speed;
	int speedVary;
	int slant;
	float length;
	float minDist;
	float width;
	char shader[16][MAX_STRINGCHARS];
	int numShaders;

} rain_t;

typedef struct serverSound_s
{
	vec3_t origin;
	int entityNumber;
	int channel;
	short int soundIndex;
	float volume;
	float minDist;
	float maxDist;
	float pitch;
	qboolean stopFlag;
	qboolean streamed;

} serverSound_t;

typedef struct debugLine_s
{
	vec3_t start;
	vec3_t end;
	float color[3];
	float alpha;
	float width;
	short unsigned int factor;
	short unsigned int pattern;

} debugLine_t;

typedef struct debugString_s
{
	char text[MAX_QPATH];
	vec3_t pos;
	float scale;
	vec4_t color;

} debugString_t;

typedef struct profVar_s
{
	int start;
	int clockCycles;
	int calls;
	float time;
	float totTime;
	float avgTime;
	float low;
	float high;

} profVar_t;

typedef struct profGame_s
{
	profVar_t AI;
	profVar_t MmoveSingle;
	profVar_t thread_timingList;
	profVar_t gamescripts;
	profVar_t GProbe1;
	profVar_t GProbe2;
	profVar_t GProbe3;
	profVar_t FindPath;
	profVar_t vector_length;
	profVar_t script_trace;
	profVar_t internal_trace;
	profVar_t PreAnimate;
	profVar_t PostAnimate;

} profGame_t;

typedef struct profCGame_s
{
	profVar_t CG_AddCEntity;
	profVar_t CG_DrawActiveFrame;
	profVar_t CG_AddPacketEntities;
	profVar_t CG_DrawActive;
	profVar_t CG_EntityShadow;
	profVar_t CG_Rain;
	profVar_t CG_AddBeams;
	profVar_t CG_ModelAnim;
	profVar_t CG_ProcessSnapshots;
	profVar_t CProbe1;
	profVar_t CProbe2;
	profVar_t CProbe3;

} profCGame_t;

typedef struct refEntity_s
{
	entityType_t reType;
	int renderFx;
	int model;
	int oldModel;
	vec3_t lightingOrigin;
	int parentEntity;
	vec3_t axis[3];
	int nonNormalizedAxes;
	vec3_t origin;
	frameInfo_t frameInfo[MAX_FRAMEINFOS];
	float actionWeight;
	short int wasframe;
	float scale;
	vec3_t oldOrigin;
	int skinNum;
	int customShader;
	BYTE shaderRGBA[4];
	float shaderTexCoord[2];
	float shaderTime;
	int entityNumber;
	BYTE surfaces[MAX_SURFACES];
	float shaderData[2];
	int *boneTag;
	vec4_t *boneQuat;
	tikiFrame_t *of;
	tikiFrame_t *nf;
	dtiki_t *tiki;
	int boneStart;
	int morphStart;
	int hasMorph;
	float radius;
	float rotation;

} refEntity_t;

typedef struct refDef_s
{
	int x;
	int y;
	int width;
	int height;
	float fovX;
	float fovY;
	vec3_t viewOrg;
	vec3_t viewAxis[3];
	int time;
	int rdFlags;
	BYTE areaMask[MAX_MAPAREABYTES];
	float farplaneDistance;
	float farplaneColor[3];
	qboolean farplaneCull;
	qboolean skyPortal;
	float skyAlpha;
	vec3_t skyOrigin;
	vec3_t skyAxis[3];

} refDef_t;

typedef struct snapshotAA_s
{
	int snapFlags;
	int ping;
	int serverTime;
	BYTE areaMask[MAX_MAPAREABYTES];
	playerStateAA_t ps;
	int numEntities;
	entityState_t entities[MAX_ENTITIESINSNAPSHOT];
	int numServerCommands;
	int serverCommandSequence;
	int numberOfSounds;
	serverSound_t sounds[MAX_SERVERSOUNDS];

} snapshotAA_t;


typedef struct snapshotDSH_s
{
	int snapFlags;
	int ping;
	int serverTime;
	BYTE areaMask[MAX_MAPAREABYTES];
	playerStateDSH_t ps;
	int numEntities;
	entityState_t entities[MAX_ENTITIESINSNAPSHOT];
	int numServerCommands;
	int serverCommandSequence;
	int numberOfSounds;
	serverSound_t sounds[MAX_SERVERSOUNDS];

} snapshotDSH_t;

typedef snapshotDSH_t snapshotDBT_t;

typedef struct centity_s
{
	entityState_t currentState;
	entityState_t nextState;
	int teleported;
	int interpolate;
	int currentValid;
	int miscTime;
	int snapShotTime;
	int errorTime;
	vec3_t errorOrigin;
	vec3_t errorAngles;
	int extrapolated;
	vec3_t rawOrigin;
	vec3_t rawAngles;
	vec3_t beamEnd;
	vec3_t lerpOrigin;
	vec3_t lerpAngles;
	int tikiLoopSound;
	float tikiLoopSoundVolume;
	float tikiLoopSoundMinDist;
	float tikiLoopSoundMaxDist;
	float tikiLoopSoundPitch;
	int tikiLoopSoundFlags;
	vec4_t color;
	vec4_t clientColor;
	int clientFlags;
	int splashLastSpawnTime;
	int splashStillCount;
	vec4_t boneQuat[MAX_BONECONTROLLERS];
	float animLastTimes[MAX_ANIMLAST];
	int animLast[MAX_ANIMLAST];
	int animLastWeight;
	int usageIndexLast;
	int footOnGround_Right;
	int footOnGround_Left;
	int nextLandTime;

} centity_t;

typedef struct cgs_s
{
	gameState_t gameState;
	glConfig_t glConfig;
	float screenXScale;
	float screenYScale;
	float screenXBias;
	int serverCommandSequence;
	int processedSnapshotNum;
	qboolean localServer;
	int levelStartTime;
	int matchEndTime;
	int serverLagTime;
	int gameType;
	int dmFlags;
	int teamFlags;
	int fragLimit;
	int timeLimit;
	int maxClients;
	int cinematic;
	char mapName[MAX_QPATH];
	int modelDraw[MAX_MODELS];
	int soundPrecache[MAX_SOUNDS];
	int numInlineModels;
	int inlineDrawModel[MAX_MODELS];
	vec3_t inlineModelMidpoints[MAX_MODELS];
	media_t media;

} cgs_t;

/*
typedef struct cg_s
{
	int clientFrame;
	int clientNum;
	int demoPlayback;
	int levelShot;
	int latestSnapshotNum;
	int latestSnapshotTime;
	snapshot_t *snap;
	snapshot_t *nextSnap;
	snapshot_t activeSnapshots[MAX_ACTIVESNAPSHOTS];
	float frameInterpolation;
	int thisFrameTeleport;
	int nextFrameTeleport;
	int nextFrameCameraCut;
	int frametime;
	int time;
	int physicsTime;
	int renderingThirdPerson;
	int hyperSpace;
	playerState_t predictedPlayerState;
	int validPPS;
	int predictedErrorTime;
	vec3_t predictedError;
	int weaponCommand;
	int weaponCommandSend;
	vec3_t autoAngles;
	vec3_t autoAxis[3];
	vec3_t autoAnglesSlow;
	vec3_t autoAxisSlow[3];
	vec3_t autoAnglesFast;
	vec3_t autoAxisFast[3];
	refDef_t refdef;
	vec3_t playerHeadPos;
	vec3_t refdefViewAngles;
	vec3_t currentViewPos;
	vec3_t currentViewAngles;
	float currentViewHeight;
	float currentViewBobPhase;
	float currentViewBobAmp;
	dtiki_t *lastPlayerWorldModel;
	dtiki_t *playerFPSModel;
	int playerFPSModelHandle;
	int fpsModelLastFrame;
	int fpsOnGround;
	dtiki_t *alliedPlayerModel;
	int alliedPlayerModelHandle;
	dtiki_t *axisPlayerModel;
	int axisPlayerModelHandle;
	vec3_t offsetViewAngles;
	vec3_t lastHeadAngles;
	vec3_t lastViewAngles;
	vec3_t eyeOffsetMax;
	float eyeOffsetFrac;
	vec3_t soundOrg;
	vec3_t soundAxis[3];
	vec3_t cameraOrigin;
	vec3_t cameraAngles;
	float cameraFov;
	float zoomSensitivity;
	int intermissionDisplay;
	int scoresRequestTime;
	int showScores;
	char scoresMenuName[256];
	int instaMessageMenu;
	int centerPrintTime;
	int centerPrintCharWidth;
	int centerPrintY;
	char centerPrint[1024];
	int centerPrintLines;
	int matchStartTime;
	refEntity_t testModelEntity;
	char testModelName[MAX_QPATH];
	int testGun;
	float farplaneDistance;
	float farplaneColor[3];
	int farplaneCull;
	int skyPortal;
	float skyAlpha;
	vec3_t skyOrigin;
	vec3_t skyAxis[3];
	vec2_t viewKick;
	float viewKickRecenter;
	float viewKickMinDecay;
	float viewKickMaxDecay;
	objective_t objectives[MAX_OBJECTIVES];
	float objectivesAlphaTime;
	float objectivesBaseAlpha;
	float objectivesDesiredAlpha;
	float objectivesCurrentAlpha;
	rain_t rain;
	clientInfo_t clientinfo[MAX_CLIENTS];

} cg_t;
*/

typedef struct clientSnapshotAA_s
{
  int areabytes;
  unsigned char areabits[32];
  playerStateAA_t ps;
  int num_entities;
  int first_entity;
  int messageSent;
  int messageAcked;
  int messageSize;

} clientSnapshotAA_t;

typedef struct clientSnapshotDSH_s
{
	int areabytes;
	unsigned char areabits[32];
	playerStateDSH_t ps;
	int num_entities;
	int first_entity;
	int messageSent;
	int messageAcked;
	int messageSize;

} clientSnapshotDSH_t;

typedef clientSnapshotDSH_t clientSnapshotDBT_t;

typedef struct netChan_s
{
	netSrc_t sock;
	int dropped;
	netAdr_t remoteAddress;
	int qport;
	int incomingSequence;
	int outgoingSequence;
	int fragmentSequence;
	int fragmentLength;
	BYTE fragmentBuffer[MAX_MSGLEN];
	qboolean unsentFragments;
	int unsentFragmentStart;
	int unsentLength;
	BYTE unsentBuffer[MAX_MSGLEN];

} netChan_t;

typedef struct clientDSH_s
{
	clientState_t state;//extra in bt
	char userinfo[MAX_INFOSTRING];
	int reliableSequence;
	int reliableAcknowledge;
	char reliableCommands[MAX_RELIABLECOMMANDS][MAX_STRINGCHARS];
	int reliableSent;
	int messageAcknowledge;
	int gamestateMessageNum;
	int challenge;
	DWORD filler2;//extra in bt
	struct usercmd_s lastUsercmd;
	struct userEyes_s lastEyeinfo;
	int lastMessageNum;
	int lastClientCommand;
	char  lastClientCommandString[MAX_STRINGCHARS];
	struct gentity_s *gentity;
	char name[MAX_NAMELENGTH];
	char downloadName[MAX_QPATH];
	fileHandle_t download;
	int downloadSize;
	int downloadCount;
	int downloadClientBlock;
	int downloadCurrentBlock;
	int downloadXmitBlock;
	unsigned char *downloadBlocks[MAX_DOWNLOADWINDOW];
	int downloadBlockSize[MAX_DOWNLOADWINDOW];
	qboolean downloadEOF;
	int downloadSendTime;
	int deltaMessage;
	int nextReliableTime;
	int lastPacketTime;
	int lastConnectTime;
	int nextSnapshotTime;
	qboolean rateDelayed;
	int timeoutCount;
	clientSnapshotDSH_t frames[PACKET_BACKUP];
	int ping;
	int rate;
	int snapshotMsec;
	netChan_t netchan;
	BYTE filler3[1680];//extra in bt
	server_sound_t sounds[MAX_SOUNDS];
	int numberOfSounds;
	qboolean locprint;
	int locprintX;
	int locprintY;
	char stringToPrint[256];
	BYTE filler4[524];//extra in bt
} clientDSH_t;
typedef clientDSH_t clientDBT_t;

typedef struct clientAA_s
{
	clientState_t state;
	char userinfo[MAX_INFOSTRING];
	int reliableSequence;
	int reliableAcknowledge;
	char reliableCommands[MAX_RELIABLECOMMANDS][MAX_STRINGCHARS];
	int reliableSent;
	int messageAcknowledge;
	int gamestateMessageNum;
	int challenge;
	struct usercmd_s lastUsercmd;
	struct userEyes_s lastEyeinfo;
	int lastMessageNum;
	int lastClientCommand;
	char  lastClientCommandString[MAX_STRINGCHARS];
	struct gentity_s* gentity;
	char name[MAX_NAMELENGTH];
	char downloadName[MAX_QPATH];
	fileHandle_t download;
	int downloadSize;
	int downloadCount;
	int downloadClientBlock;
	int downloadCurrentBlock;
	int downloadXmitBlock;
	unsigned char* downloadBlocks[MAX_DOWNLOADWINDOW];
	int downloadBlockSize[MAX_DOWNLOADWINDOW];
	qboolean downloadEOF;
	int downloadSendTime;
	int deltaMessage;
	int nextReliableTime;
	int lastPacketTime;
	int lastConnectTime;
	int nextSnapshotTime;
	qboolean rateDelayed;
	int timeoutCount;
	clientSnapshotAA_t frames[PACKET_BACKUP];
	int ping;
	int rate;
	int snapshotMsec;
	netChan_t netchan;
	server_sound_t sounds[MAX_SOUNDS];
	int numberOfSounds;
	qboolean locprint;
	int locprintX;
	int locprintY;
	char stringToPrint[256];
} clientAA_t;

//DO NOT USE AS DATA MEMBER.
//wrapper class for clientAA_t/clientDSH_t/clientDBT_t
class Client
{
	union realClientType
	{
		clientAA_t clientAA;
		clientDSH_t clientDSH;
		clientDBT_t clientDBT;
	};
	realClientType* realClient;
public:
	Client(void* client)
		: realClient((realClientType*)client)
	{
	}

	operator void* ()
	{
		return (void*)realClient;
	}

	Client* operator ->()
	{
		return this;
	}
};
typedef struct svEntity_s
{
	struct worldSector_s *worldSector;
	struct svEntity_s *nextEntityInWorldSector;
	entityState_t baseline;
	int numClusters;
	int clusternums[16];
	int lastCluster;
	int areanum;
	int areanum2;
	int snapshotCounter;
} svEntity_t;

typedef struct worldSector_s
{
	int axis;
	float dist;
	struct worldSector_s *children[2];
	svEntity_t *entities;

} worldSector_t;

typedef struct areaParms_s
{
	float *mins;
	float *maxs;
	int *list;
	int count;
	int maxcount;

} areaParms_t;

typedef struct pointer_fixup_s
{
  void **ptr;
  int index;
  int type;

} pointer_fixup_t;

typedef struct prof_var_s
{
  int start;
  int clockcycles;
  int calls;
  float time;
  float totTime;
  float avgTime;
  float low;
  float high;

} prof_var_t;

typedef struct prof_game_s
{
  prof_var_t AI;
  prof_var_t MmoveSingle;
  prof_var_t thread_timingList;
  prof_var_t gamescripts;
  prof_var_t GProbe1;
  prof_var_t GProbe2;
  prof_var_t GProbe3;
  prof_var_t FindPath;
  prof_var_t vector_length;
  prof_var_t script_trace;
  prof_var_t internal_trace;
  prof_var_t PreAnimate;
  prof_var_t PostAnimate;

} prof_game_t;

typedef struct prof_cgame_s
{
  prof_var_t CG_AddCEntity;
  prof_var_t CG_DrawActiveFrame;
  prof_var_t CG_AddPacketEntities;
  prof_var_t CG_DrawActive;
  prof_var_t CG_EntityShadow;
  prof_var_t CG_Rain;
  prof_var_t CG_AddBeams;
  prof_var_t CG_ModelAnim;
  prof_var_t CG_ProcessSnapshots;
  prof_var_t CProbe1;
  prof_var_t CProbe2;
  prof_var_t CProbe3;

} prof_cgame_t;

typedef struct prof_exe_s
{
  prof_var_t CL_Frame;
  prof_var_t S_Update;
  prof_var_t RE_RenderScene;
  prof_var_t SCR_UpdateScreen;
  prof_var_t UpdateStereoSide;
  prof_var_t UI_Update;
  prof_var_t UpdateViews;
  prof_var_t Display;
  prof_var_t Display_1;
  prof_var_t Display_2;
  prof_var_t Display_3;
  prof_var_t GetAllBonesFrame;
  prof_var_t rb_surfaceTable;
  prof_var_t RB_DrawTerrainTris;
  prof_var_t RB_BeginSurface;
  prof_var_t RB_EndSurface;
  prof_var_t RB_RenderDrawSurfList;
  prof_var_t RB_SkelMesh;
  prof_var_t RB_StaticMesh;
  prof_var_t RB_DrawBuffer;
  prof_var_t R_AddEntitySurfaces;
  prof_var_t R_AddStaticModelSurfaces;
  prof_var_t R_AddTerrainSurfaces;
  prof_var_t R_AddWorldSurfaces;
  prof_var_t R_MarkLeaves;
  prof_var_t R_RecursiveWorldNode;
  prof_var_t R_RenderView;
  prof_var_t SphereLighting;
  prof_var_t SV_Frame;
  prof_var_t RB_ExecuteRenderCommands;
  prof_var_t Probe1;
  prof_var_t Probe2;
  prof_var_t Probe3;
  prof_var_t R_IssueRenderCommands;
  prof_var_t R_AddSkelSurfaces;
  prof_var_t EndFrame;
  prof_var_t LocBasedDmg;
  prof_var_t Total;
  prof_var_t SV_BuildClientSnapshot;
  prof_var_t SV_AddEntitiesVisibleFromPoint;
  prof_var_t CopySnapshot;
  prof_var_t CL_ParseSnapshot;

} prof_exe_t;

typedef struct prof_s
{
  float time;
  prof_var_t winTime;
  prof_var_t start_game;
  prof_var_t AI;
  prof_var_t MmoveSingle;
  prof_var_t thread_timingList;
  prof_var_t gamescripts;
  prof_var_t GProbe1;
  prof_var_t GProbe2;
  prof_var_t GProbe3;
  prof_var_t FindPath;
  prof_var_t vector_length;
  prof_var_t script_trace;
  prof_var_t internal_trace;
  prof_var_t PreAnimate;
  prof_var_t PostAnimate;
  prof_var_t start_cgame;
  prof_var_t CG_AddCEntity;
  prof_var_t CG_DrawActiveFrame;
  prof_var_t CG_AddPacketEntities;
  prof_var_t CG_DrawActive;
  prof_var_t CG_EntityShadow;
  prof_var_t CG_Rain;
  prof_var_t CG_AddBeams;
  prof_var_t CG_ModelAnim;
  prof_var_t CG_ProcessSnapshots;
  prof_var_t CProbe1;
  prof_var_t CProbe2;
  prof_var_t CProbe3;
  prof_var_t start_exe;
  prof_var_t CL_Frame;
  prof_var_t S_Update;
  prof_var_t RE_RenderScene;
  prof_var_t SCR_UpdateScreen;
  prof_var_t UpdateStereoSide;
  prof_var_t UI_Update;
  prof_var_t UpdateViews;
  prof_var_t Display;
  prof_var_t Display_1;
  prof_var_t Display_2;
  prof_var_t Display_3;
  prof_var_t GetAllBonesFrame;
  prof_var_t rb_surfaceTable;
  prof_var_t RB_DrawTerrainTris;
  prof_var_t RB_BeginSurface;
  prof_var_t RB_EndSurface;
  prof_var_t RB_RenderDrawSurfList;
  prof_var_t RB_SkelMesh;
  prof_var_t RB_StaticMesh;
  prof_var_t RB_DrawBuffer;
  prof_var_t R_AddEntitySurfaces;
  prof_var_t R_AddStaticModelSurfaces;
  prof_var_t R_AddTerrainSurfaces;
  prof_var_t R_AddWorldSurfaces;
  prof_var_t R_MarkLeaves;
  prof_var_t R_RecursiveWorldNode;
  prof_var_t R_RenderView;
  prof_var_t SphereLighting;
  prof_var_t SV_Frame;
  prof_var_t RB_ExecuteRenderCommands;
  prof_var_t Probe1;
  prof_var_t Probe2;
  prof_var_t Probe3;
  prof_var_t R_IssueRenderCommands;
  prof_var_t R_AddSkelSurfaces;
  prof_var_t EndFrame;
  prof_var_t LocBasedDmg;
  prof_var_t Total;
  prof_var_t SV_BuildClientSnapshot;
  prof_var_t SV_AddEntitiesVisibleFromPoint;
  prof_var_t CopySnapshot;
  prof_var_t CL_ParseSnapshot;

} prof_t;


typedef struct Weapon_s
{
  //struct weapvtable_s *vtable;
  DWORD vtable;
  DWORD owner;
  DWORD respawnable; //0x0008
  DWORD ID02A14990; //0x000C
  char unknown16[1040]; //0x0010
  DWORD weaponstate_dum; //0x0420
  char unknown1060[40]; //0x0424
  DWORD weap_state_dum; //0x044C
  char unknown1104[56]; //0x0450

  /*
  int m_iAnimSlot;
  qboolean attached;
  float nextweaponsoundtime;
  float m_fLastFireTime;
  str current_attachToTag;
  str attachToTag_main;
  str attachToTag_offhand;
  str holster_attachToTag;
  float lastScale;
  Vector lastAngles;
  qboolean lastValid;
  qboolean auto_putaway;			// This isn't sure so dummy in place of this
  qboolean use_no_ammo;
  qboolean crosshair;
  int m_iZoom;
  float m_fZoomSpreadMult;
  qboolean m_bAutoZoom;
  qboolean m_bSemiAuto;
  float maxrange;
  float minrange;
  str viewmodel;
  weaponstate_t weaponstate;
  */

  int rank;
  int order;
  //SentientPtr last_owner;
  int last_owner;
  float last_owner_trigger_time;
  qboolean notdroppable;
  int aimanim;
  int aimframe;
  Vector holsterOffset;
  Vector holsterAngles;
  float holsterScale;
  float next_noise_time;
  float next_noammo_time;
  qboolean m_bShouldReload;
  float fire_delay[2];
  str ammo_type[2];
  int ammorequired[2];
  int startammo[2];
  str projectileModel[2];
  float bulletdamage[2];
  float bulletcount[2];
  float bulletrange[2];
  float bulletknockback[2];
  float projectilespeed[2];
  Vector bulletspread[2];
  Vector bulletspreadmax[2];
  firetype_t firetype[2];
  int ammo_clip_size[2];
  int ammo_in_clip[2];
  float max_charge_time[2];
  float min_charge_time[2];
  meansOfDeath_t meansofdeath[2];
  int loopfire[2];
  str worldhitspawn[2];
  int tracerfrequency[2];
  int tracercount[2];
  Vector viewkickmin[2];
  Vector viewkickmax[2];
  int quiet[2];
  float m_fFireSpreadMultAmount[2];
  float m_fFireSpreadMultFalloff[2];
  float m_fFireSpreadMultCap[2];
  float m_fFireSpreadMultTimeCap[2];
  float m_fFireSpreadMultTime[2];
  float m_fFireSpreadMult[2];
  qboolean m_bShareClip;
  qboolean m_bCanPartialReload;
  qboolean autoaim;
  float charge_fraction;
  qboolean putaway;
  firemode_t firemodeindex;
  int weapon_class;
  const_str_t m_csWeaponGroup;
  float m_fMovementSpeed;
  str m_sAmmoPickupSound;
  str m_NoAmmoSound;
  int m_iNumShotsFired;
  int m_iNumHits;
  float m_fAccuracy;
  float m_fTimeUsed;
  int m_iNumHeadShots;
  int m_iNumTorsoShots;
  int m_iNumLeftLegShots;
  int m_iNumRightLegShots;
  int m_iNumGroinShots;
  int m_iNumLeftArmShots;
  int m_iNumRightArmShots;

} Weapon_t;

struct SafePtr_s
{
    struct SafePtr_s *prev;
    struct SafePtr_s *next;
};

#ifdef MOHAA_2

typedef struct Animate_s
{
	struct Entity_s baseEntity;
	DWORD dummy[70];

} Animate;



typedef struct Container_s
{
  struct SafePtr_s *objlist;
  int numobjects;
  int maxobjects;

} Container_t;

typedef struct Sentient_s
{
    //DWORD dummy1[247];
	struct Animate_s baseAnimate;
	DWORD dummy1[22];
	struct SafePtr_s activeWeaponList[2];
	DWORD dummy2[42];
    struct SafePtr_s m_pTurret;
    struct SafePtr_s m_pLadder;
    DWORD dummy3[60];
    qboolean m_bFootOnGround_Right; //originally a bool
    qboolean m_bFootOnGround_Left; //originally a bool

} Sentient;

#endif // MOHAA_2
typedef struct State_s
{
    DWORD dummy[2];
    DWORD condition_indexes[3];
    DWORD statemap[1];
    str name;
    str nextState;
    movecontrol_t movetype;
    cameratype_t cameratype;
    float minTime;
    float maxTime;
    DWORD legAnims[3];
    DWORD m_ActionAnims[3];
    int m_iActionAnimType;
    DWORD states[3];
    DWORD entryCommands[3];
    DWORD exitCommands[3];

} State;

typedef struct Event_GAMEDLL_s //not complete
{
	DWORD dummy[2];
	qboolean fromScript;
	short unsigned int eventnum;
	short unsigned int dataSize;
    DWORD *dummy2;

} Event_GAMEDLL;

/*
typedef struct Player_s
{
	struct Sentient_s baseSentient;
	DWORD dummy1[2];
    State *currentState_Legs;
    State *currentState_Torso;
	str last_torso_anim_name;
	str last_leg_anim_name;
	str partAnim[2];
	int m_iPartSlot[2];
	float m_fPartBlends[2];
	str partOldAnim[2];
	float partBlendMult[2];
	qboolean animdone_Legs;
	qboolean animdone_Torso;
	DWORD dummy2[4];
	float m_fLastDeltaTime;
	qboolean m_bActionAnimPlaying;
	int m_iBaseActionAnimSlot;
	str m_sActionAnimName;
	int m_iActionAnimType;
	qboolean m_bActionAnimDone;
	str m_sOldActionAnimName;
	float m_fOldActionAnimWeight;
	float m_fOldActionAnimFadeTime;
	int m_iOldActionAnimType;
	qboolean m_bMovementAnimPlaying;
	int m_iBaseMovementAnimSlot;
	str m_sMovementAnimName;
	str m_sOldMovementAnimName;
	float m_fOldMovementWeight;
	float m_fOldMovementFadeTime;
	str m_sSlotAnimNames[16];
	movecontrol_t movecontrol;
    int m_iMovePosFlags;
	int last_camera_type;
	vec3_t oldvelocity;
	vec3_t old_v_angle;
	vec3_t oldorigin;
	float animspeed;
	float airspeed;
	vec3_t m_vPushVelocity;
	float blend[4];
	float fov;
	float selectedfov;
	qboolean m_iInZoomMode;
	vec3_t vAngle;
	vec3_t vViewPos;
	vec3_t vViewAngle;
    int buttons;
    int newButtons;
    int serverNewButtons;
	float respawn_time;
	int lastAttackButton;
	float damage_blood;
	float damage_alpha;
	vec3_t damage_blend;
	vec3_t damage_from;
	vec3_t damage_angles;
	float damage_count;
	float damage_yaw;
	float next_painsound_time;
	str waitForState;
	DWORD dummy3[3];
	qboolean actor_camera_right;
	qboolean starting_actor_camera_right;
	int music_current_mood;
	int music_fallback_mood;
	float music_current_volume;
	float music_saved_volume;
	float music_volume_fade_time;
	int reverb_type;
	float reverb_level;
	qboolean gibbed;
	float pain;
	painDirection_t pain_dir;
	meansOfDeath_t pain_type;
	int pain_location;
	qboolean take_pain;
	int nextpaintime;
	qboolean knockdown;
	qboolean canfall;
	qboolean falling;
	int feetfalling;
	vec3_t falldir;
	qboolean mediumimpact;
	qboolean hardimpact;
	qboolean music_forced;
	userCmd_t lastUcmd;
	userEyes_t lastEyeInfo;
	float animheight;
	vec3_t yaw_forward;
	vec3_t yaw_left;
	DWORD dummy4[1];
    float atobject_dist;
	Vector atobject_dir;
	DWORD dummy5[1];
	int useanim_numloops;
	DWORD dummy6[1];
	float move_left_vel;
	float move_right_vel;
	float move_backward_vel;
	float move_forward_vel;
	float move_up_vel;
	float move_down_vel;
	int moveresult;
	float damage_multiplier;
	voicetype_t m_voiceType;
	int num_deaths;
	int num_kills;
	int num_won_matches;
	int num_lost_matches;
	qboolean m_bTempSpectator;
	qboolean m_bSpectator;
	qboolean m_bAllowFighting;
	qboolean m_bReady;
	int m_iPlayerSpectating;
	teamType_t dm_team;
	struct SafePtr_s teamPtr;
    float m_fTeamSelectTime;
	DWORD *lastSpawnpoint;
	DWORD dummy10[28];
	//these are one-life and single-player only
	int statsHitsTaken;
	int statsEnemiesKilled;
	int statsObjectsDestroyed;
	int statsShotsFired;
	int statsHits;
	float statsAccuracy;
	float statsTimeUsed;
	int statsHeadShots;
	int statsTorsoShots;
	int statsLeftLegShots;
	int statsRightLegShots;
	int statsGroinShots;
	int statsLeftArmShots;
	int statsRightArmShots;

} Player;
*/


typedef struct refImport_s
{
	void ( *Printf )( char *format, ... );
	void ( *Error )( errorParm_t errorCode, char *format, ... );
	int ( *Milliseconds )( );
	char * ( *LV_ConvertString )( char *string );
	void ( *Hunk_Clear )( );
	void * ( *Hunk_Alloc )( int size );
	void * ( *Hunk_AllocateTempMemory )( int size );
	void ( *Hunk_FreeTempMemory )( void *buffer );
	void * ( *Malloc )( int size );
	void ( *Free )( void *ptr );
	void ( *Clear )( );
	cvar_t * ( *Cvar_Get )( char *varName, char *varValue, int varFlags );
	void ( *Cvar_Set )( char *varName, char *varValue );
	void ( *Cvar_SetDefault )( cvar_t *var, char *varValue );
	void ( *Cmd_AddCommand )( char *cmdName, xcommand_t cmdFunction );
	void ( *Cmd_RemoveCommand )( char *cmdName );
	int ( *Argc )( );
	char * ( *Argv )( int arg );
	void ( *Cmd_ExecuteText )( cbufExec_t execWhen, char *text );
	void ( *CM_DrawDebugSurface )( void ( *drawPoly )( ) );
	int ( *FS_OpenFile )( char *qpath, fsMode_t mode );
	int ( *FS_Read )( void *buffer, int len, fileHandle_t fileHandle );
	void ( *FS_CloseFile )( fileHandle_t fileHandle );
	int ( *FS_Seek )( fileHandle_t fileHandle, long int offset, fsOrigin_t origin );
	int ( *FS_FileIsInPAK )( char *fileName, int *checksum );
	int ( *FS_ReadFile )( char *qpath, void **buffer );
	int ( *FS_ReadFileEx )( char *qpath, void **buffer, qboolean quiet );
	void ( *FS_FreeFile )( void *buffer );
	char ** ( *FS_ListFiles )( char *qpath, char *extension, qboolean wantSubs, int *numFiles );
	void ( *FS_FreeFileList )( char **list );
	int ( *FS_WriteFile )( char *qpath, void *buffer, int size );
	qboolean ( *FS_FileExists )( char *file );
	void ( *CM_BoxTrace )( trace_t *results, vec3_t start, vec3_t end, vec3_t mins, vec3_t maxs, int model, int brushMask, int cylinder );
	int ( *CM_TerrainSquareType )( int terrainPatch, int i, int j );
	char * ( *CM_EntityString )( );
	char * ( *CM_MapTime )( );
	int ( *CG_PermanentMark )( vec3_t origin, vec3_t dir, float orientation, float sScale, float tScale, float red, float green, float blue, float alpha, qboolean doLighting, float sCenter, float tCenter, markFragment_t *markFragments, void *polyVerts );
	int ( *CG_PermanentTreadMarkDecal )( treadMark_t *treadMark, qboolean startSegment, qboolean doLighting, markFragment_t *markFragments, void *polyVerts );
	int ( *CG_PermanentUpdateTreadMark )( treadMark_t *treadMark, float alpha, float minSegment, float maxSegment, float maxOffset, float texScale );
	void ( *CG_ProcessInitCommands )( dtiki_t *tiki, refEntity_t *ent );
	void ( *CG_EndTiki )( dtiki_t *tiki );
	void ( *SetPerformanceCounters )( int totalTris, int totalVerts, int totalTexels, int worldTris, int worldVerts, int characterLights );

	debugLine_t **debugLines;
	int *numDebugLines;
	debugString_t **debugStrings;
	int *numDebugStrings;

	orientation_t ( *TIKI_OrientationInternal )( dtiki_t *tiki, int entNum, int tagNum, float scale );
	qboolean ( *TIKI_IsOnGroundInternal )( dtiki_t *tiki, int entNum, int tagNum, float thresHold );
	void ( *TIKI_SetPoseInternal )( void *skeletor, frameInfo_t *frameInfo, int *boneTag, vec4_t boneQuat[4], float actionWeight );
	void * ( *TIKI_Alloc )( int size );
	float ( *GetRadiusInternal )( dtiki_t *tiki, int entNum, float scale );
	float ( *GetCentroidRadiusInternal )( dtiki_t *tiki, int entNum, float scale, vec3_t centroid );
	void ( *GetFrameInternal )( dtiki_t *tiki, int entNum, skelAnimFrame_t *newFrame );

} refImport_t;

typedef struct refExport_s
{
	void ( *Shutdown )( );
	void ( *BeginRegistration )( glConfig_t *glConfigOut );
	qhandle_t ( *RegisterModel )( char *name );
	qhandle_t ( *SpawnEffectModel )( char *name, vec3_t pos, vec3_t axis[3] );
	qhandle_t ( *RegisterServerModel )( char *name );
	void ( *UnregisterServerModel )( qhandle_t model );
	qhandle_t ( *RegisterShader )( char *name );
	qhandle_t ( *RegisterShaderNoMip )( char *name );
	qhandle_t ( *RefreshShaderNoMip )( char *name );
	void ( *EndRegistration )( );
	void ( *FreeModels )( );
	void ( *SetWorldVisData )( BYTE *vis );
	void ( *LoadWorld )( char *name );
	void ( *PrintBSPFileSizes )( );
	int ( *MapVersion )( );
	void ( *ClearScene )( );
	void ( *AddRefEntityToScene )( refEntity_t *ent, int parentEntityNumber );
	void ( *AddRefSpriteToScene )( refEntity_t *ent );
	qboolean ( *AddPolyToScene )( qhandle_t hShader, int numVerts, polyVert_t *verts, int renderFx );
	void ( *AddTerrainMarkToScene )( int terrainIndex, qhandle_t hShader, int numVerts, polyVert_t *verts, int renderfx );
	void ( *AddLightToScene )( vec3_t org, float intensity, float r, float g, float b, dlightType_t type );
	void ( *RenderScene )( refDef_t *fd );
	refEntity_t * ( *GetRenderEntity )( int entityNumber );
	void ( *SavePerformanceCounters )( );
	void ( *SetColor )( vec4_t color );
	void ( *Set2DWindow )( int x, int y, int w, int h, float left, float right, float bottom, float top, float n, float f );
	void ( *DrawStretchPic )( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );
	void ( *DrawTilePic )( float x, float y, float w, float h, qhandle_t hShader );
	void ( *DrawTilePicOffset )( float x, float y, float w, float h, qhandle_t hShader, int offsetX, int offsetY );
	void ( *DrawTrianglePic )( vec2_t *points, vec2_t *texCoords, qhandle_t hShader );
	void ( *DrawBackground )( int cols, int rows, int bgr, BYTE *data );
	void ( *DrawStretchRaw )( int x, int y, int w, int h, int cols, int rows, int components, BYTE *data );
	void ( *DebugLine )( vec3_t start, vec3_t end, float r, float g, float b, float alpha );
	void ( *DrawBox )( float x, float y, float w, float h );
	void ( *AddBox )( float x, float y, float w, float h );
	void ( *BeginFrame )( stereoFrame_t stereoFrame );
	void ( *Scissor )( int x, int y, int width, int height );
	void ( *DrawLineLoop )( vec2_t *points, int count, int stippleFactor, int stippleMask );
	void ( *EndFrame )( int *frontEndMsec, int *backEndMsec );
	int ( *MarkFragments )( int numPoints, vec3_t *points, vec3_t projection, int maxPoints, float *pointBuffer, int maxFragments, markFragment_t *fragmentBuffer, float radiusSquared );
	int ( *MarkFragmentsForInlineModel )( clipHandle_t bmodel, vec3_t angles, vec3_t origin, int numPoints, vec3_t *points, vec3_t projection, int maxPoints, float *pointBuffer, int maxFragments, markFragment_t *fragmentBuffer, float radiusSquared );
	void ( *GetInlineModelBounds )( int index, vec3_t mins, vec3_t maxs );
	void ( *GetLightingForDecal )( vec3_t light, vec3_t facing, vec3_t origin );
	void ( *GetLightingForSmoke )( vec3_t light, vec3_t origin );
	int ( *R_GatherLightSources )( vec3_t pos, vec3_t *lightPos, vec3_t *lightIntensity, int maxLights );
	void ( *ModelBounds )( qhandle_t handle, vec3_t mins, vec3_t maxs );
	float ( *ModelRadius )( qhandle_t handle );
	dtiki_t * ( *R_Model_GetHandle )( qhandle_t handle );
	void ( *DrawString )( fontHeader_t *font, char *text, float x, float y, int maxLen, qboolean virtualScreen );
	float ( *GetFontHeight )( fontHeader_t *font );
	float ( *GetFontStringWidth )( fontHeader_t *font, char *string );
	fontHeader_t * ( *LoadFont )( char *name );
	void ( *SwipeBegin )( float thisTime, float life, qhandle_t hShader );
	void ( *SwipePoint )( vec3_t point1, vec3_t point2, float time );
	void ( *SwipeEnd )( );
	void ( *SetRenderTime )( int t );
	float ( *Noise )( vec3_t vec, int len );
	qboolean ( *SetMode )( int mode, glConfig_t *glConfig );
	void ( *SetFullscreen )( qboolean fullScreen );
	int ( *GetShaderWidth )( qhandle_t hShader );
	int ( *GetShaderHeight )( qhandle_t hShader );
	char * ( *GetGraphicsInfo )( );
	void ( *ForceUpdatePose )( refEntity_t *model );
	orientation_t ( *TIKI_Orientation )( refEntity_t *model, int tagNum );
	qboolean ( *TIKI_IsOnGround )( refEntity_t *model );
	void ( *SetFrameNumber )( int frameNumber );

} refExport_t;
/*
typedef struct clientGameImport_s
{
	int apiVersion;

	void ( *Printf )( char *fmt, ... );
	void ( *DPrintf )( char *fmt, ... );
	void ( *DebugPrintf )( char *fmt, ... );
	void * ( *Malloc )( int size );
	void ( *Free )( void *ptr );
	void ( *Error )( errorParm_t code, char *fmt, ... );
	int ( *Milliseconds )( );
	char * ( *LV_ConvertString )( char *string );
	cvar_t * ( *Cvar_Get )( char *varName, char *varValue, int varFlags );
	void ( *Cvar_Set )( char *varName, char *varValue );
	int ( *Argc )( );
	char * ( *Argv )( int arg );
	char * ( *Args )( );
	void ( *AddCommand )( char *cmdName, xcommand_t cmdFunction );
	void ( *Cmd_Stuff )( const char *text );
	void ( *Cmd_Execute )( cbufExec_t execWhen, char *text );
	void ( *Cmd_TokenizeString )( char *textIn );
	int ( *FS_ReadFile )( char *qpath, void **buffer );
	void ( *FS_FreeFile )( void *buffer );
	int ( *FS_WriteFile )( char *qpath, void *buffer, int size );
	void ( *FS_WriteTextFile )( char *qpath, void *buffer, int size );
	void ( *SendConsoleCommand )( const char *text );
	int ( *MSG_ReadBits )( int bits );
	int ( *MSG_ReadChar )( );
	int ( *MSG_ReadByte )( );
	int ( *MSG_ReadSVC )( );
	int ( *MSG_ReadShort )( );
	int ( *MSG_ReadLong )( );
	float ( *MSG_ReadFloat )( );
	char * ( *MSG_ReadString )( );
	char * ( *MSG_ReadStringLine )( );
	float ( *MSG_ReadAngle8 )( );
	float ( *MSG_ReadAngle16 )( );
	void ( *MSG_ReadData )( void *data, int len );
	float ( *MSG_ReadCoord )( );
	void ( *MSG_ReadDir )( vec3_t dir );
	void ( *SendClientCommand )( const char *text );
	void ( *CM_LoadMap )( char *name );
	clipHandle_t ( *CM_InlineModel )( int index );
	int ( *CM_NumInlineModels )( );
	int ( *CM_PointContents )( vec3_t point, clipHandle_t model );
	int ( *CM_TransformedPointContents )( vec3_t point, clipHandle_t model, vec3_t origin, vec3_t angles );
	void ( *CM_BoxTrace )( trace_t *results, vec3_t start, vec3_t end, vec3_t mins, vec3_t maxs, int model, int brushMask, int cylinder );
	void ( *CM_TransformedBoxTrace )( trace_t *results, vec3_t start, vec3_t end, vec3_t mins, vec3_t maxs, int model, int brushMask, vec3_t origin, vec3_t angles, int cylinder );
	clipHandle_t ( *CM_TempBoxModel )( vec3_t mins, vec3_t maxs, int contents );
	void ( *CM_PrintBSPFileSizes )( );
	qboolean ( *CM_LeafInPVS )( int leaf1, int leaf2 );
	int ( *CM_PointLeafnum )( vec3_t p );
	int ( *R_MarkFragments )( int numPoints, vec3_t *points, vec3_t projection, int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t *fragmentBuffer, float fRadiusSquared );
	int ( *R_MarkFragmentsForInlineModel )( clipHandle_t bmodel, vec3_t vAngles, vec3_t vOrigin, int numPoints, vec3_t *points, vec3_t projection, int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t *fragmentBuffer, float fRadiusSquared );
	void ( *R_GetInlineModelBounds )( int index, vec3_t mins, vec3_t maxs );
	void ( *R_GetLightingForDecal )( vec3_t light, vec3_t facing, vec3_t origin );
	void ( *R_GetLightingForSmoke )( vec3_t light, vec3_t origin );
	int ( *R_GatherLightSources )( vec3_t pos, vec3_t *lightPos, vec3_t *lightIntensity, int maxLights );
	void ( *S_StartSound )( vec3_t origin, int entNum, int entChannel, sfxHandle_t sfxHandle, float volume, float minDist, float pitch, float maxDist, int streamed );
	void ( *S_StartLocalSound )( char *soundName, qboolean forceLoad );
	void ( *S_StopSound )( int entNum, int channel );
	void ( *S_ClearLoopingSounds )( );
	void ( *S_AddLoopingSound )( vec3_t origin, vec3_t velocity, sfxHandle_t sfxHandle, float volume, float minDist, float maxDist, float pitch, int flags );
	void ( *S_Respatialize )( int entityNum, vec3_t head, vec3_t axis[3] );
	void ( *S_BeginRegistration )( );
	sfxHandle_t ( *S_RegisterSound )( char *name, int streamed, qboolean forceLoad );
	void ( *S_EndRegistration )( );
	void ( *S_UpdateEntity )( int entityNum, vec3_t origin, vec3_t velocity, qboolean useListener );
	void ( *S_SetReverb )( int reverbType, float reverbLevel );
	void ( *S_SetGlobalAmbientVolumeLevel )( float volume );
	float ( *S_GetSoundTime )( sfxHandle_t handle );
	int ( *S_ChannelNameToNum )( char *name );
	char * ( *S_ChannelNumToName )( int channel );
	int ( *S_IsSoundPlaying )( int channelNumber, char *name );
	void ( *MUSIC_NewSoundtrack )( char *name );
	void ( *MUSIC_UpdateMood )( musicMood_t current, musicMood_t fallback );
	void ( *MUSIC_UpdateVolume )( float volume, float fadeTime );
	float * ( *get_camera_offset )( qboolean *lookActive, qboolean *resetView );
	void ( *R_ClearScene )( );
	void ( *R_RenderScene )( refDef_t *fd );
	void ( *R_LoadWorldMap )( char *name );
	void ( *R_PrintBSPFileSizes )( );
	int ( *MapVersion )( );
	int ( *R_MapVersion )( );
	qhandle_t ( *R_RegisterModel )( char *name );
	qhandle_t ( *R_SpawnEffectModel )( char *name, vec3_t pos, vec3_t axis[3] );
	qhandle_t ( *R_RegisterServerModel )( char *name );
	void ( *R_UnregisterServerModel )( qhandle_t hModel );
	qhandle_t ( *R_RegisterSkin )( char *name );
	qhandle_t ( *R_RegisterShader )( char *name );
	qhandle_t ( *R_RegisterShaderNoMip )( char *name );
	void ( *R_AddRefEntityToScene )( refEntity_t *ent, int parentEntityNumber );
	void ( *R_AddRefSpriteToScene )( refEntity_t *ent );
	void ( *R_AddLightToScene )( vec3_t org, float intensity, float r, float g, float b, dlightType_t type );
	qboolean ( *R_AddPolyToScene )( qhandle_t hShader, int numVerts, polyVert_t *verts, int renderFx );
	void ( *R_AddTerrainMarkToScene )( int terrainIndex, qhandle_t hShader, int numVerts, polyVert_t *verts, int renderFx );
	void ( *R_SetColor )( vec4_t rgba );
	void ( *R_DrawStretchPic )( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );
	fontHeader_t * ( *R_LoadFont )( const char *name );
	void ( *R_DrawString )( fontHeader_t *font, char *text, float x, float y, int maxLen, qboolean virtualScreen );
	refEntity_t * ( *R_GetRenderEntity )( int entityNumber );
	void ( *R_ModelBounds )( clipHandle_t model, vec3_t mins, vec3_t maxs );
	float ( *R_ModelRadius )( qhandle_t handle );
	float ( *R_Noise )( float x, float y, float z, float t );
	void ( *R_DebugLine )( vec3_t start, vec3_t end, float r, float g, float b, float alpha );
	baseShader_t * ( *GetShader )( int shaderNum );
	void ( *R_SwipeBegin )( float thistime, float life, qhandle_t shader );
	void ( *R_SwipePoint )( vec3_t point1, vec3_t point2, float time );
	void ( *R_SwipeEnd )( );
	int ( *R_GetShaderWidth )( qhandle_t hShader );
	int ( *R_GetShaderHeight )( qhandle_t hShader );
	void ( *R_DrawBox )( float x, float y, float w, float h );
	void ( *GetGameState )( gameState_t *gameState );
	int ( *GetSnapshot )( int snapshotNumber, snapshot_t *snapshot );
	int ( *GetServerStartTime )( );
	void ( *SetTime )( float time );
	void ( *GetCurrentSnapshotNumber )( int *snapshotNumber, int *serverTime );
	void ( *GetGlconfig )( glConfig_t *glConfig );
	qboolean ( *GetParseEntityState )( int parseEntityNumber, entityState_t *state );
	int ( *GetCurrentCmdNumber )( );
	qboolean ( *GetUserCmd )( int cmdNumber, userCmd_t *userCmd );
	qboolean ( *GetServerCommand )( int serverCommandNumber, qboolean differentServer );
	qboolean ( *Alias_Add )( char *alias, char *name, char *parameters );
	qboolean ( *Alias_ListAdd )( aliasList_t *list, char *alias, char *name, char *parameters );
	char * ( *Alias_FindRandom )( char *alias, aliasListNode_t **ret );
	char * ( *Alias_ListFindRandom )( aliasList_t *list, char *alias, aliasListNode_t **ret );
	void ( *Alias_Dump )( );
	void ( *Alias_Clear )( );
	aliasList_t * ( *AliasList_New )( char *name );
	void ( *Alias_ListFindRandomRange )( aliasList_t *list, char *alias, int *minIndex, int *maxIndex, float *totalWeight );
	aliasList_t * ( *Alias_GetGlobalList )( );
	void ( *UI_ShowMenu )( char *name, qboolean bForce );
	void ( *UI_HideMenu )( char *name, qboolean bForce );
	int ( *UI_FontStringWidth )( fontHeader_t *font, char *string, int maxLen );
	int ( *Key_StringToKeynum )( char *str );
	char * ( *Key_KeynumToBindString )( int keyNum );
	void ( *Key_GetKeysForCommand )( char *command, int *key1, int *key2 );
	dtiki_t * ( *R_Model_GetHandle )( qhandle_t handle );
	int ( *TIKI_NumAnims )( dtiki_t *pmdl );
	void ( *TIKI_CalculateBounds )( dtiki_t *pmdl, float scale, vec3_t mins, vec3_t maxs );
	char * ( *TIKI_Name )( dtiki_t *tiki, int entNum );
	void * ( *TIKI_GetSkeletor )( dtiki_t *tiki, int entNum );
	void ( *TIKI_SetEyeTargetPos )( dtiki_t *tiki, int entNum, vec3_t pos );
	char * ( *Anim_NameForNum )( dtiki_t *tiki, int animNum );
	int ( *Anim_NumForName )( dtiki_t *tiki, char *name );
	int ( *Anim_Random )( dtiki_t *tiki, char *name );
	int ( *Anim_NumFrames )( dtiki_t *tiki, int animNum );
	float ( *Anim_Time )( dtiki_t *tiki, int animNum );
	float ( *Anim_Frametime )( dtiki_t *tiki, int animNum );
	void ( *Anim_Delta )( dtiki_t *tiki, int animNum, vec3_t delta );
	int ( *Anim_Flags )( dtiki_t *tiki, int animNum );
	int ( *Anim_FlagsSkel )( dtiki_t *tiki, int animNum );
	float ( *Anim_CrossblendTime )( dtiki_t *tiki, int animNum );
	qboolean ( *Anim_HasCommands )( dtiki_t *tiki, int animNum );
	qboolean ( *Frame_Commands )( dtiki_t *tiki, int animNum, int frameNum, tikiCmd_t *tikiCmds );
	qboolean ( *Frame_CommandsTime )( dtiki_t *pmdl, int animNum, float start, float end, tikiCmd_t *tikiCmd );
	int ( *Surface_NameToNum )( dtiki_t *pmdl, char *name );
	int ( *Tag_NumForName )( dtiki_t *pmdl, char *name );
	char * ( *Tag_NameForNum )( dtiki_t *pmdl, int animNum );
	void ( *ForceUpdatePose )( refEntity_t *model );
	orientation_t ( *TIKI_Orientation )( orientation_t *orientation, refEntity_t *model, int tagNum );
	qboolean ( *TIKI_IsOnGround )( refEntity_t *model, int tagNum, float threshold );
	void ( *UI_ShowScoreBoard )( const char *menuName );
	void ( *UI_HideScoreBoard )( );
	void ( *UI_SetScoreBoardItem )( int itemNumber, char *data1, char *data2, char *data3, char *data4, char *data5, char *data6, char *data7, char *data8, float *textColor, float *backColor, qboolean isHeader );
	void ( *UI_DeleteScoreBoardItems )( int maxIndex );
	void ( *UI_ToggleDMMessageConsole )( int consoleMode );
	dtiki_t * ( *TIKI_FindTiki )( char *path );
	void ( *LoadResource )( char *name );
	void ( *FS_CanonicalFilename )( char *name );

	cvar_t *fsDebug;
	hdElement_t *hudDrawElements;
	clientAnim_t *anim;
	stopWatch_t *stopWatch;

} clientGameImport_t;

typedef struct clientGameExport_s
{
	void ( *CG_Init )( clientGameImport_t *imported, int serverMessageNum, int serverCommandSequence, int clientNum );
	void ( *CG_Shutdown )( );
	void ( *CG_DrawActiveFrame )( int serverTime, int frameTime, stereoFrame_t stereoView, qboolean demoPlayback );
	qboolean ( *CG_ConsoleCommand )( );
	void ( *CG_GetRendererConfig )( );
	void ( *CG_Draw2D )( );
	void ( *CG_EyePosition )( vec3_t *eyePos );
	void ( *CG_EyeOffset )( vec3_t *eyeOffset );
	void ( *CG_EyeAngles )( vec3_t *eyeAngles );
	float ( *CG_SensitivityScale )( );
	void ( *CG_ParseCGMessage )( );
	void ( *CG_RefreshHudDrawElements )( );
	void ( *CG_HudDrawShader )( int info );
	void ( *CG_HudDrawFont )( int info );
	int ( *CG_GetParent )( int entNum );
	float ( *CG_GetObjectiveAlpha )( );
	int ( *CG_PermanentMark )( vec3_t origin, vec3_t dir, float orientation, float sScale, float tScale, float red, float green, float blue, float alpha, qboolean doLighting, float sCenter, float tCenter, markFragment_t *markFragments, void *polyVerts );
	int ( *CG_PermanentTreadMarkDecal )( treadMark_t *treadMark, qboolean startSegment, qboolean doLighting, markFragment_t *markFragments, void *polyVerts );
	int ( *CG_PermanentUpdateTreadMark )( treadMark_t *treadMark, float alpha, float minSegment, float maxSegment, float maxOffset, float texScale );
	void ( *CG_ProcessInitCommands )( dtiki_t *tiki, refEntity_t *ent );
	void ( *CG_EndTiki )( dtiki_t *tiki );
	char * ( *CG_GetColumnName )( int columnNum, int *columnWidth );
	void ( *CG_GetScoreBoardColor )( float *red, float *green, float *blue, float *alpha );
	void ( *CG_GetScoreBoardFontColor )( float *red, float *green, float *blue, float *alpha );
	int ( *CG_GetScoreBoardDrawHeader )( );
	void ( *CG_GetScoreBoardPosition )( float *x, float *y, float *width, float *height );
	int ( *CG_WeaponCommandButtonBits )( );
	int ( *CG_CheckCaptureKey )( keyNum_t key, qboolean down, unsigned int time );

	profCGame_t *profStruct;

	qboolean ( *CG_Command_ProcessFile )( char *name, qboolean quiet, dtiki_t *curTiki );

} clientGameExport_t;
*/


typedef struct gameImportAA_s
{
	void(*Printf)(const char* format, ...);
	void(*DPrintf)(const char* format, ...);
	void(*DPrintf2)(const char* format, ...);
	void(*DebugPrintf)(const char* format, ...);
	void(*Error)(int level, const char* format, ...);
	int(*Milliseconds)();
	const char* (*LV_ConvertString)(const char* string);
	void* (*Malloc)(size_t size);
	void(*Free)(void* ptr);
	cvar_t* (*Cvar_Get)(const char* varName, const char* varValue, int varFlags);
	void (*Cvar_Set)(const char* varName, const char* varValue);
	cvar_t* (*cvar_set2)(const char* varName, const char* varValue, qboolean force);
	cvar_t* (*NextCvar)(cvar_t* var);
	int(*Argc)();
	char* (*Argv)(int arg);
	char* (*Args)();
	void(*AddCommand)(const char* cmdName, xcommand_t cmdFunction);
	int(*FS_ReadFile)(const char* qpath, void** buffer);// , qboolean quiet);< from FS_ReadFileEX
	void(*FS_FreeFile)(void* buffer);
	size_t(*FS_WriteFile)(const char* qpath, const void* buffer, size_t size);
	fileHandle_t(*FS_FOpenFileWrite)(const char* fileName);
	fileHandle_t(*FS_FOpenFileAppend)(const char* fileName);
	const char* (*FS_PrepFileWrite)(const char* fileName);
	size_t(*FS_Write)(void* buffer, size_t size, fileHandle_t fileHandle);
	size_t(*FS_Read)(void* buffer, size_t len, fileHandle_t fileHandle);
	void(*FS_FCloseFile)(fileHandle_t fileHandle);
	int(*FS_Tell)(fileHandle_t fileHandle);
	int(*FS_Seek)(fileHandle_t fileHandle, long int offset, fsOrigin_t origin);
	void(*FS_Flush)(fileHandle_t fileHandle);
	int(*FS_FileNewer)(const char* source, const char* destination);
	void(*FS_CanonicalFilename)(char* fileName);
	char** (*FS_ListFiles)(const char* qpath, const char* extension, qboolean wantSubs, int* numFiles);
	void(*FS_FreeFileList)(char** list);
	const char* (*GetArchiveFileName)(char* fileName, char* extension);
	void(*SendConsoleCommand)(const char* text);
	void(*DebugGraph)(float value, int color);
	void(*SendServerCommand)(int client, const char* format, ...);//shouldn't exceed 500 bytes
	void(*DropClient)(int client, const char* reason);
	void(*MSG_WriteBits)(int value, int bits);
	void(*MSG_WriteChar)(int c);
	void(*MSG_WriteByte)(int c);
	void(*MSG_WriteSVC)(int c);
	void(*MSG_WriteShort)(int c);
	void(*MSG_WriteLong)(int c);
	void(*MSG_WriteFloat)(float f);
	void(*MSG_WriteString)(const char* s);
	void(*MSG_WriteAngle8)(float f);
	void(*MSG_WriteAngle16)(float f);
	void(*MSG_WriteCoord)(float f);
	void(*MSG_WriteDir)(vec3_t dir);
	void(*MSG_StartCGM)(int type);
	void(*MSG_EndCGM)();
	void(*MSG_SetClient)(int client);
	void(*SetBroadcastVisible)(vec3_t pos, vec3_t posB);
	void(*SetBroadcastHearable)(vec3_t pos, vec3_t posB);
	void(*SetBroadcastAll)();
	void(*SetConfigstring)(int index, const char* val);
	char* (*GetConfigstring)(int index);
	void(*SetUserinfo)(int index, char* val);
	void(*GetUserinfo)(int index, char* buffer, int bufferSize);
	void(*SetBrushModel)(gentityAA_t* ent, const char* name);
	void(*ModelBoundsFromName)(char* name, vec3_t mins, vec3_t maxs);
	qboolean(*SightTraceEntity)(gentityAA_t* touch, vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int contentMask, qboolean cylinder);
	qboolean(*SightTrace)(vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int passEntityNum, int passEntityNum2, int contentMask, qboolean cylinder);
	void(*Trace)(trace_t* results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask, qboolean cylinder, qboolean traceDeep);
	baseShader_t* (*GetShader)(int shaderNum);
	int(*PointContents)(const vec3_t p, int passEntityNum);
	int(*PointBrushnum)(vec3_t p, clipHandle_t model);
	void(*AdjustAreaPortalState)(gentityAA_t* ent, qboolean open);
	int(*AreaForPoint)(vec3_t pos);
	qboolean(*AreasConnected)(int area1, int area2);
	qboolean(*InPVS)(float* p1, float* p2);
	void(*LinkEntity)(gentityAA_t* gEnt);
	void(*UnlinkEntity)(gentityAA_t* gEnt);
	int(*AreaEntities)(const vec3_t mins, const vec3_t maxs, int* list, int maxcount);
	void(*ClipToEntity)(trace_t* tr, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int entityNum, int contentMask);
	int(*imageindex)(const char* name);
	int(*itemindex)(const char* name);
	int(*soundindex)(const char* name, int streamed);
	dtiki_t* (*TIKI_RegisterModel)(const char* path);
	dtiki_t* (*modeltiki)(const char* name);
	dtikianim_t* (*modeltikianim)(const char* name);
	void(*SetLightStyle)(int index, const char* data);
	const char* (*GameDir)();
	qboolean(*setmodel)(gentityAA_t* ent, const char* name);
	void(*clearmodel)(gentityAA_t* ent);
	int(*TIKI_NumAnims)(dtiki_t* tiki);
	int(*NumSurfaces)(dtiki_t* tiki);
	int(*NumTags)(dtiki_t* tiki);
	void(*CalculateBounds)(dtiki_t* tiki, float scale, vec3_t mins, vec3_t maxs);
	void* (*TIKI_GetSkeletor)(dtiki_t* tiki, int entNum);
	const char* (*Anim_NameForNum)(dtiki_t* tiki, int animNum);
	int(*Anim_NumForName)(dtiki_t* tiki, const char* name);
	int(*Anim_Random)(dtiki_t* tiki, const char* name);
	int(*Anim_NumFrames)(dtiki_t* tiki, int animNum);
	float(*Anim_Time)(dtiki_t* tiki, int animNum);
	float(*Anim_Frametime)(dtiki_t* tiki, int animNum);
	float(*Anim_CrossTime)(dtiki_t* tiki, int animNum);
	void(*Anim_Delta)(dtiki_t* tiki, int animNum, float* delta);
	qboolean(*Anim_HasDelta)(dtiki_t* tiki, int animNum);
	void(*Anim_DeltaOverTime)(dtiki_t* tiki, int animNum, float time1, float time2, float* delta);
	int(*Anim_Flags)(dtiki_t* tiki, int animNum);
	int(*Anim_FlagsSkel)(dtiki_t* tiki, int animNum);
	qboolean(*Anim_HasCommands)(dtiki_t* tiki, int animNum);
	int(*NumHeadModels)(const char* model);
	void(*GetHeadModel)(const char* model, int num, char* name);
	int(*NumHeadSkins)(const char* model);
	void(*GetHeadSkin)(const char* model, int num, char* name);
	qboolean(*Frame_Commands)(dtiki_t* tiki, int animNum, int frameNum, tiki_cmd_t* tikiCmds);
	int(*Surface_NameToNum)(dtiki_t* tiki, const char* name);
	const char* (*Surface_NumToName)(dtiki_t* tiki, int surfacenum);
	int(*Tag_NumForName)(dtiki_t* pmdl, const char* name);
	const char* (*Tag_NameForNum)(dtiki_t* pmdl, int tagNum);
	orientation_t(*TIKI_OrientationInternal)(dtiki_t* tiki, int entNum, int tagNum, float scale);
	void* (*TIKI_TransformInternal)(dtiki_t* tiki, int entNum, int tagNum);
	qboolean(*TIKI_IsOnGroundInternal)(dtiki_t* tiki, int entNum, int num, float threshold);
	void(*TIKI_SetPoseInternal)(dtiki_t* tiki, int entNum, frameInfo_t* frameInfo, int* boneTag, vec4_t* boneQuat, float actionWeight);
	const char* (*CM_GetHitLocationInfo)(int location, float* radius, float* offset);
	const char* (*CM_GetHitLocationInfoSecondary)(int location, float* radius, float* offset);
	qboolean(*Alias_Add)(dtiki_t* pmdl, const char* alias, const char* name, const char* parameters);
	const char* (*Alias_FindRandom)(dtiki_t* tiki, const char* alias, aliasListNode_t** ret);
	void(*Alias_Dump)(dtiki_t* tiki);
	void(*Alias_Clear)(dtiki_t* tiki);
	void(*Alias_UpdateDialog)(dtikianim_t* tiki, const char* alias);
	const char* (*TIKI_NameForNum)(dtiki_t* tiki);
	qboolean(*GlobalAlias_Add)(const char* alias, const char* name, const char* parameters);
	const char* (*GlobalAlias_FindRandom)(const char* alias, aliasListNode_t** ret);
	void(*GlobalAlias_Dump)();
	void(*GlobalAlias_Clear)();
	void(*centerprintf)(gentityAA_t* ent, const char* format, ...);
	void(*locationprintf)(gentityAA_t* ent, int x, int y, const char* format, ...);
	void(*Sound)(vec3_t* org, int entNum, int channel, const char* soundName, float volume, float minDist, float pitch, float maxDist, int streamed);
	void(*StopSound)(int entNum, int channel);
	float (*SoundLength)(int channel, const char* name);
	unsigned char* (*SoundAmplitudes)(int channel, const char* name);
	int(*S_IsSoundPlaying)(int channel, const char* name);
	short unsigned int(*CalcCRC)(unsigned char* start, int count);
	void** DebugLines;
	int* numDebugLines;
	void** DebugStrings;
	int* numDebugStrings;
	void(*LocateGameData)(gentityAA_t* gEnts, int numGEntities, int sizeofGEntity, playerStateAA_t* clients, int sizeofGameClient);
	void(*SetFarPlane)(int farPlane);
	void(*SetSkyPortal)(qboolean skyPortal);
	void(*Popmenu)(int client, int i);
	void(*Showmenu)(int client, const char* name, qboolean force);
	void(*Hidemenu)(int client, const char* name, qboolean force);
	void(*Pushmenu)(int client, const char* name);
	void(*HideMouseCursor)(int client);
	void(*ShowMouseCursor)(int client);
	const char* (*MapTime)();
	void(*LoadResource)(char* name);
	void(*ClearResource)();
	int(*Key_StringToKeynum)(char* str);
	const char* (*Key_KeynumToBindString)(int keyNum);
	void(*Key_GetKeysForCommand)(const char* command, int* key1, int* key2);
	void(*ArchiveLevel)(qboolean loading);
	void(*AddSvsTimeFixup)(int* piTime);
	void(*HudDrawShader)(int info, char* name);
	void(*HudDrawAlign)(int info, int horizontalAlign, int verticalAlign);
	void(*HudDrawRect)(int info, int x, int y, int width, int height);
	void(*HudDrawVirtualSize)(int info, qboolean virtualScreen);
	void(*HudDrawColor)(int info, float* color);
	void(*HudDrawAlpha)(int info, float alpha);
	void(*HudDrawString)(int info, char* string);
	void(*HudDrawFont)(int info, char* fontName);
	qboolean(*SanitizeName)(char* oldName, char* newName);
	cvar_t* fsDebug;
} gameImportAA_t;


typedef struct gameImportDSH_s
{
	void(*Printf)(const char* format, ...);
	void(*DPrintf)(const char* format, ...);
	void(*DPrintf2)(const char* format, ...);
	void(*DebugPrintf)(const char* format, ...);
	void(*Error)(int level, const char* format, ...);
	int(*Milliseconds)();
	int(*sub_493F70) (int a1);//1
	const char* (*LV_ConvertString)(const char* string);
	void* (*Malloc)(size_t size);
	void(*Free)(void* ptr);
	cvar_t* (*Cvar_Get)(const char* varName, const char* varValue, int varFlags);
	void (*Cvar_Set)(const char* varName, const char* varValue);
	cvar_t* (*cvar_set2)(const char* varName, const char* varValue, qboolean force);
	cvar_t* (*NextCvar)(cvar_t* var);
	int(*Argc)();
	char* (*Argv)(int arg);
	char* (*Args)();
	void(*AddCommand)(const char* cmdName, xcommand_t cmdFunction);
	int(*FS_ReadFile)(const char* qpath, void** buffer);// , qboolean quiet);< from FS_ReadFileEX
	void(*FS_FreeFile)(void* buffer);
	size_t(*FS_WriteFile)(const char* qpath, const void* buffer, size_t size);
	fileHandle_t(*FS_FOpenFileWrite)(const char* fileName);
	fileHandle_t(*FS_FOpenFileAppend)(const char* fileName);
	const char* (*FS_PrepFileWrite)(const char* fileName);
	size_t(*FS_Write)(void* buffer, size_t size, fileHandle_t fileHandle);
	size_t(*FS_Read)(void* buffer, size_t len, fileHandle_t fileHandle);
	void(*FS_FCloseFile)(fileHandle_t fileHandle);
	int(*FS_Tell)(fileHandle_t fileHandle);
	int(*FS_Seek)(fileHandle_t fileHandle, long int offset, fsOrigin_t origin);
	void(*FS_Flush)(fileHandle_t fileHandle);
	int(*FS_FileNewer)(const char* source, const char* destination);
	void(*FS_CanonicalFilename)(char* fileName);
	char** (*FS_ListFiles)(const char* qpath, const char* extension, qboolean wantSubs, int* numFiles);
	char** (*FS_ListFilteredFiles)(const char* path, const char* extension, char* filter, qboolean wantSubs, int* numfiles);//2
	void(*FS_FreeFileList)(char** list);
	const char* (*GetArchiveFileName)(char* fileName, char* extension);
	void(*SendConsoleCommand)(const char* text);
	void(*Cbuf_ExecuteText) (int exec_when, const char* text);//3: Cbuf_ExecuteText
	void(*DebugGraph)(float value, int color);
	void(*SendServerCommand)(int client, const char* format, ...);//shouldn't exceed 500 bytes
	void(*DropClient)(int client, const char* reason);
	void(*MSG_WriteBits)(int value, int bits);
	void(*MSG_WriteChar)(int c);
	void(*MSG_WriteByte)(int c);
	void(*MSG_WriteSVC)(int c);
	void(*MSG_WriteShort)(int c);
	void(*MSG_WriteLong)(int c);
	void(*MSG_WriteFloat)(float f);
	void(*MSG_WriteString)(const char* s);
	void(*MSG_WriteAngle8)(float f);
	void(*MSG_WriteAngle16)(float f);
	void(*MSG_WriteCoord)(float f);
	void(*MSG_WriteDir)(vec3_t dir);
	void(*MSG_StartCGM)(int type);
	void(*MSG_EndCGM)();
	void(*MSG_SetClient)(int client);
	void(*SetBroadcastVisible)(vec3_t pos, vec3_t posB);
	void(*SetBroadcastHearable)(vec3_t pos, vec3_t posB);
	void(*SetBroadcastAll)();
	void(*SetConfigstring)(int index, const char* val);
	char* (*GetConfigstring)(int index);
	void(*SetUserinfo)(int index, char* val);
	void(*GetUserinfo)(int index, char* buffer, int bufferSize);
	void(*SetBrushModel)(gentityDSH_t* ent, const char* name);
	void(*ModelBoundsFromName)(char* name, vec3_t mins, vec3_t maxs);
	qboolean(*SightTraceEntity)(gentityDSH_t* touch, vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int contentMask, qboolean cylinder);
	qboolean(*SightTrace)(vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int passEntityNum, int passEntityNum2, int contentMask, qboolean cylinder);
	void(*Trace)(trace_t* results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask, qboolean cylinder, qboolean traceDeep);
	int(*sub_451C80) (int* a1, float* a2);//4
	baseShader_t* (*GetShader)(int shaderNum);
	int(*PointContents)(const vec3_t p, int passEntityNum);
	int(*PointBrushnum)(vec3_t p, clipHandle_t model);
	void(*AdjustAreaPortalState)(gentityDSH_t* ent, qboolean open);
	int(*AreaForPoint)(vec3_t pos);
	qboolean(*AreasConnected)(int area1, int area2);
	qboolean(*InPVS)(float* p1, float* p2);
	void(*LinkEntity)(gentityDSH_t* gEnt);
	void(*UnlinkEntity)(gentityDSH_t* gEnt);
	int(*AreaEntities)(const vec3_t mins, const vec3_t maxs, int* list, int maxcount);
	void(*ClipToEntity)(trace_t* tr, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int entityNum, int contentMask);
	qboolean(*SV_EntityContact)(vec3_t mins, vec3_t maxs, gentityDSH_t* gEnt);//5:
	int(*imageindex)(const char* name);
	int(*itemindex)(const char* name);
	int(*soundindex)(const char* name, int streamed);
	dtiki_t* (*TIKI_RegisterModel)(const char* path);
	dtiki_t* (*modeltiki)(const char* name);
	dtikianim_t* (*modeltikianim)(const char* name);
	void(*SetLightStyle)(int index, const char* data);
	const char* (*GameDir)();
	qboolean(*setmodel)(gentityDSH_t* ent, const char* name);
	void(*clearmodel)(gentityDSH_t* ent);
	int(*TIKI_NumAnims)(dtiki_t* tiki);
	int(*NumSurfaces)(dtiki_t* tiki);
	int(*NumTags)(dtiki_t* tiki);
	void(*CalculateBounds)(dtiki_t* tiki, float scale, vec3_t mins, vec3_t maxs);
	void* (*TIKI_GetSkeletor)(dtiki_t* tiki, int entNum);
	const char* (*Anim_NameForNum)(dtiki_t* tiki, int animNum);
	int(*Anim_NumForName)(dtiki_t* tiki, const char* name);
	int(*Anim_Random)(dtiki_t* tiki, const char* name);
	int(*Anim_NumFrames)(dtiki_t* tiki, int animNum);
	float(*Anim_Time)(dtiki_t* tiki, int animNum);
	float(*Anim_Frametime)(dtiki_t* tiki, int animNum);
	float(*Anim_CrossTime)(dtiki_t* tiki, int animNum);
	void(*Anim_Delta)(dtiki_t* tiki, int animNum, float* delta);
	DWORD* (*sub_487570)(DWORD* a1, int a2, DWORD* a3);//6
	qboolean(*Anim_HasDelta)(dtiki_t* tiki, int animNum);
	void(*Anim_DeltaOverTime)(dtiki_t* tiki, int animNum, float time1, float time2, float* delta);
	void(*TIKI_Anim_AngularDeltaOverTime)(int a1, int a2, float a3, float a4, float* a5);//7
	int(*Anim_Flags)(dtiki_t* tiki, int animNum);
	int(*Anim_FlagsSkel)(dtiki_t* tiki, int animNum);
	qboolean(*Anim_HasCommands)(dtiki_t* tiki, int animNum);
	int(*NumHeadModels)(const char* model);
	void(*GetHeadModel)(const char* model, int num, char* name);
	int(*NumHeadSkins)(const char* model);
	void(*GetHeadSkin)(const char* model, int num, char* name);
	qboolean(*Frame_Commands)(dtiki_t* tiki, int animNum, int frameNum, tiki_cmd_t* tikiCmds);
	int(*Surface_NameToNum)(dtiki_t* tiki, const char* name);
	const char* (*Surface_NumToName)(dtiki_t* tiki, int surfacenum);
	int(*Tag_NumForName)(dtiki_t* pmdl, const char* name);
	const char* (*Tag_NameForNum)(dtiki_t* pmdl, int tagNum);
	orientation_t(*TIKI_OrientationInternal)(dtiki_t* tiki, int entNum, int tagNum, float scale);
	void* (*TIKI_TransformInternal)(dtiki_t* tiki, int entNum, int tagNum);
	qboolean(*TIKI_IsOnGroundInternal)(dtiki_t* tiki, int entNum, int num, float threshold);
	void(*TIKI_SetPoseInternal)(dtiki_t* tiki, int entNum, frameInfo_t* frameInfo, int* boneTag, vec4_t* boneQuat, float actionWeight);
	const char* (*CM_GetHitLocationInfo)(int location, float* radius, float* offset);
	const char* (*CM_GetHitLocationInfoSecondary)(int location, float* radius, float* offset);
	qboolean(*Alias_Add)(dtiki_t* pmdl, const char* alias, const char* name, const char* parameters);
	const char* (*Alias_FindRandom)(dtiki_t* tiki, const char* alias, aliasListNode_t** ret);
	void(*Alias_Dump)(dtiki_t* tiki);
	void(*Alias_Clear)(dtiki_t* tiki);
	void(*Alias_UpdateDialog)(dtikianim_t* tiki, const char* alias);
	const char* (*TIKI_NameForNum)(dtiki_t* tiki);
	qboolean(*GlobalAlias_Add)(const char* alias, const char* name, const char* parameters);
	const char* (*GlobalAlias_FindRandom)(const char* alias, aliasListNode_t** ret);
	void(*GlobalAlias_Dump)();
	void(*GlobalAlias_Clear)();
	void(*centerprintf)(gentityDSH_t* ent, const char* format, ...);
	void(*locationprintf)(gentityDSH_t* ent, int x, int y, const char* format, ...);
	void(*Sound)(vec3_t* org, int entNum, int channel, const char* soundName, float volume, float minDist, float pitch, float maxDist, int streamed);
	void(*StopSound)(int entNum, int channel);
	float (*SoundLength)(int channel, const char* name);
	unsigned char* (*SoundAmplitudes)(int channel, const char* name);
	int(*S_IsSoundPlaying)(int channel, const char* name);
	short unsigned int(*CalcCRC)(unsigned char* start, int count);
	void** DebugLines;
	int* numDebugLines;
	void** DebugStrings;
	int* numDebugStrings;
	void(*LocateGameData)(gentityDSH_t* gEnts, int numGEntities, int sizeofGEntity, playerStateDSH_t* clients, int sizeofGameClient);
	void(*SetFarPlane)(int farPlane);
	void(*SetSkyPortal)(qboolean skyPortal);
	void(*Popmenu)(int client, int i);
	void(*Showmenu)(int client, const char* name, qboolean force);
	void(*Hidemenu)(int client, const char* name, qboolean force);
	void(*Pushmenu)(int client, const char* name);
	void(*HideMouseCursor)(int client);
	void(*ShowMouseCursor)(int client);
	const char* (*MapTime)();
	void(*LoadResource)(char* name);
	void(*ClearResource)();
	int(*Key_StringToKeynum)(char* str);
	const char* (*Key_KeynumToBindString)(int keyNum);
	void(*Key_GetKeysForCommand)(const char* command, int* key1, int* key2);
	void(*ArchiveLevel)(qboolean loading);
	void(*AddSvsTimeFixup)(int* piTime);
	void(*HudDrawShader)(int info, char* name);
	void(*HudDrawAlign)(int info, int horizontalAlign, int verticalAlign);
	void(*HudDrawRect)(int info, int x, int y, int width, int height);
	void(*HudDrawVirtualSize)(int info, qboolean virtualScreen);
	void(*HudDrawColor)(int info, float* color);
	void(*HudDrawAlpha)(int info, float alpha);
	void(*HudDrawString)(int info, char* string);
	void(*HudDrawFont)(int info, char* fontName);
	qboolean(*SanitizeName)(char* oldName, char* newName);
	cvar_t* fsDebug;
} gameImportDSH_t;

typedef struct gameImportDBT_s
{
	void(*Printf)(const char* format, ...);
	void(*DPrintf)(const char* format, ...);
	void(*DPrintf2)(const char* format, ...);
	void(*DebugPrintf)(const char* format, ...);
	void(*Error)(int level, const char* format, ...);
	int(*Milliseconds)();
	int(*sub_493F70) (int a1);//1
	const char* (*LV_ConvertString)(const char* string);
	void* (*Malloc)(size_t size);
	void(*Free)(void* ptr);
	cvar_t* (*Cvar_Get)(const char* varName, const char* varValue, int varFlags);
	void (*Cvar_Set)(const char* varName, const char* varValue);
	cvar_t* (*cvar_set2)(const char* varName, const char* varValue, qboolean force);
	cvar_t* (*NextCvar)(cvar_t* var);
	int(*Argc)();
	char* (*Argv)(int arg);
	char* (*Args)();
	void(*AddCommand)(const char* cmdName, xcommand_t cmdFunction);
	int(*FS_ReadFile)(const char* qpath, void** buffer);// , qboolean quiet);< from FS_ReadFileEX
	void(*FS_FreeFile)(void* buffer);
	size_t(*FS_WriteFile)(const char* qpath, const void* buffer, size_t size);
	fileHandle_t(*FS_FOpenFileWrite)(const char* fileName);
	fileHandle_t(*FS_FOpenFileAppend)(const char* fileName);
	const char* (*FS_PrepFileWrite)(const char* fileName);
	size_t(*FS_Write)(void* buffer, size_t size, fileHandle_t fileHandle);
	size_t(*FS_Read)(void* buffer, size_t len, fileHandle_t fileHandle);
	void(*FS_FCloseFile)(fileHandle_t fileHandle);
	int(*FS_Tell)(fileHandle_t fileHandle);
	int(*FS_Seek)(fileHandle_t fileHandle, long int offset, fsOrigin_t origin);
	void(*FS_Flush)(fileHandle_t fileHandle);
	int(*FS_FileNewer)(const char* source, const char* destination);
	void(*FS_CanonicalFilename)(char* fileName);
	char** (*FS_ListFiles)(const char* qpath, const char* extension, qboolean wantSubs, int* numFiles);
	char** (*FS_ListFilteredFiles)(const char* path, const char* extension, char* filter, qboolean wantSubs, int* numfiles);//2
	void(*FS_FreeFileList)(char** list);
	const char* (*GetArchiveFileName)(char* fileName, char* extension);
	void(*SendConsoleCommand)(const char* text);
	void(*Cbuf_ExecuteText) (int exec_when, const char* text);//3: Cbuf_ExecuteText
	void(*DebugGraph)(float value, int color);
	void(*SendServerCommand)(int client, const char* format, ...);//shouldn't exceed 500 bytes
	void(*DropClient)(int client, const char* reason);
	void(*MSG_WriteBits)(int value, int bits);
	void(*MSG_WriteChar)(int c);
	void(*MSG_WriteByte)(int c);
	void(*MSG_WriteSVC)(int c);
	void(*MSG_WriteShort)(int c);
	void(*MSG_WriteLong)(int c);
	void(*MSG_WriteFloat)(float f);
	void(*MSG_WriteString)(const char* s);
	void(*MSG_WriteAngle8)(float f);
	void(*MSG_WriteAngle16)(float f);
	void(*MSG_WriteCoord)(float f);
	void(*MSG_WriteDir)(vec3_t dir);
	void(*MSG_StartCGM)(int type);
	void(*MSG_EndCGM)();
	void(*MSG_SetClient)(int client);
	void(*SetBroadcastVisible)(vec3_t pos, vec3_t posB);
	void(*SetBroadcastHearable)(vec3_t pos, vec3_t posB);
	void(*SetBroadcastAll)();
	void(*SetConfigstring)(int index, const char* val);
	char* (*GetConfigstring)(int index);
	void(*SetUserinfo)(int index, char* val);
	void(*GetUserinfo)(int index, char* buffer, int bufferSize);
	void(*SetBrushModel)(gentityDBT_t* ent, const char* name);
	void(*ModelBoundsFromName)(char* name, vec3_t mins, vec3_t maxs);
	qboolean(*SightTraceEntity)(gentityDBT_t* touch, vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int contentMask, qboolean cylinder);
	qboolean(*SightTrace)(vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int passEntityNum, int passEntityNum2, int contentMask, qboolean cylinder);
	void(*Trace)(trace_t* results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask, qboolean cylinder, qboolean traceDeep);
	int(*sub_451C80) (int* a1, float* a2);//4
	baseShader_t* (*GetShader)(int shaderNum);
	int(*PointContents)(const vec3_t p, int passEntityNum);
	int(*PointBrushnum)(vec3_t p, clipHandle_t model);
	void(*AdjustAreaPortalState)(gentityDBT_t* ent, qboolean open);
	int(*AreaForPoint)(vec3_t pos);
	qboolean(*AreasConnected)(int area1, int area2);
	qboolean(*InPVS)(float* p1, float* p2);
	void(*LinkEntity)(gentityDBT_t* gEnt);
	void(*UnlinkEntity)(gentityDBT_t* gEnt);
	int(*AreaEntities)(const vec3_t mins, const vec3_t maxs, int* list, int maxcount);
	void(*ClipToEntity)(trace_t* tr, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int entityNum, int contentMask);
	qboolean(*SV_EntityContact)(vec3_t mins, vec3_t maxs, gentityDBT_t* gEnt);//5:
	int(*imageindex)(const char* name);
	int(*itemindex)(const char* name);
	int(*soundindex)(const char* name, int streamed);
	dtiki_t* (*TIKI_RegisterModel)(const char* path);
	dtiki_t* (*modeltiki)(const char* name);
	dtikianim_t* (*modeltikianim)(const char* name);
	void(*SetLightStyle)(int index, const char* data);
	const char* (*GameDir)();
	qboolean(*setmodel)(gentityDBT_t* ent, const char* name);
	void(*clearmodel)(gentityDBT_t* ent);
	int(*TIKI_NumAnims)(dtiki_t* tiki);
	int(*NumSurfaces)(dtiki_t* tiki);
	int(*NumTags)(dtiki_t* tiki);
	void(*CalculateBounds)(dtiki_t* tiki, float scale, vec3_t mins, vec3_t maxs);
	void* (*TIKI_GetSkeletor)(dtiki_t* tiki, int entNum);
	const char* (*Anim_NameForNum)(dtiki_t* tiki, int animNum);
	int(*Anim_NumForName)(dtiki_t* tiki, const char* name);
	int(*Anim_Random)(dtiki_t* tiki, const char* name);
	int(*Anim_NumFrames)(dtiki_t* tiki, int animNum);
	float(*Anim_Time)(dtiki_t* tiki, int animNum);
	float(*Anim_Frametime)(dtiki_t* tiki, int animNum);
	float(*Anim_CrossTime)(dtiki_t* tiki, int animNum);
	void(*Anim_Delta)(dtiki_t* tiki, int animNum, float* delta);
	DWORD* (*sub_487570)(DWORD* a1, int a2, DWORD* a3);//6
	qboolean(*Anim_HasDelta)(dtiki_t* tiki, int animNum);
	void(*Anim_DeltaOverTime)(dtiki_t* tiki, int animNum, float time1, float time2, float* delta);
	void(*TIKI_Anim_AngularDeltaOverTime)(int a1, int a2, float a3, float a4, float* a5);//7
	int(*Anim_Flags)(dtiki_t* tiki, int animNum);
	int(*Anim_FlagsSkel)(dtiki_t* tiki, int animNum);
	qboolean(*Anim_HasCommands)(dtiki_t* tiki, int animNum);
	int(*NumHeadModels)(const char* model);
	void(*GetHeadModel)(const char* model, int num, char* name);
	int(*NumHeadSkins)(const char* model);
	void(*GetHeadSkin)(const char* model, int num, char* name);
	qboolean(*Frame_Commands)(dtiki_t* tiki, int animNum, int frameNum, tiki_cmd_t* tikiCmds);
	int(*Surface_NameToNum)(dtiki_t* tiki, const char* name);
	const char* (*Surface_NumToName)(dtiki_t* tiki, int surfacenum);
	int(*Tag_NumForName)(dtiki_t* pmdl, const char* name);
	const char* (*Tag_NameForNum)(dtiki_t* pmdl, int tagNum);
	orientation_t(*TIKI_OrientationInternal)(dtiki_t* tiki, int entNum, int tagNum, float scale);
	void* (*TIKI_TransformInternal)(dtiki_t* tiki, int entNum, int tagNum);
	qboolean(*TIKI_IsOnGroundInternal)(dtiki_t* tiki, int entNum, int num, float threshold);
	void(*TIKI_SetPoseInternal)(dtiki_t* tiki, int entNum, frameInfo_t* frameInfo, int* boneTag, vec4_t* boneQuat, float actionWeight);
	const char* (*CM_GetHitLocationInfo)(int location, float* radius, float* offset);
	const char* (*CM_GetHitLocationInfoSecondary)(int location, float* radius, float* offset);
	qboolean(*Alias_Add)(dtiki_t* pmdl, const char* alias, const char* name, const char* parameters);
	const char* (*Alias_FindRandom)(dtiki_t* tiki, const char* alias, aliasListNode_t** ret);
	void(*Alias_Dump)(dtiki_t* tiki);
	void(*Alias_Clear)(dtiki_t* tiki);
	void(*Alias_UpdateDialog)(dtikianim_t* tiki, const char* alias);
	const char* (*TIKI_NameForNum)(dtiki_t* tiki);
	qboolean(*GlobalAlias_Add)(const char* alias, const char* name, const char* parameters);
	const char* (*GlobalAlias_FindRandom)(const char* alias, aliasListNode_t** ret);
	void(*GlobalAlias_Dump)();
	void(*GlobalAlias_Clear)();
	void(*centerprintf)(gentityDBT_t* ent, const char* format, ...);
	void(*locationprintf)(gentityDBT_t* ent, int x, int y, const char* format, ...);
	void(*Sound)(vec3_t* org, int entNum, int channel, const char* soundName, float volume, float minDist, float pitch, float maxDist, int streamed);
	void(*StopSound)(int entNum, int channel);
	float (*SoundLength)(int channel, const char* name);
	unsigned char* (*SoundAmplitudes)(int channel, const char* name);
	int(*S_IsSoundPlaying)(int channel, const char* name);
	short unsigned int(*CalcCRC)(unsigned char* start, int count);
	void** DebugLines;
	int* numDebugLines;
	void** DebugStrings;
	int* numDebugStrings;
	void(*LocateGameData)(gentityDBT_t* gEnts, int numGEntities, int sizeofGEntity, playerStateDBT_t* clients, int sizeofGameClient);
	void(*SetFarPlane)(int farPlane);
	void(*SetSkyPortal)(qboolean skyPortal);
	void(*Popmenu)(int client, int i);
	void(*Showmenu)(int client, const char* name, qboolean force);
	void(*Hidemenu)(int client, const char* name, qboolean force);
	void(*Pushmenu)(int client, const char* name);
	void(*HideMouseCursor)(int client);
	void(*ShowMouseCursor)(int client);
	const char* (*MapTime)();
	void(*LoadResource)(char* name);
	void(*ClearResource)();
	int(*Key_StringToKeynum)(char* str);
	const char* (*Key_KeynumToBindString)(int keyNum);
	void(*Key_GetKeysForCommand)(const char* command, int* key1, int* key2);
	void(*ArchiveLevel)(qboolean loading);
	void(*AddSvsTimeFixup)(int* piTime);
	void(*HudDrawShader)(int info, char* name);
	void(*HudDrawAlign)(int info, int horizontalAlign, int verticalAlign);
	void(*HudDrawRect)(int info, int x, int y, int width, int height);
	void(*HudDrawVirtualSize)(int info, qboolean virtualScreen);
	void(*HudDrawColor)(int info, float* color);
	void(*HudDrawAlpha)(int info, float alpha);
	void(*HudDrawString)(int info, char* string);
	void(*HudDrawFont)(int info, char* fontName);
	qboolean(*SanitizeName)(char* oldName, char* newName);
	cvar_t* fsDebug;
} gameImportDBT_t;

typedef struct gameExportAA_s
{
	int apiVersion;

	void (*Init)(int svsStartTime, int randomSeed);
	void (*Shutdown)();
	void (*Cleanup)(qboolean sameMap);
	void (*Precache)();
	void (*SetMap)(char* mapName);
	void (*Restart)();
	void (*SetTime)(int svsStartTime, int svsTime);
	void (*SpawnEntities)(char* entities, int svsTime);
	char* (*ClientConnect)(int clientNum, qboolean firstTime);
	void (*ClientBegin)(gentityAA_t* ent, userCmd_t* cmd);
	void (*ClientUserinfoChanged)(gentityAA_t* ent, char* userInfo);
	void (*ClientDisconnect)(gentityAA_t* ent);
	void (*ClientCommand)(gentityAA_t* ent);
	void (*ClientThink)(gentityAA_t* ent, userCmd_t* ucmd, userEyes_t* eyeInfo);
	void (*BotBegin)(gentityAA_t* ent, userCmd_t* cmd);
	void (*BotThink)(gentityAA_t* ent, userCmd_t* ucmd, userEyes_t* eyeInfo);
	void (*PrepFrame)();

	void (*RunFrame)(int svsTime, int frameTime);
	void (*ServerSpawned)();
	void (*RegisterSounds)();
	qboolean(*AllowPaused)();
	qboolean(*ConsoleCommand)();
	void (*ArchivePersistant)(char* name, qboolean loading);
	void (*WriteLevel)(char* fileName, qboolean autoSave);
	qboolean(*ReadLevel)(char* fileName);
	qboolean(*LevelArchiveValid)(char* fileName);
	void (*ArchiveInteger)(int* i);
	void (*ArchiveFloat)(float* fl);
	void (*ArchiveString)(char* s);
	void (*ArchiveSvsTime)(int* pi);
	orientation_t(*TIKI_Orientation)(gentityAA_t* edict, int num);
	void (*DebugCircle)(float* org, float radius, float r, float g, float b, float alpha, qboolean horizontal);
	void (*SetFrameNumber)(int frameNumber);
	void (*SoundCallback)(int entNum, soundChannel_t channelNumber, char* name);
	//void ( *cgameSub3 )( );//Client sub

	profGame_t* profStruct;//Extra in opm
	gentityAA_t* gentities;
	int gentitySize;
	int num_entities;
	int max_entities;
	char* errorMessage;

} gameExportAA_t;


typedef struct gameExportDSH_s
{
	int apiVersion;

	void (*Init)(int svsStartTime, int randomSeed);
	void (*Shutdown)();
	void (*Cleanup)(qboolean sameMap);
	void (*Precache)();
	void (*SetMap)(char* mapName);
	void (*Restart)();
	void (*SetTime)(int svsStartTime, int svsTime);
	void (*SpawnEntities)(char* entities, int svsTime);

	char* (*ClientConnect)(int clientNum, qboolean firstTime, int a3);
	void (*ClientBegin)(gentityDSH_t* ent, userCmd_t* cmd);
	void (*ClientUserinfoChanged)(gentityDSH_t* ent, char* userInfo);
	void (*ClientDisconnect)(gentityDSH_t* ent);
	void (*ClientCommand)(gentityDSH_t* ent);
	void (*ClientThink)(gentityDSH_t* ent, userCmd_t* ucmd, userEyes_t* eyeInfo);
	void (*BotBegin)(gentityDSH_t* ent, userCmd_t* cmd);
	void (*BotThink)(gentityDSH_t* ent, userCmd_t* ucmd, userEyes_t* eyeInfo);
	void (*DavenExtra)();

	void (*RunFrame)(int svsTime, int frameTime);
	void (*ServerSpawned)();
	void (*RegisterSounds)();
	qboolean(*AllowPaused)();
	qboolean(*ConsoleCommand)();
	void (*ArchivePersistant)(char* name, qboolean loading);
	void (*WriteLevel)(char* fileName, qboolean autoSave);
	qboolean(*ReadLevel)(char* fileName);
	qboolean(*LevelArchiveValid)(char* fileName);
	void (*ArchiveInteger)(int* i);
	void (*ArchiveFloat)(float* fl);
	void (*ArchiveString)(char* s);
	void (*ArchiveSvsTime)(int* pi);
	orientation_t(*TIKI_Orientation)(gentityDSH_t* edict, int num);
	void (*DebugCircle)(float* org, float radius, float r, float g, float b, float alpha, qboolean horizontal);
	void (*SetFrameNumber)(int frameNumber);
	void (*SoundCallback)(int entNum, soundChannel_t channelNumber, char* name);
	//void ( *cgameSub3 )( );//Client sub

	profGame_t* profStruct;//Extra in opm
	gentityDSH_t* gentities;
	int gentitySize;
	int num_entities;
	int max_entities;
	char* errorMessage;

} gameExportDSH_t;

typedef struct gameExportDBT_s
{
	int apiVersion;

	void (*Init)(int svsStartTime, int randomSeed);
	void (*Shutdown)();
	void (*Cleanup)(qboolean sameMap);
	void (*Precache)();
	void (*SetMap)(char* mapName);
	void (*Restart)();
	void (*SetTime)(int svsStartTime, int svsTime);
	void (*SpawnEntities)(char* entities, int svsTime);

	char* (*ClientConnect)(int clientNum, qboolean firstTime, int a3);
	void (*ClientBegin)(gentityDBT_t* ent, userCmd_t* cmd);
	void (*ClientUserinfoChanged)(gentityDBT_t* ent, char* userInfo);
	void (*ClientDisconnect)(gentityDBT_t* ent);
	void (*ClientCommand)(gentityDBT_t* ent);
	void (*ClientThink)(gentityDBT_t* ent, userCmd_t* ucmd, userEyes_t* eyeInfo);
	void (*BotBegin)(gentityDBT_t* ent, userCmd_t* cmd);
	void (*BotThink)(gentityDBT_t* ent, userCmd_t* ucmd, userEyes_t* eyeInfo);
	void (*DavenExtra)();

	void (*RunFrame)(int svsTime, int frameTime);
	void (*ServerSpawned)();
	void (*RegisterSounds)();
	qboolean(*AllowPaused)();
	qboolean(*ConsoleCommand)();
	void (*ArchivePersistant)(char* name, qboolean loading);
	void (*WriteLevel)(char* fileName, qboolean autoSave);
	qboolean(*ReadLevel)(char* fileName);
	qboolean(*LevelArchiveValid)(char* fileName);
	void (*ArchiveInteger)(int* i);
	void (*ArchiveFloat)(float* fl);
	void (*ArchiveString)(char* s);
	void (*ArchiveSvsTime)(int* pi);
	orientation_t(*TIKI_Orientation)(gentityDBT_t* edict, int num);
	void (*DebugCircle)(float* org, float radius, float r, float g, float b, float alpha, qboolean horizontal);
	void (*SetFrameNumber)(int frameNumber);
	void (*SoundCallback)(int entNum, soundChannel_t channelNumber, char* name);
	//void ( *cgameSub3 )( );//Client sub

	profGame_t* profStruct;//Extra in opm
	gentityDBT_t* gentities;
	int gentitySize;
	int num_entities;
	int max_entities;
	char* errorMessage;

} gameExportDBT_t;

/*
These are custom function non related to MOHAA
these are just here to make the code easier to follow
*/







//---------------------------------------------------------
/*		These are list of funcitons I need to work on

	SkelVec3();
	SkelVec4();
	SkelMat3();
	SkelMat4();
	Entity_t();
	FileRead();
	Weapon();
	Item();
*/


/* Moved the custom gamex86.c structs so it's easier to find and modify when needed */
/* Razorapid */

#define LOG_DEBUG		"DEBUG"
#define LOG_INFO		"INFO"
#define LOG_WARNING		"WARNING"
#define LOG_ERROR		"ERROR"


#define MEM_DEBUG 0   // print debug messages at memory allocations/frees
#define LOG_LEVEL LOG_INFO   // only log messages with level equal to or higher than this will be logged
#define CUSTOM_SIGNAL_HANDLERS 1   // uses custom signal handlers to print stack trace info when the application crashes (linux only)


typedef struct clientdata_s
{
	char		ip[64];
	int			joinTime;
	qboolean	admin;
	int			adminNum;
	char		name[32];
} clientdata_t;

class BaseGameImport
{
public:
	virtual void Printf(char* format, ...) = 0;
};
template <class T>
class GameImport : public BaseGameImport
{
	T realGameImport;
public:
	GameImport(T &rgi)
		: realGameImport(rgi)
	{
	}
	virtual void Printf(char* format, ...) override
	{
		va_list args;
		va_start(args, format);
		realGameImport.Printf(format, args);
		va_end(args);
	}
};


class GameImportFactory
{
	shared_ptr<BaseGameImport> realGameImport;
public:
	void GetGameImport()
	{
		if (gameInfo.GetExpansion() == gameInfo.AA)
		{
			realGameImport = make_shared<GameImport<gameImportAA_t>>(gameImportAA_t());
		}
		else if (gameInfo.GetExpansion() == gameInfo.SH)
		{
			realGameImport = make_shared<GameImport<gameImportDSH_t>>(gameImportDSH_t());
		}
		else if (gameInfo.GetExpansion() == gameInfo.BT)
		{
			realGameImport = make_shared<GameImport<gameImportDBT_t>>(gameImportDBT_t());
		}
	}
};

#define EXPORT_SETTER_GETTER(func_name, return_type, ...) virtual void Set##func_name (return_type(*func_name)(__VA_ARGS__)) = 0; virtual return_type(*Get##func_name(__VA_ARGS__)) ()= 0; 
class BaseGameExport
{
public:
	EXPORT_SETTER_GETTER(Cleanup, void, qboolean sameMap);
	EXPORT_SETTER_GETTER(ClientBegin, void, void* ent, userCmd_t* cmd);
	EXPORT_SETTER_GETTER(ClientCommand, void, void* ent);
	EXPORT_SETTER_GETTER(ClientConnect, char*, int clientNum, qboolean firstTime, int a3);// different in sh/bt
	EXPORT_SETTER_GETTER(ClientDisconnect, void, void* ent);
	EXPORT_SETTER_GETTER(ClientThink, void, void* ent, userCmd_t* ucmd, userEyes_t* eyeInfo);
	EXPORT_SETTER_GETTER(ClientUserinfoChanged, void, void* ent, char* userInfo);
	EXPORT_SETTER_GETTER(ConsoleCommand, qboolean, void);
	EXPORT_SETTER_GETTER(Init, void, int svsStartTime, int randomSeed);
	EXPORT_SETTER_GETTER(Precache, void, void);
	EXPORT_SETTER_GETTER(RunFrame, void, int svsTime, int frameTime);
	EXPORT_SETTER_GETTER(Shutdown, void, void);

	virtual void* GetRealGameExport();

};

#define EXPORT_SETTER_GETTER_OVERRIDE(func_name, return_type, ...) virtual void Set##func_name (return_type(*func_name)(__VA_ARGS__)) {realGameExport.func_name = func_name;} virtual return_type(*Get##func_name(__VA_ARGS__)) () {return realGameExport.func_name}; 
template <class T>
class GameExport
{
	T& realGameExport;
public:
	GameExport(T& rgi)
		: realGameExport(rgi)
	{

	}
	EXPORT_SETTER_GETTER_OVERRIDE(Cleanup, void, qboolean sameMap);
	EXPORT_SETTER_GETTER_OVERRIDE(ClientBegin, void, void* ent, userCmd_t* cmd);
	EXPORT_SETTER_GETTER_OVERRIDE(ClientCommand, void, void* ent);
	EXPORT_SETTER_GETTER_OVERRIDE(ClientConnect, char*, int clientNum, qboolean firstTime, int a3);// different in sh/bt
	EXPORT_SETTER_GETTER_OVERRIDE(ClientDisconnect, void, void* ent);
	EXPORT_SETTER_GETTER_OVERRIDE(ClientThink, void, void* ent, userCmd_t* ucmd, userEyes_t* eyeInfo);
	EXPORT_SETTER_GETTER_OVERRIDE(ClientUserinfoChanged, void, void* ent, char* userInfo);
	EXPORT_SETTER_GETTER_OVERRIDE(ConsoleCommand, qboolean, void);
	EXPORT_SETTER_GETTER_OVERRIDE(Init, void, int svsStartTime, int randomSeed);
	EXPORT_SETTER_GETTER_OVERRIDE(Precache, void, void);
	EXPORT_SETTER_GETTER_OVERRIDE(RunFrame, void, int svsTime, int frameTime);
	EXPORT_SETTER_GETTER_OVERRIDE(Shutdown, void, void);

	virtual void* GetRealGameExport()
	{
		return &realGameExport;
	}
};


class GameExportFactory
{
	shared_ptr<BaseGameExport> realGameExport;
public:
	void GetGameExport()
	{
		if (gameInfo.GetExpansion() == gameInfo.AA)
		{
			realGameExport = make_shared<GameExport<gameExportAA_t>>(gameExportAA_t());
		}
		else if (gameInfo.GetExpansion() == gameInfo.SH)
		{
			realGameExport = make_shared<GameExport<gameExportDSH_t>>(gameExportDSH_t());
		}
		else if (gameInfo.GetExpansion() == gameInfo.BT)
		{
			realGameExport = make_shared<GameExport<gameExportDBT_t>>(gameExportDBT_t());
		}
	}
};

/* Added some externs so we can use those variables in misc.c */
/* Razorapid */
extern	GameImport	gi;
extern	GameExport	*globals;
extern	GameExport	globals_backup;


enum INTTYPE_e { TRANS_BSP, TRANS_LEVEL, TRANS_MISSION, TRANS_MISSION_FAILED };

enum SEV_INTERMISSION_TYPE
{
	INTERM_SCREEN,
	INTERM_MAP,
	INTERM_RESTART,
};

void *__cdecl MemoryMalloc(int size);
void __cdecl MemoryFree(void * ptr);
