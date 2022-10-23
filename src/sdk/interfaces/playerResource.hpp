#pragma once
#include "../netvars.hpp"

#define TICKCOUNTWITHPING() (int)(Interfaces::globals->tickcount + ((float)playerResource->GetPing(Globals::localPlayer->index())/1000.f) / Interfaces::globals->interval_per_tick)

class PlayerResource {
public:
	int GetPing(int index) {
		return *(int*)((uintptr_t)this + GETNETVAROFFSET("DT_PlayerResource", "m_iPing") + (index * 4));
	}
};