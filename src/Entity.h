#pragma once
#include "SimpleEntity.h"
#include "dgamex86.h"
#define MAX_MODEL_CHILDREN 16
#define MAX_GLUE_CHILDREN 8

class Entity;
typedef int EntityPtr[4];


class pathway_ref {
public:
	short int from;
	short int to;
};

class Entity : public SimpleEntity
{
public:
	int			entnum;//0
	int			radnum;//1
	gentity_t	*edict;//2
	gclient_t	*client;//3
	int			spawnflags;//4
	str			 model;//5
	Vector		mins;//6
	Vector		maxs;//9
	Vector		absmin;//12
	Vector		absmax;//15
	Vector		velocity;//18
	Vector		accel;//21
	Vector		avelocity;//24
	Vector		aaccel;//27
	Vector		size;//30
	int			movetype;//33
	int			mass;//34
	float		gravity;//35
	float		orientation[3][3];//36
	gentity_t	*groundentity;//45
	cplane_t	groundplane;//46
	int			groundcontents;//51
	int			numchildren;//52
	int			children[MAX_MODEL_CHILDREN];//53
	float		lightRadius;//69
	str				moveteam;//70
	class Entity	*teamchain;//71
	class Entity	*teammaster;//72
	class Entity	*bindmaster;//73
	qboolean		bind_use_my_angles;//74
	Vector			localorigin;//75
	Vector			localangles;//78
	str				killtarget;//81
	float			health;//82
	float			max_health;//83
	int				deadflag;//84
	int				flags;//85
	int				watertype;//86
	int				waterlevel;//87
	damage_t		takedamage;//88
	EntityPtr		enemy;//89
	float			pain_finished;//93
	float			damage_debounce_time;//94
	int				damage_type;//95
	int				m_iNumGlues;//96
	EntityPtr		m_pGlues[MAX_GLUE_CHILDREN];//97
	int				m_pGluesFlags[MAX_GLUE_CHILDREN];//129
	class Entity	*m_pGlueMaster;//137
	bool			m_bGlueAngles;//138
	qboolean		detach_at_death;//139
	float				stealthMovementScale;//140
	class pathway_ref	*m_BlockedPaths;//141
	int					 m_iNumBlockedPaths;//142
	Vector /*Container<int>*/		immunities;//143 //FIXME
	//146
public:
	Entity();
	~Entity();
	static void Init();
	static void Shutdown();
	static void(__thiscall *Damage_Orignal)(Entity * _this, Entity *pTargetEntity, Entity *pInflictorEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location);

	qboolean checkEntity();
};


void __fastcall Damage(Entity *_this, void* edx, Entity *pTargetEntity, Entity *pInflictorEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location);