#pragma once
#include "classes/vector.h"
#include <map>

inline const char* skyboxes[] = {
        	"None",
		"Black", // sky_l4d_rural02_ldr
		"cs_baggage_skybox_",
		"cs_tibet",
		"embassy",
		"italy",
		"jungle",
		"nukeblank",
		"office",
		"sky_cs15_daylight01_hdr",
		"sky_cs15_daylight02_hdr",
		"sky_cs15_daylight03_hdr",
		"sky_cs15_daylight04_hdr",
		"sky_csgo_cloudy01",
		"sky_csgo_night_flat",
		"sky_csgo_night02",
		"sky_csgo_night02b",
		"sky_day02_05",
		"sky_day02_05_hdr",
		"sky_dust",
		"sky_hr_aztec",
        	"sky_lunacy",
		"sky_venice",
		"vertigo",
		"vertigo_hdr",
		"vertigoblue_hdr",
		"vietnam"
};

enum FrameStage {
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

enum EClassIds {
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBRC4Target,
	CBreachCharge,
	CBreachChargeProjectile,
	CBreakableProp,
	CBreakableSurface,
	CBumpMine,
	CBumpMineProjectile,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDangerZone,
	CDangerZoneController,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDrone,
	CDronegun,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvGasCanister,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFists,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CGrassBurn,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoMapRegion,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemCash,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMapVetoPickController,
	CMaterialModifyControl,
	CMelee,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParadropChopper,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPhysPropAmmoBox,
	CPhysPropLootCrate,
	CPhysPropRadarJammer,
	CPhysPropWeaponUpgrade,
	CPlantedC4,
	CPlasma,
	CPlayerPing,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropCounter,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSnowball,
	CSnowballPile,
	CSnowballProjectile,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CSurvivalSpawnChopper,
	CTablet,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponShield,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWeaponZoneRepulsor,
	CWorld,
	CWorldVguiText,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};

enum ItemIndex {
	INVALID = -1,
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5 = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_KNIFE_BAYONET = 500,
    	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
    	WEAPON_KNIFE_CORD = 517,
    	WEAPON_KNIFE_CANIS = 518,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
    	WEAPON_KNIFE_OUTDOOR = 521,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER,
    	WEAPON_KNIFE_SKELETON = 525,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
};

const ItemIndex pistols[] = {
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_TEC9,
	WEAPON_HKP2000,
	WEAPON_P250,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A
};

const ItemIndex heavyPistols[] = {
	WEAPON_DEAGLE,
	WEAPON_REVOLVER
};

const ItemIndex rifles[] = {
	WEAPON_AK47,
	WEAPON_AUG,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR,
	WEAPON_M4A1,
	WEAPON_SCAR20,
	WEAPON_SG556,
	WEAPON_M4A1_SILENCER
};

const ItemIndex heavyWeapons[] = {
	WEAPON_M249,
	WEAPON_XM1014,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_NOVA
};

const ItemIndex smgs[] = {
	WEAPON_MAC10,
	WEAPON_P90,
	WEAPON_UMP45,
	WEAPON_MP5,
	WEAPON_BIZON,
	WEAPON_MP7,
	WEAPON_MP9
};
enum HitGroups {
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_GEAR
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

#define FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3)	// Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5)	// Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6)	// Player can't move, but keeps key inputs for controlling another entity
#define FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them
#define FL_PARTIALGROUND		(1<<18) // Partially on the ground
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define FL_INWATER				(1<<9)	// In water

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)
#define IN_SPEED		(1 << 17)
#define IN_WALK			(1 << 18)
#define IN_ZOOM			(1 << 19)
#define IN_WEAPON1		(1 << 20)
#define IN_WEAPON2		(1 << 21)
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)
#define IN_GRENADE2		(1 << 24)
#define	IN_ATTACK3		(1 << 25)


