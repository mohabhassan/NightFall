#include "Player.h"
#include "g_misc.h"
#include "detours.h"
#include "ScriptedEvent.h"

#define RESPAWN_ADDR 0x311530C0
#define KILLED_ADDR 0x31153D60

ResponseDef<Player> *Player::Responses;

CustomEventResponseSet<Player> Player::cerSet{};
void(__thiscall *Player::Respawn_Orignal)(Player*_this, Event *ev);
void(__thiscall *Player::Killed_Orignal)(Player*_this, Event *ev);

/* Offset updates:
 * x-> opm size
 * - : opm is larger
 * + : opm is smaller
 * 
 * BT Player sizeof is 2404 (x-52)
 * BT Sentient sizeof is 1504 (x+24) -> Fixed, no var added/removed
 * BT Animate sizeof is 940 (x+24) -> Fixed, 2 dimmies added
 * BT Entity sizeof is 652 (x+16) -> Fixed, no var added/removed.
 * BT SimpleEntity sizeof is 68 (x-4) -> Remove Listener.m_EndList (-4)
 * BT Listener sizeof is 20 (x-4) -> Remove m_EndList (-4)
 * BT Class sizeof is 8
 **/
Player::Player()
{
	sizeof(Player);
}
template<typename T, typename U> constexpr size_t classOffsetOf(U T::*member)
{
	return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

Player::~Player()
{
}
void Player::PrintOffsets()
{
	gi.Printf("Player::num_kills offset: %d\n", classOffsetOf(&Player::num_kills));
	gi.Printf("Player::num_deaths offset: %d\n", classOffsetOf(&Player::num_deaths));
	gi.Printf("Player::buttons offset: %d\n", classOffsetOf(&Player::buttons));
	/*sizeof(last_ucmd);
	gi.Printf("Player::statemap_Legs offset: %d\n", classOffsetOf(&Player::statemap_Legs));
	gi.Printf("Player::statemap_Torso offset: %d\n", classOffsetOf(&Player::statemap_Torso));
	gi.Printf("Player::currentState_Legs offset: %d\n", classOffsetOf(&Player::currentState_Legs));
	gi.Printf("Player::currentState_Torso offset: %d\n", classOffsetOf(&Player::currentState_Torso));
	gi.Printf("Player::last_torso_anim_name offset: %d\n", classOffsetOf(&Player::last_torso_anim_name));
	gi.Printf("Player::last_leg_anim_name offset: %d\n", classOffsetOf(&Player::last_leg_anim_name));
	gi.Printf("Player::partAnim offset: %d\n", classOffsetOf(&Player::partAnim));
	gi.Printf("Player::m_iPartSlot offset: %d\n", classOffsetOf(&Player::m_iPartSlot));
	gi.Printf("Player::m_fPartBlends offset: %d\n", classOffsetOf(&Player::m_fPartBlends));
	gi.Printf("Player::partOldAnim offset: %d\n", classOffsetOf(&Player::partOldAnim));
	gi.Printf("Player::partBlendMult offset: %d\n", classOffsetOf(&Player::partBlendMult));
	gi.Printf("Player::animdone_Legs offset: %d\n", classOffsetOf(&Player::animdone_Legs));
	gi.Printf("Player::animdone_Torso offset: %d\n", classOffsetOf(&Player::animdone_Torso));
	gi.Printf("Player::legs_conditionals offset: %d\n", classOffsetOf(&Player::legs_conditionals));
	gi.Printf("Player::torso_conditionals offset: %d\n", classOffsetOf(&Player::torso_conditionals));
	gi.Printf("Player::m_pLegsPainCond offset: %d\n", classOffsetOf(&Player::m_pLegsPainCond));
	gi.Printf("Player::m_pTorsoPainCond offset: %d\n", classOffsetOf(&Player::m_pTorsoPainCond));
	gi.Printf("Player::m_fLastDeltaTime offset: %d\n", classOffsetOf(&Player::m_fLastDeltaTime));
	gi.Printf("Player::m_bActionAnimPlaying offset: %d\n", classOffsetOf(&Player::m_bActionAnimPlaying));
	gi.Printf("Player::m_iBaseActionAnimSlot offset: %d\n", classOffsetOf(&Player::m_iBaseActionAnimSlot));
	gi.Printf("Player::m_sActionAnimName offset: %d\n", classOffsetOf(&Player::m_sActionAnimName));
	gi.Printf("Player::m_iActionAnimType offset: %d\n", classOffsetOf(&Player::m_iActionAnimType));
	gi.Printf("Player::m_bActionAnimDone offset: %d\n", classOffsetOf(&Player::m_bActionAnimDone));
	gi.Printf("Player::m_sOldActionAnimName offset: %d\n", classOffsetOf(&Player::m_sOldActionAnimName));
	gi.Printf("Player::m_fOldActionAnimWeight offset: %d\n", classOffsetOf(&Player::m_fOldActionAnimWeight));
	gi.Printf("Player::m_fOldActionAnimFadeTime offset: %d\n", classOffsetOf(&Player::m_fOldActionAnimFadeTime));
	gi.Printf("Player::m_iOldActionAnimType offset: %d\n", classOffsetOf(&Player::m_iOldActionAnimType));
	gi.Printf("Player::m_bMovementAnimPlaying offset: %d\n", classOffsetOf(&Player::m_bMovementAnimPlaying));
	gi.Printf("Player::m_iBaseMovementAnimSlot offset: %d\n", classOffsetOf(&Player::m_iBaseMovementAnimSlot));
	gi.Printf("Player::m_sMovementAnimName offset: %d\n", classOffsetOf(&Player::m_sMovementAnimName));
	gi.Printf("Player::m_sOldMovementAnimName offset: %d\n", classOffsetOf(&Player::m_sOldMovementAnimName));
	gi.Printf("Player::m_fOldMovementWeight offset: %d\n", classOffsetOf(&Player::m_fOldMovementWeight));
	gi.Printf("Player::m_fOldMovementFadeTime offset: %d\n", classOffsetOf(&Player::m_fOldMovementFadeTime));
	gi.Printf("Player::m_sSlotAnimNames offset: %d\n", classOffsetOf(&Player::m_sSlotAnimNames));
	gi.Printf("Player::movecontrol offset: %d\n", classOffsetOf(&Player::movecontrol));
	gi.Printf("Player::m_iMovePosFlags offset: %d\n", classOffsetOf(&Player::m_iMovePosFlags));
	gi.Printf("Player::last_camera_type offset: %d\n", classOffsetOf(&Player::last_camera_type));
	gi.Printf("Player::oldvelocity offset: %d\n", classOffsetOf(&Player::oldvelocity));
	gi.Printf("Player::old_v_angle offset: %d\n", classOffsetOf(&Player::old_v_angle));
	gi.Printf("Player::oldorigin offset: %d\n", classOffsetOf(&Player::oldorigin));
	gi.Printf("Player::animspeed offset: %d\n", classOffsetOf(&Player::animspeed));
	gi.Printf("Player::airspeed offset: %d\n", classOffsetOf(&Player::airspeed));
	gi.Printf("Player::m_vPushVelocity offset: %d\n", classOffsetOf(&Player::m_vPushVelocity));
	gi.Printf("Player::blend offset: %d\n", classOffsetOf(&Player::blend));
	gi.Printf("Player::fov offset: %d\n", classOffsetOf(&Player::fov));
	gi.Printf("Player::selectedfov offset: %d\n", classOffsetOf(&Player::selectedfov));
	gi.Printf("Player::m_iInZoomMode offset: %d\n", classOffsetOf(&Player::m_iInZoomMode));
	gi.Printf("Player::v_angle offset: %d\n", classOffsetOf(&Player::v_angle));
	gi.Printf("Player::m_vViewPos offset: %d\n", classOffsetOf(&Player::m_vViewPos));
	gi.Printf("Player::m_vViewAng offset: %d\n", classOffsetOf(&Player::m_vViewAng));
	gi.Printf("Player::buttons offset: %d\n", classOffsetOf(&Player::buttons));
	gi.Printf("Player::new_buttons offset: %d\n", classOffsetOf(&Player::new_buttons));
	gi.Printf("Player::server_new_buttons offset: %d\n", classOffsetOf(&Player::server_new_buttons));
	gi.Printf("Player::respawn_time offset: %d\n", classOffsetOf(&Player::respawn_time));
	gi.Printf("Player::last_attack_button offset: %d\n", classOffsetOf(&Player::last_attack_button));
	gi.Printf("Player::damage_blood offset: %d\n", classOffsetOf(&Player::damage_blood));
	gi.Printf("Player::damage_alpha offset: %d\n", classOffsetOf(&Player::damage_alpha));
	gi.Printf("Player::damage_blend offset: %d\n", classOffsetOf(&Player::damage_blend));
	gi.Printf("Player::damage_from offset: %d\n", classOffsetOf(&Player::damage_from));
	gi.Printf("Player::damage_angles offset: %d\n", classOffsetOf(&Player::damage_angles));
	gi.Printf("Player::damage_count offset: %d\n", classOffsetOf(&Player::damage_count));
	gi.Printf("Player::damage_yaw offset: %d\n", classOffsetOf(&Player::damage_yaw));
	gi.Printf("Player::next_painsound_time offset: %d\n", classOffsetOf(&Player::next_painsound_time));
	gi.Printf("Player::waitForState offset: %d\n", classOffsetOf(&Player::waitForState));
	gi.Printf("Player::camera offset: %d\n", classOffsetOf(&Player::camera));
	gi.Printf("Player::actor_camera offset: %d\n", classOffsetOf(&Player::actor_camera));
	gi.Printf("Player::actor_to_watch offset: %d\n", classOffsetOf(&Player::actor_to_watch));
	gi.Printf("Player::actor_camera_right offset: %d\n", classOffsetOf(&Player::actor_camera_right));
	gi.Printf("Player::starting_actor_camera_right offset: %d\n", classOffsetOf(&Player::starting_actor_camera_right));
	gi.Printf("Player::music_current_mood offset: %d\n", classOffsetOf(&Player::music_current_mood));
	gi.Printf("Player::music_fallback_mood offset: %d\n", classOffsetOf(&Player::music_fallback_mood));
	gi.Printf("Player::music_current_volume offset: %d\n", classOffsetOf(&Player::music_current_volume));
	gi.Printf("Player::music_saved_volume offset: %d\n", classOffsetOf(&Player::music_saved_volume));
	gi.Printf("Player::music_volume_fade_time offset: %d\n", classOffsetOf(&Player::music_volume_fade_time));
	gi.Printf("Player::reverb_type offset: %d\n", classOffsetOf(&Player::reverb_type));
	gi.Printf("Player::reverb_level offset: %d\n", classOffsetOf(&Player::reverb_level));
	gi.Printf("Player::gibbed offset: %d\n", classOffsetOf(&Player::gibbed));
	gi.Printf("Player::pain offset: %d\n", classOffsetOf(&Player::pain));
	gi.Printf("Player::pain_dir offset: %d\n", classOffsetOf(&Player::pain_dir));
	gi.Printf("Player::pain_type offset: %d\n", classOffsetOf(&Player::pain_type));
	gi.Printf("Player::pain_location offset: %d\n", classOffsetOf(&Player::pain_location));
	gi.Printf("Player::take_pain offset: %d\n", classOffsetOf(&Player::take_pain));
	gi.Printf("Player::nextpaintime offset: %d\n", classOffsetOf(&Player::nextpaintime));
	gi.Printf("Player::knockdown offset: %d\n", classOffsetOf(&Player::knockdown));
	gi.Printf("Player::canfall offset: %d\n", classOffsetOf(&Player::canfall));
	gi.Printf("Player::falling offset: %d\n", classOffsetOf(&Player::falling));
	gi.Printf("Player::feetfalling offset: %d\n", classOffsetOf(&Player::feetfalling));
	gi.Printf("Player::falldir offset: %d\n", classOffsetOf(&Player::falldir));
	gi.Printf("Player::mediumimpact offset: %d\n", classOffsetOf(&Player::mediumimpact));
	gi.Printf("Player::hardimpact offset: %d\n", classOffsetOf(&Player::hardimpact));
	gi.Printf("Player::music_forced offset: %d\n", classOffsetOf(&Player::music_forced));
	gi.Printf("Player::last_ucmd offset: %d\n", classOffsetOf(&Player::last_ucmd));
	gi.Printf("Player::last_eyeinfo offset: %d\n", classOffsetOf(&Player::last_eyeinfo));
	gi.Printf("Player::animheight offset: %d\n", classOffsetOf(&Player::animheight));
	gi.Printf("Player::yaw_forward offset: %d\n", classOffsetOf(&Player::yaw_forward));
	gi.Printf("Player::yaw_left offset: %d\n", classOffsetOf(&Player::yaw_left));
	gi.Printf("Player::atobject offset: %d\n", classOffsetOf(&Player::atobject));
	gi.Printf("Player::atobject_dist offset: %d\n", classOffsetOf(&Player::atobject_dist));
	gi.Printf("Player::atobject_dir offset: %d\n", classOffsetOf(&Player::atobject_dir));
	gi.Printf("Player::toucheduseanim offset: %d\n", classOffsetOf(&Player::toucheduseanim));
	gi.Printf("Player::useanim_numloops offset: %d\n", classOffsetOf(&Player::useanim_numloops));
	gi.Printf("Player::useitem_in_use offset: %d\n", classOffsetOf(&Player::useitem_in_use));
	gi.Printf("Player::move_left_vel offset: %d\n", classOffsetOf(&Player::move_left_vel));
	gi.Printf("Player::move_right_vel offset: %d\n", classOffsetOf(&Player::move_right_vel));
	gi.Printf("Player::move_backward_vel offset: %d\n", classOffsetOf(&Player::move_backward_vel));
	gi.Printf("Player::move_forward_vel offset: %d\n", classOffsetOf(&Player::move_forward_vel));
	gi.Printf("Player::move_up_vel offset: %d\n", classOffsetOf(&Player::move_up_vel));
	gi.Printf("Player::move_down_vel offset: %d\n", classOffsetOf(&Player::move_down_vel));
	gi.Printf("Player::moveresult offset: %d\n", classOffsetOf(&Player::moveresult));
	gi.Printf("Player::damage_multiplier offset: %d\n", classOffsetOf(&Player::damage_multiplier));
	gi.Printf("Player::m_voiceType offset: %d\n", classOffsetOf(&Player::m_voiceType));
	gi.Printf("Player::num_deaths offset: %d\n", classOffsetOf(&Player::num_deaths));
	gi.Printf("Player::num_kills offset: %d\n", classOffsetOf(&Player::num_kills));
	gi.Printf("Player::num_won_matches offset: %d\n", classOffsetOf(&Player::num_won_matches));
	gi.Printf("Player::num_lost_matches offset: %d\n", classOffsetOf(&Player::num_lost_matches));
	gi.Printf("Player::m_bTempSpectator offset: %d\n", classOffsetOf(&Player::m_bTempSpectator));
	gi.Printf("Player::m_bSpectator offset: %d\n", classOffsetOf(&Player::m_bSpectator));
	gi.Printf("Player::m_bAllowFighting offset: %d\n", classOffsetOf(&Player::m_bAllowFighting));
	gi.Printf("Player::m_bReady offset: %d\n", classOffsetOf(&Player::m_bReady));
	gi.Printf("Player::m_iPlayerSpectating offset: %d\n", classOffsetOf(&Player::m_iPlayerSpectating));
	gi.Printf("Player::dm_team offset: %d\n", classOffsetOf(&Player::dm_team));
	gi.Printf("Player::current_team offset: %d\n", classOffsetOf(&Player::current_team));
	gi.Printf("Player::m_fTeamSelectTime offset: %d\n", classOffsetOf(&Player::m_fTeamSelectTime));
	gi.Printf("Player::m_pLastSpawnpoint offset: %d\n", classOffsetOf(&Player::m_pLastSpawnpoint));
	gi.Printf("Player::voted offset: %d\n", classOffsetOf(&Player::voted));
	gi.Printf("Player::votecount offset: %d\n", classOffsetOf(&Player::votecount));
	gi.Printf("Player::m_fWeapSelectTime offset: %d\n", classOffsetOf(&Player::m_fWeapSelectTime));
	gi.Printf("Player::fAttackerDispTime offset: %d\n", classOffsetOf(&Player::fAttackerDispTime));
	gi.Printf("Player::pAttackerDistPointer offset: %d\n", classOffsetOf(&Player::pAttackerDistPointer));
	gi.Printf("Player::m_iInfoClient offset: %d\n", classOffsetOf(&Player::m_iInfoClient));
	gi.Printf("Player::m_iInfoClientHealth offset: %d\n", classOffsetOf(&Player::m_iInfoClientHealth));
	gi.Printf("Player::m_fInfoClientTime offset: %d\n", classOffsetOf(&Player::m_fInfoClientTime));
	gi.Printf("Player::m_iNumObjectives offset: %d\n", classOffsetOf(&Player::m_iNumObjectives));
	gi.Printf("Player::m_iObjectivesCompleted offset: %d\n", classOffsetOf(&Player::m_iObjectivesCompleted));
	gi.Printf("Player::m_sPerferredWeaponOverride offset: %d\n", classOffsetOf(&Player::m_sPerferredWeaponOverride));
	gi.Printf("Player::mvTrail offset: %d\n", classOffsetOf(&Player::mvTrail));
	gi.Printf("Player::mvTrailEyes offset: %d\n", classOffsetOf(&Player::mvTrailEyes));
	gi.Printf("Player::mCurTrailOrigin offset: %d\n", classOffsetOf(&Player::mCurTrailOrigin));
	gi.Printf("Player::mLastTrailTime offset: %d\n", classOffsetOf(&Player::mLastTrailTime));
	gi.Printf("Player::m_iNumHitsTaken offset: %d\n", classOffsetOf(&Player::m_iNumHitsTaken));
	gi.Printf("Player::m_iNumEnemiesKilled offset: %d\n", classOffsetOf(&Player::m_iNumEnemiesKilled));
	gi.Printf("Player::m_iNumObjectsDestroyed offset: %d\n", classOffsetOf(&Player::m_iNumObjectsDestroyed));
	gi.Printf("Player::m_iNumShotsFired offset: %d\n", classOffsetOf(&Player::m_iNumShotsFired));
	gi.Printf("Player::m_iNumHits offset: %d\n", classOffsetOf(&Player::m_iNumHits));
	gi.Printf("Player::m_fAccuracy offset: %d\n", classOffsetOf(&Player::m_fAccuracy));
	gi.Printf("Player::m_fTimeUsed offset: %d\n", classOffsetOf(&Player::m_fTimeUsed));
	gi.Printf("Player::m_iNumHeadShots offset: %d\n", classOffsetOf(&Player::m_iNumHeadShots));
	gi.Printf("Player::m_iNumTorsoShots offset: %d\n", classOffsetOf(&Player::m_iNumTorsoShots));
	gi.Printf("Player::m_iNumLeftLegShots offset: %d\n", classOffsetOf(&Player::m_iNumLeftLegShots));
	gi.Printf("Player::m_iNumRightLegShots offset: %d\n", classOffsetOf(&Player::m_iNumRightLegShots));
	gi.Printf("Player::m_iNumGroinShots offset: %d\n", classOffsetOf(&Player::m_iNumGroinShots));
	gi.Printf("Player::m_iNumLeftArmShots offset: %d\n", classOffsetOf(&Player::m_iNumLeftArmShots));
	gi.Printf("Player::m_iNumRightArmShots offset: %d\n", classOffsetOf(&Player::m_iNumRightArmShots));*/
}

void Player::Init()
{
	//PrintOffsets();
	cerSet.AddEventResponse(new Event(
		"ptest",
		EV_DEFAULT,
		"IFSB",
		"test_int test_float test_string test_bool",
		"PLAYER TEST COMMAND"
	),
		&Player::Test);

	MiscInit();

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


	Respawn_Orignal = reinterpret_cast<void(__thiscall *)(Player*_this, Event*)>(RESPAWN_ADDR);
	LONG ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourAttach(&(PVOID&)(Player::Respawn_Orignal), (PVOID)(&Respawn));
	ret = DetourTransactionCommit();

	Killed_Orignal = reinterpret_cast<void(__thiscall *)(Player*_this, Event*)>(KILLED_ADDR);
	ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourAttach(&(PVOID&)(Player::Killed_Orignal), (PVOID)(&Killed));
	ret = DetourTransactionCommit();
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
	delete[] Responses;

	cerSet.Clear();

	LONG ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourDetach(&(PVOID&)(Player::Respawn_Orignal), (PVOID)(&Respawn));
	ret = DetourTransactionCommit();


	ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourDetach(&(PVOID&)(Player::Killed_Orignal), (PVOID)(&Killed));
	ret = DetourTransactionCommit();
}

void Player::Test(Event*ev)
{
	str strTat = ev->GetString(2);
	gentity_t *gent = G_GetEntityByClient(0);
	gi.centerprintf(gent, "Player Test success");
}

void __fastcall Respawn(Player *_this,Event * ev)
{
	ScriptedEvent sev(SEV_SPAWN);

	if (sev.isRegistered())
	{
		sev.Trigger({ (Entity*)_this });
	}
	_this->Respawn_Orignal(_this, ev);
}

void __fastcall Killed(Player *_this, Event * ev)
{
	ScriptedEvent sev(SEV_KILL);

	if (sev.isRegistered())
	{
		sev.Trigger({
			ev->GetEntity(1),
			ev->GetFloat(2),
			ev->GetEntity(3),
			ev->GetVector(4),
			ev->GetVector(5),
			ev->GetVector(6),
			ev->GetInteger(7),
			ev->GetInteger(8),
			ev->GetInteger(9),
			ev->GetInteger(10),
			_this
		});
	}
	_this->Killed_Orignal(_this, ev);
}
