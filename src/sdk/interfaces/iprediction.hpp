#pragma once
#include "iclientmode.hpp"

class Entity;
class CMoveData;

class IGameMovement {
public:
	void ProcessMovement(Entity* player, CMoveData* move) {
		typedef void (*Fn)(void* , Entity* , CMoveData* );
		return getVirtualFunc<Fn>(this, 2)(this, player, move);
	}

	void StartTrackPredictionErrors(Entity* player) {
		typedef void (*Fn)(void* , Entity* );
		return getVirtualFunc<Fn>(this, 4)(this, player);
	}

	void FinishTrackPredictionErrors(Entity* player) {
		typedef void (*Fn)(void* , Entity* );
		return getVirtualFunc<Fn>(this, 5)(this, player);
	}
};

class IMoveHelper {
public:
	void SetHost(Entity* host) {
		typedef void (*Fn)(void* , Entity* );
		return getVirtualFunc<Fn>(this, 1)(this, host);
	}
};

class IPrediction {
public:
	void SetupMove(Entity* player, CUserCmd* cmd, IMoveHelper* helper, CMoveData* move) {
		typedef void (*Fn)(void* , Entity* , CUserCmd* , IMoveHelper* , CMoveData* );
		return getVirtualFunc<Fn>(this, 21)(this, player, cmd, helper, move);
	}

	void FinishMove(Entity* player, CUserCmd* cmd, CMoveData* move) {
		typedef void (*Fn)(void*, Entity*, CUserCmd*, CMoveData*);
		return getVirtualFunc<Fn>(this, 22)(this, player, cmd, move);
	}
};