// Fuzion
class AnimState {
public:
	char pad_0008[128]; //0x0000
	float lastAnimUpdateTime; //0x0080
	int32_t lastAnimUpdateFrame; //0x0084
	float eyePitch; //0x0088
	float yaw; //0x008C
	float pitch; //0x0090
	float goalFeetYaw; //0x0094
	float currentFeetYaw; //0x0098
	float absMovementDirection; //0x009C  Movement direction on a compass, North = 0, East = 90, South = 180...
	float lastAbsMovementDirection; //0x00A0 ^^^^^ for last tick
	float leanAmount; //0x00A4
	char pad_00A8[4]; //0x00A8
	float feetCycle; //0x00AC Progress from 0.0-1.0 of the legs moving animation.
	float feetYawRate; //0x00B0 How fast to play feetCycle ( walking = slower )
	char pad_00B4[4]; //0x00B4
	float duckProgress; //0x00B8 Progress 0.0-1.0, 0.0 = standing, 1.0 = fully crouched. Also used for jumping. Counts backwards from 1.0 for jumps
	float landingAnimationTimeLeftUntilDone; //0x00BC Adds some time when landing animation starts.
	char pad_00C0[4]; //0x00C0
	Vector origin; //0x00C4
	Vector lastOrigin; //0x00D0
	float velocityX; //0x00DC Speeds on axis
	float velocityY; //0x00E0 ^^^^^^^^^^
	char pad_00E4[4]; //0x00E4
	float currentDirectionX; //0x00E8 -1.0 to 1.0. West is 1.0, East is -1.0. North and South are both 0
	float currentDirectionY; //0x00EC -1.0 to 1.0. North is -1.0, South is 1.0. East and West are both 0
	char pad_00F0[4]; //0x00F0
	float lastKnownDirectionX; //0x00F4 Same as its counterpart above, but this is saved until the next update
	float lastKnownDirectionY; //0x00F8 ^^^^^^^^^^^^^^^^^^^^^^^
	char pad_00FC[4]; //0x00FC
	float horizontalVelocity; //0x0100 Affected by slopes. ( got 240 with knife on a hill )
	float verticalVelocity; //0x0104. Goes up when jumping, negative when falling
	float speed; //0x0108 0.0 -> 1.0, how fast you are going; 1.0 = full speed.
	float feetShuffleSpeed; //0x010C // 0.0-2.0 (approx)
	float feetShuffleSpeed2; //0x0110 // 0.0-3.0 (approx)
	float timeSinceStartedMoving; //0x0114 Jumping and Crouching do not affect these
	float timeSinceStoppedMoving; //0x0118 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	bool onGround; //0x011C True if on ground (do I need to type this?)
	bool inJumpRecoveryAnim; //0x011D True if you're doing one of the retarded knee buckling animations
	char pad_011E[10]; //0x011E
	float heightBeforeJump; //0x0128 Updated right when you jump
	char pad_012C[4]; //0x012C
	float runningAccelProgress; //0x0130 0 - 1.0, Only affected by Running, reaches 1.0 when you are at full speed (ex: 250 w/ knife )
	char pad_0134[68]; //0x0134
	char unkown[572];// Overall Size should be 0x3B0(+4), padding the end here.
}; //Size: 0x0178


