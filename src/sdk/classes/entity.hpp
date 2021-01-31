#pragma once
#include "../netvars.hpp"
#include "vector.h"
#include "../../utils/utils.hpp"

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

	bool dormant() {
		typedef bool(*Fn)(void*);
		return getVirtualFunc<Fn>(networkable(), 9)(networkable());
	}

	int index() {
		typedef int(*Fn)(void*);
		return getVirtualFunc<Fn>(networkable(), 10)(networkable());
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
	NETVAR("DT_CSPlayer", "m_iAccount", money, int);
    NETVAR("DT_BasePlayer", "m_iHealth", health, int);
	NETVAR("DT_CSPlayer", "m_fFlags", flags, int);
};