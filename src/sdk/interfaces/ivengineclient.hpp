#pragma once
#include <cstdint>
#include "../../utils/utils.hpp"
#include "../classes/vector.h"

// Engine player info, no game related infos here
typedef struct player_info_s
{
    int64_t __pad0;
    union {
        int64_t xuid;
        struct {
            int xuidlow;
            int xuidhigh;
        };
    };
    char name[128];
    int userid;
    char guid[33];
    unsigned int friendsid;
    char friendsname[128];
    bool fakeplayer;
    bool ishltv;
    unsigned int customfiles[4];
    unsigned char filesdownloaded;
} player_info_t;


// https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/public/cdll_int.h#L194
class IVEngineClient {
public:
    // Gets the dimensions of the game window
	void GetScreenSize(int& width, int& height) {
		typedef void (*Fn)(void*, int&, int&);
		return getVirtualFunc<Fn>(this, 5)(this, width, height);
	}

    // Fill in the player info structure for the specified player index (name, model, etc.)
	bool GetPlayerInfo(int iIndex, player_info_t *pInfo) {
		typedef bool (*Fn)(void*, int, player_info_t*);
		return getVirtualFunc<Fn>(this, 8)(this, iIndex, pInfo);
	}

    // Retrieve the player entity number for a specified userID
	int GetPlayerForUserID(int UserID) {
		typedef int (*Fn)(void*, int);
		return getVirtualFunc<Fn>(this, 9)(this, UserID);
	}

    // Get the entity index of the local player
	int GetLocalPlayer() {
		typedef int (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 12)(this);
	}

	// Copy current view orientation into va
	void GetViewAngles(QAngle& angle) {
		typedef void (*Fn)(void*, QAngle&);
		return getVirtualFunc<Fn>(this, 18)(this, angle);
	}

    // Retrieve the current game's maxclients setting
	int GetMaxClients() {
		typedef int (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 20)(this);
	}

    // Returns true if the player is fully connected and active in game (i.e, not still loading)
	bool IsInGame() {
		typedef bool (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 26)(this);
	}

    // Returns true if the player is connected, but not necessarily active in game (could still be loading)
	bool IsConnected() {
		typedef bool (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 27)(this);
	}

	const VMatrix& WorldToScreenMatrix() {
		typedef VMatrix& (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 37)(this);
	}

    // Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
	// And then executes the command string immediately (vs ClientCmd() which executes in the next frame)
	//
	// Note: this is NOT checked against the FCVAR_CLIENTCMD_CAN_EXECUTE vars.
	void ExecuteClientCmd(const char* szCmdString) {
		typedef void (*Fn)(void*, const char*);
		return getVirtualFunc<Fn>(this, 108)(this, szCmdString);
	}
};