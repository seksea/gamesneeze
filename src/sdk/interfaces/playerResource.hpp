#pragma once
#include "../netvars.hpp"

class PlayerResource {
public:
	int GetPing(int index) {
		return *(int*)((uintptr_t)this + GETNETVAROFFSET("DT_PlayerResource", "m_iPing") + (index * 4));
	}
};