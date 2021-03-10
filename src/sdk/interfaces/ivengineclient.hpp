#pragma once
#include <cstdint>
#include "../../utils/utils.hpp"
#include "../classes/vector.h"

#define FULLUPDATE() Offsets::getLocalClient(-1)->m_nDeltaTick = -1

class BaseClientState {
public:
	char pad_0000[296]; //0x0000
	class INetChannel* m_NetChannel; //0x0128
	char pad_0130[124]; //0x0130
	float m_flNextCmdTime; //0x01AC
	int32_t m_nServerCount; //0x01B0
	int32_t m_nCurrentSequence; //0x01B4
	char pad_01B8[8]; //0x01B8
	float clockOffset1; //0x01C0
	float clockOffset2; //0x01C4
	float clockOffset3; //0x01C8
	float clockOffset4; //0x01CC
	float clockOffset5; //0x01D0
	float clockOffset6; //0x01D4
	float clockOffset7; //0x01D8
	float clockOffset8; //0x01DC
	float clockOffset9; //0x01E0
	float clockOffset10; //0x01E4
	float clockOffset11; //0x01E8
	float clockOffset12; //0x01EC
	float clockOffset13; //0x01F0
	float clockOffset14; //0x01F4
	float clockOffset15; //0x01F8
	float clockOffset16; //0x01FC
	int32_t m_iCurClockOffset; //0x0200
	int32_t m_nServerTick; //0x0204
	int32_t m_nClientTick; //0x0208
	int32_t m_nDeltaTick; //0x020C
	bool m_bPaused; //0x0210
	char pad_0211[15]; //0x0211
	char m_szLevelName[260]; //0x0220
	char m_szLevelNameShort[80]; //0x0324
	char m_szGroupName[80]; //0x0374
};

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

	bool IsVoiceRecording() {
        typedef bool (*Fn)(void*);
        return getVirtualFunc<Fn>(this, 225)(this);
    }
};