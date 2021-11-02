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
	std::byte		pad0[0x4];						// 0x0000
	std::uintptr_t	hLastGround;					// 0x0004
	bool			bInPrediction;					// 0x0008
	bool			bIsFirstTimePredicted;			// 0x0009
	bool			bEnginePaused;					// 0x000A
	bool			bOldCLPredictValue;				// 0x000B
	int				iPreviousStartFrame;			// 0x000C
	int				nIncomingPacketNumber;			// 0x0010
	float			flLastServerWorldTimeStamp;		// 0x0014

	struct Split_t
	{
		bool		bIsFirstTimePredicted;			// 0x0018
		std::byte	pad0[0x3];						// 0x0019
		int			nCommandsPredicted;				// 0x001C
		int			nServerCommandsAcknowledged;	// 0x0020
		int			iPreviousAckHadErrors;			// 0x0024
		float		flIdealPitch;					// 0x0028
		int			iLastCommandAcknowledged;		// 0x002C
		bool		bPreviousAckErrorTriggersFullLatchReset; // 0x0030
		CUtlVector<std::uintptr_t> vecEntitiesWithPredictionErrorsInLastAck; // 0x0031
		bool		bPerformedTickShift;			// 0x0045
	};

	Split_t			Split[1];						// 0x0018
	
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