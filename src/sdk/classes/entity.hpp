#pragma once
#include "../netvars.hpp"
#include "vector.h"
#include "../../utils/utils.hpp"
#include <functional>

inline std::map<float, int, std::greater<float>> entityDistanceMap; // Map containing entity distance
void cachePlayers();

class ICollideable {
public:
	virtual void pad0();
	virtual const Vector& OBBMins() const;
	virtual const Vector& OBBMaxs() const;
};

class Entity {
public:
	void* networkable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 16);
	}

	void* renderable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x8);
	}

	ClientClass* clientClass() {
		typedef ClientClass*(*Fn)(void*);
		return getVirtualFunc<Fn>(networkable(), 2)(networkable());
	}

	bool dormant() {
		typedef bool(*Fn)(void*);
		return getVirtualFunc<Fn>(networkable(), 9)(networkable());
	}

	int index() {
		typedef int(*Fn)(void*);
		return getVirtualFunc<Fn>(networkable(), 10)(networkable());
	}

	model_t* model() {
		typedef model_t* (*Fn)(void*);
		return getVirtualFunc<Fn>(renderable(), 8)(renderable());
	}

	bool setupBones(matrix3x4_t* pBoneMatrix, int nMaxBones, int nBoneMask, float flCurTime = 0) {
		typedef bool (*Fn)(void*, matrix3x4_t*, int, int, float);
		return getVirtualFunc<Fn>(renderable(), 13)(renderable(), pBoneMatrix, nMaxBones, nBoneMask, flCurTime);
	}

	bool shouldDraw() {
		typedef bool (*Fn)(void*);
		return getVirtualFunc<Fn>(renderable(), 5)(renderable());
	}

	const Vector& origin()
	{
		typedef const Vector& (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 12)(this);
	}

	bool isPlayer() {
		typedef bool (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 157)(this);
	}

	NETVAR("DT_BaseEntity", "m_Collision", collideable, ICollideable);
	NETVAR("DT_BaseEntity", "m_iTeamNum", team, int);
	NETVAR("DT_BaseEntity", "m_bSpotted", spotted, bool);
};

class Player : public Entity {
public:
	NETVAR("DT_BasePlayer", "m_vecVelocity[0]", velocity, Vector);
	NETVAR("DT_BasePlayer", "m_nTickBase", tickbase, unsigned int);
	NETVAR("DT_CSPlayer", "m_iAccount", money, int);
    NETVAR("DT_BasePlayer", "m_iHealth", health, int);
	NETVAR("DT_CSPlayer", "m_fFlags", flags, int);
	NETVAR("DT_BasePlayer", "m_aimPunchAngle", aimPunch, QAngle);
	NETVAR("DT_BasePlayer", "m_viewPunchAngle", viewPunch, QAngle);
	NETVAR("DT_CSPlayer", "m_hActiveWeapon", activeWeapon, void*);
	NETVAR("DT_CSPlayer", "m_hObserverTarget", observerTarget, Player*);
	NETVAR("DT_CSPlayer", "m_bHasDefuser", defuser, bool);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", viewOffset, Vector);
    NETVAR("DT_CSPlayer", "m_angEyeAngles[0]", eyeAngles, QAngle);
	NETVAR("DT_CSPlayer", "m_flLowerBodyYawTarget", lbyTarget, float);
	NETVAR("DT_CSPlayer", "m_bIsScoped", scoped, bool);
	NETVAR("DT_BasePlayer", "deadflag", deadflag, bool);
    NETVAR("DT_CSPlayer", "m_flFlashDuration", flashDuration, float);
	NETVAR("DT_CSPlayer", "m_flFlashMaxAlpha", maxFlashAlpha, float);
	NETVAR("DT_CSPlayer", "m_bHasHelmet", helmet, bool);
	NETVAR("DT_CSPlayer", "m_ArmorValue", armor, int);
	NETVAR("DT_CSPlayer", "m_nSurvivalTeam", survivalTeam, int);

	AnimState* animState() {
		return *reinterpret_cast<AnimState **>((uintptr_t)
		this + Offsets::animState);
	}

	QAngle* viewAngles() {
		return (QAngle*)((uintptr_t)deadflag_ptr() + 0x4);
	}

	Vector eyePos() {
		return origin() + ((viewOffset().z > 0) ? viewOffset() : Vector(0, 0, (flags() & (1 << 1)) ? 46 : 64)); // For some reason some ents' viewoffset is all 0s, this is a hacky fix for it
	}

	int crosshair() {
		return *reinterpret_cast<int*>((uintptr_t)defuser_ptr()+0x7c);
	}

	int moveType() {
		return *reinterpret_cast<int*>((uintptr_t)this + GETNETVAROFFSET("DT_BaseEntity", "m_nRenderMode") + 1);
	}

	void saveData(const char *context, int slot, int type) {
		Offsets::saveData(this, context, slot, type);
	}

	void restoreData (const char *context, int slot, int type) {
		Offsets::restoreData(this, context, slot, type);
	}

	void onPostRestoreData() {
		Offsets::onPostRestoreData(this);
	}

	bool isEnemy();
	bool getHitboxBones(matrix3x4_t* boneMatrix);
	bool getAnythingBones(matrix3x4_t* boneMatrix);
	Vector getBonePos(int bone);
	bool visible();
};

class Item : public Entity{
public:
	NETVAR("DT_BaseAttributableItem", "m_iItemDefinitionIndex", itemIndex, ItemIndex);
};

class Weapon : public Item {
public:
	NETVAR("DT_BaseCombatWeapon", "m_hOwner", owner, int);

	NETVAR("DT_BaseCombatWeapon", "m_iItemIDHigh", itemIDHigh, int);
	NETVAR("DT_BaseCombatWeapon", "m_iAccountID", accountID, int);
	NETVAR("DT_BaseCombatWeapon", "m_nFallbackPaintKit", paintKit, int);
	NETVAR("DT_BaseCombatWeapon", "m_flFallbackWear", wear, float);
	NETVAR("DT_BaseCombatWeapon", "m_nFallbackStatTrak", statTrack, int);

	float GetSpread() {
		typedef float (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 521)(this);
	}

	float GetInaccuracy() {
		typedef float (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 551)(this);
	}
};

class PlantedC4 : public Item {
public:
	NETVAR("DT_PlantedC4", "m_flC4Blow", time, float);
};

class TonemapController {
public:
	NETVAR("DT_EnvTonemapController", "m_bUseCustomAutoExposureMin", useExposureMin, bool);
	NETVAR("DT_EnvTonemapController", "m_bUseCustomAutoExposureMax", useExposureMax, bool);
	NETVAR("DT_EnvTonemapController", "m_flCustomAutoExposureMin", exposureMin, float);
	NETVAR("DT_EnvTonemapController", "m_flCustomAutoExposureMax", exposureMax, float);
};

class FogController {
public:
	NETVAR("DT_FogController", "m_fog.enable", enable, bool);
	NETVAR("DT_FogController", "m_fog.start", start, float);
	NETVAR("DT_FogController", "m_fog.end", end, float);
	NETVAR("DT_FogController", "m_fog.farz", farz, float);
	NETVAR("DT_FogController", "m_fog.maxdensity", maxDensity, float);
	NETVAR("DT_FogController", "m_fog.colorPrimary", colorPrimary, int);
};
