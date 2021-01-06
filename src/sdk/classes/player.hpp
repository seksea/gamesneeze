#pragma once
#include "../netvars.hpp"
#include "vector.h"

class player {
public:
	NETVAR("DT_CSPlayer", "m_fFlags", flags, int)
    NETVAR("DT_BasePlayer", "m_iHealth", health, int);
	NETVAR("DT_BasePlayer", "m_vecOrigin", origin, Vector);
	NETVAR("DT_BaseEntity", "m_bSpotted", spotted, bool)
};