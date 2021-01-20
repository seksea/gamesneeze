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

class player {
public:
	void* networkable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 16);
	}

	bool isPlayer() {
		typedef bool (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 157)(this);
	}

	bool dormant() {
		typedef bool(*Fn)(void*);
		return getVirtualFunc<Fn>(networkable(), 9)(networkable());
	}

	NETVAR("DT_BaseEntity", "m_Collision", collideable, ICollideable);
    NETVAR("DT_BasePlayer", "m_iHealth", health, int);
	NETVAR("DT_CSPlayer", "m_fFlags", flags, int);
	NETVAR("DT_BaseEntity", "m_bSpotted", spotted, bool);
	NETVAR("DT_BasePlayer", "m_vecOrigin", origin, Vector);
};