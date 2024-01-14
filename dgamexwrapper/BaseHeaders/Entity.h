#pragma once
#include "SimpleEntity.h"
#include "dgamex86.h"

#define MAX_GLUE_CHILDREN 8
#define MAX_MODEL_CHILDREN_AA 8
#define MAX_MODEL_CHILDREN_DSH 16
#define MAX_MODEL_CHILDREN_DBT 16

class Entity {}; // empty definition to avoid mistakes
typedef int EntityPtr[4];


class pathway_ref {
public:
	short int from;
	short int to;
};


/*
 * Class Entity
 * Used as an important utility class for the patch.
 **/
class EntityAA : public SimpleEntity
{

public:
	int			entnum;//0
	int			radnum;//1
	gentityAA_t* edict;//2
	gclientAA_t* client;//3
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
	gentity_t* groundentity;//45
	cplane_t	groundplane;//46
	int			groundcontents;//51
	int			numchildren;//52
	int			children[MAX_MODEL_CHILDREN_AA];//53
	float		lightRadius;//69
	str				moveteam;//70
	class EntityAA* teamchain;//71
	class EntityAA* teammaster;//72
	class EntityAA* bindmaster;//73
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
	class EntityAA* m_pGlueMaster;//137
	bool			m_bGlueAngles;//138
	qboolean		detach_at_death;//139
	float				stealthMovementScale;//140
	class pathway_ref* m_BlockedPaths;//141
	int					 m_iNumBlockedPaths;//142
	Vector /*Container<int>*/		immunities;//143 //FIXME
	//146
};

/*
 * Class Entity
 * Used as an important utility class for the patch.
 **/
class EntityDSH : public SimpleEntity
{
public:
	int			entnum;//0
	int			radnum;//1
	gentityDSH_t	*edict;//2
	gclientDSH_t	*client;//3
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
	int			children[MAX_MODEL_CHILDREN_DSH];//53
	float		lightRadius;//69
	str				moveteam;//70
	class EntityDSH *teamchain;//71
	class EntityDSH *teammaster;//72
	class EntityDSH *bindmaster;//73
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
	class EntityDSH *m_pGlueMaster;//137
	bool			m_bGlueAngles;//138
	qboolean		detach_at_death;//139
	float				stealthMovementScale;//140
	class pathway_ref	*m_BlockedPaths;//141
	int					 m_iNumBlockedPaths;//142
	Vector /*Container<int>*/		immunities;//143 //FIXME
	//146
public:
};

using EntityDBT = EntityDSH;



/*
 * Class EntityNF
 * Used as an wrapper class for different entity definitions (depending on which game is running).
 **/
class EntityNF
{

	union realEntityType
	{
		EntityAA entAA;
		EntityDSH entDSH;
		EntityDBT entDBT;
	};
	realEntityType* realEntity;

#define ENTITYNF_MEMEBER_GETTER(varname) \
		decltype(EntityAA::varname)& init_##varname() \
		{\
			static decltype(EntityAA::varname) s_##varname; \
			if (!realEntity) return s_##varname; \
			if (gameInfo.IsAA())\
				return realEntity->entAA.varname;\
			else if (gameInfo.IsSH())\
				return realEntity->entDSH.varname;\
			else if (gameInfo.IsBT())\
				return realEntity->entDBT.varname;\
		}

	gclient_t* const & init_client()
	{
		//GClient has its own null checks.
		if (gameInfo.IsAA())
			return (gclient_t*)(realEntity->entAA.client);
		else if (gameInfo.IsSH())
			return (gclient_t*)(realEntity->entDSH.client);
		else if (gameInfo.IsBT())
			return (gclient_t*)(realEntity->entDBT.client);
	}
	ENTITYNF_MEMEBER_GETTER(entnum);
	ENTITYNF_MEMEBER_GETTER(damage_type);



#undef ENTITYNF_MEMEBER_GETTER
public:
	int& entnum;
	int& damage_type;
	//gclient_t*const& client;
	GClient client;
	EntityNF(Entity * e) : realEntity((realEntityType* )(e)), entnum(init_entnum()), damage_type(init_damage_type()), client(init_client())
	{

	}

	static void Init();
	static void Shutdown();
	static void(__thiscall* Damage_Orignal)(Entity* _this, Entity* pTargetEntity, Entity* pInflictorEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location);

	bool isValid()
	{
		return realEntity != NULL;
	}

	operator Entity* ()
	{
		return (Entity*)realEntity;
	}

	EntityNF* operator ->()
	{
		return this;
	}
	qboolean checkEntity();
};

void __fastcall Damage(Entity *_this, void* edx, Entity * pInflictorEntity, Entity * pAttackerEntity, float damage, float vectPositionx, float vectPositiony, float vectPositionz, float vectDirectionx, float vectDirectiony, float vectDirectionz, float vectNormalx, float vectNormaly, float vectNormalz, int knockback, int damageflags, int meansofdeath, int location);