const std::map<ItemIndex, const char*> itemIndexMap = {
		{ ItemIndex::INVALID,						""},
		{ ItemIndex::WEAPON_DEAGLE,				"Deagle"},
		{ ItemIndex::WEAPON_ELITE,				"Dual Berettas"},
		{ ItemIndex::WEAPON_FIVESEVEN,			"Five Seven"},
		{ ItemIndex::WEAPON_GLOCK,				"Glock"},
		{ ItemIndex::WEAPON_AK47,					"AK47"},
		{ ItemIndex::WEAPON_AUG,					"AUG"},
		{ ItemIndex::WEAPON_AWP,					"AWP"},
		{ ItemIndex::WEAPON_FAMAS,				"Famas"},
		{ ItemIndex::WEAPON_G3SG1,				"G3SG1"},
		{ ItemIndex::WEAPON_GALILAR,				"Galil"},
		{ ItemIndex::WEAPON_M249,					"M249"},
		{ ItemIndex::WEAPON_M4A1,					"M4A4"},
		{ ItemIndex::WEAPON_MAC10,				"MAC-10"},
		{ ItemIndex::WEAPON_P90,					"P90"},
		{ ItemIndex::WEAPON_UMP45,				"UMP-45"},
        { ItemIndex::WEAPON_MP5,                  "MP5-SD"},
		{ ItemIndex::WEAPON_XM1014,				"XM1014"},
		{ ItemIndex::WEAPON_BIZON,				"PP-Bizon"},
		{ ItemIndex::WEAPON_MAG7,					"MAG-7"},
		{ ItemIndex::WEAPON_NEGEV,				"Negev"},
		{ ItemIndex::WEAPON_SAWEDOFF,				"Sawed-Off"},
		{ ItemIndex::WEAPON_TEC9,					"Tec-9"},
		{ ItemIndex::WEAPON_TASER,				"Zeus x27"},
		{ ItemIndex::WEAPON_HKP2000,				"P2000"},
		{ ItemIndex::WEAPON_MP7,					"MP7"},
		{ ItemIndex::WEAPON_MP9,					"MP9"},
		{ ItemIndex::WEAPON_NOVA,					"Nova"},
		{ ItemIndex::WEAPON_P250,					"P250"},
		{ ItemIndex::WEAPON_SCAR20,				"SCAR-20"},
		{ ItemIndex::WEAPON_SG556,				"SG 556"},
		{ ItemIndex::WEAPON_SSG08,				"SSG 08"},
		{ ItemIndex::WEAPON_KNIFE,				"Knife"},
		{ ItemIndex::WEAPON_FLASHBANG,			"Flashbang"},
		{ ItemIndex::WEAPON_HEGRENADE,			"Grenade"},
		{ ItemIndex::WEAPON_SMOKEGRENADE,			"Smoke"},
		{ ItemIndex::WEAPON_MOLOTOV,				"Molotov"},
		{ ItemIndex::WEAPON_DECOY,				"Decoy"},
		{ ItemIndex::WEAPON_INCGRENADE,			"Incendiary"},
		{ ItemIndex::WEAPON_C4,					"C4"},
		{ ItemIndex::WEAPON_KNIFE_T,				"Knife"},
		{ ItemIndex::WEAPON_M4A1_SILENCER,		"M4A1-S"},
		{ ItemIndex::WEAPON_USP_SILENCER,			"USP-S"},
		{ ItemIndex::WEAPON_CZ75A,				"CZ-75-Auto"},
		{ ItemIndex::WEAPON_REVOLVER,				"R8 Revolver"},
		{ ItemIndex::WEAPON_KNIFE_BAYONET,		"Bayonet"},
		{ ItemIndex::WEAPON_KNIFE_FLIP,			"Flip Knife"},
		{ ItemIndex::WEAPON_KNIFE_GUT,			"Gut Knife"},
		{ ItemIndex::WEAPON_KNIFE_KARAMBIT,		"Karambit"},
		{ ItemIndex::WEAPON_KNIFE_M9_BAYONET,		"M9 Bayonet"},
		{ ItemIndex::WEAPON_KNIFE_TACTICAL,		"Tactical Knife"},
		{ ItemIndex::WEAPON_KNIFE_FALCHION,		"Falchion Knife"},
		{ ItemIndex::WEAPON_KNIFE_SURVIVAL_BOWIE,	"Bowie Knife"},
		{ ItemIndex::WEAPON_KNIFE_BUTTERFLY,		"Butterfly Knife"},
		{ ItemIndex::WEAPON_KNIFE_PUSH,			"Shadow Daggers"},
		{ ItemIndex::WEAPON_KNIFE_URSUS,			"Ursus knife"},
		{ ItemIndex::WEAPON_KNIFE_GYPSY_JACKKNIFE,"Navaja Knife"},
		{ ItemIndex::WEAPON_KNIFE_STILETTO,		"Stiletto Knife"},
		{ ItemIndex::WEAPON_KNIFE_WIDOWMAKER,		"Talon Knife"},
		{ ItemIndex::WEAPON_KNIFE_CSS,			"Classic Knife"},
		{ ItemIndex::WEAPON_KNIFE_GHOST,			"Ghost Knife"},
		{ ItemIndex::WEAPON_KNIFEGG,				"???"},
		{ ItemIndex::GLOVE_STUDDED_BLOODHOUND,	"Bloodhound Gloves"},
		{ ItemIndex::GLOVE_T_SIDE,				"Gloves"},
		{ ItemIndex::GLOVE_CT_SIDE,				"Gloves"},
		{ ItemIndex::GLOVE_SPORTY,				"Sport Gloves"},
		{ ItemIndex::GLOVE_SLICK,					"Slick Gloves"},
		{ ItemIndex::GLOVE_LEATHER_WRAP,			"Leather Wrap Gloves"},
		{ ItemIndex::GLOVE_MOTORCYCLE,			"Motorcycle Gloves"},
		{ ItemIndex::GLOVE_SPECIALIST,			"Specialist Gloves"},
		{ ItemIndex::WEAPON_FISTS,                "Fists"},
		{ ItemIndex::WEAPON_SHIELD,               "Shield"},
		{ ItemIndex::WEAPON_HEALTHSHOT,           "Healthshot"},
		{ ItemIndex::WEAPON_TAGRENADE,            "Tactical Awareness Grenade"},
		{ ItemIndex::WEAPON_BREACHCHARGE,         "Breach Charge"},
		{ ItemIndex::WEAPON_TABLET,               "Tablet"},
		{ ItemIndex::WEAPON_AXE,                  "Axe"},
		{ ItemIndex::WEAPON_HAMMER,               "Hammer"},
		{ ItemIndex::WEAPON_SPANNER,              "Tango#1337 (spanner)"},
		{ ItemIndex::WEAPON_FIREBOMB,             "Firebomb"},
		{ ItemIndex::WEAPON_DIVERSION,            "Decoy"},
		{ ItemIndex::WEAPON_FRAG_GRENADE,         "Grenade"},
		{ ItemIndex::WEAPON_BUMPMINE, 			"Bump Mine"}
};

inline const char* getNameFromItemIndex(ItemIndex index) {
	if (itemIndexMap.find(index) != itemIndexMap.end()) {
		return itemIndexMap.at(index);
	}
	return "invalid item";
}