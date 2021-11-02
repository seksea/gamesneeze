#pragma once
#include "interfaces/ibaseclientdll.hpp"
#include "interfaces/iprediction.hpp"
#include <map>
#include <utility>

namespace Netvar {
    inline std::map<std::pair<std::string_view, std::string_view>, uintptr_t> offsets {
        /* Entity */
        {std::make_pair("DT_BaseEntity", "m_Collision"), 0},
        {std::make_pair("DT_BaseEntity", "m_iTeamNum"), 0},
        {std::make_pair("DT_BaseEntity", "m_bSpotted"), 0},

        /* Player */
        {std::make_pair("DT_BasePlayer", "m_vecVelocity[0]"), 0},
        {std::make_pair("DT_BasePlayer", "m_nTickBase"), 0},
        {std::make_pair("DT_CSPlayer", "m_iAccount"), 0},
        {std::make_pair("DT_BasePlayer", "m_iHealth"), 0},
        {std::make_pair("DT_CSPlayer", "m_fFlags"), 0},
        {std::make_pair("DT_BasePlayer", "m_aimPunchAngle"), 0},
        {std::make_pair("DT_BasePlayer", "m_viewPunchAngle"), 0},
        {std::make_pair("DT_CSPlayer", "m_hActiveWeapon"), 0},
        {std::make_pair("DT_CSPlayer", "m_hObserverTarget"), 0},
        {std::make_pair("DT_CSPlayer", "m_bHasDefuser"), 0},
        {std::make_pair("DT_BasePlayer", "m_vecViewOffset[0]"), 0},
        {std::make_pair("DT_CSPlayer", "m_angEyeAngles[0]"), 0},
        {std::make_pair("DT_CSPlayer", "m_flLowerBodyYawTarget"), 0},
        {std::make_pair("DT_CSPlayer", "m_flFlashDuration"), 0},
        {std::make_pair("DT_CSPlayer", "m_flFlashMaxAlpha"), 0},
        {std::make_pair("DT_CSPlayer", "m_bIsScoped"), 0},
        {std::make_pair("DT_BasePlayer", "deadflag"), 0},
        {std::make_pair("DT_CSPlayer", "m_bHasHelmet"), 0},
        {std::make_pair("DT_CSPlayer", "m_ArmorValue"), 0},
        {std::make_pair("DT_BaseEntity", "m_nRenderMode"), 0}, // Used for movetype
        {std::make_pair("DT_CSPlayer", "m_nSurvivalTeam"), 0},

        /* Item */
        {std::make_pair("DT_BaseAttributableItem", "m_iItemDefinitionIndex"), 0},

        /* Weapon */
        {std::make_pair("DT_BaseCombatWeapon", "m_hOwner"), 0},
        {std::make_pair("DT_BaseCombatWeapon", "m_hOwnerEntity"), 0},
        {std::make_pair("DT_BaseCombatWeapon", "m_iItemIDHigh"), 0},
        {std::make_pair("DT_BaseCombatWeapon", "m_iAccountID"), 0},
        {std::make_pair("DT_BaseCombatWeapon", "m_nFallbackPaintKit"), 0},
        {std::make_pair("DT_BaseCombatWeapon", "m_flFallbackWear"), 0},
        {std::make_pair("DT_BaseCombatWeapon", "m_nFallbackStatTrak"), 0},

        /* Bomb */
        {std::make_pair("DT_PlantedC4", "m_flC4Blow"), 0},

        /* Tonemap Controller */
        {std::make_pair("DT_EnvTonemapController", "m_bUseCustomAutoExposureMin"), 0},
        {std::make_pair("DT_EnvTonemapController", "m_bUseCustomAutoExposureMax"), 0},
        {std::make_pair("DT_EnvTonemapController", "m_flCustomAutoExposureMin"), 0},
        {std::make_pair("DT_EnvTonemapController", "m_flCustomAutoExposureMax"), 0},

        /* Player Resource */
        {std::make_pair("DT_PlayerResource", "m_iPing"), 0},

        /* Fog Controller */
        {std::make_pair("DT_FogController", "m_fog.enable"), 0},
        {std::make_pair("DT_FogController", "m_fog.start"), 0},
        {std::make_pair("DT_FogController", "m_fog.end"), 0},
        {std::make_pair("DT_FogController", "m_fog.farz"), 0},
        {std::make_pair("DT_FogController", "m_fog.maxdensity"), 0},
        {std::make_pair("DT_FogController", "m_fog.colorPrimary"), 0},
    };
    bool init();
}

namespace Offsets {
    typedef void (*SendClantag) (const char*, const char*);
    inline SendClantag sendClantag;

    typedef void (*SetPlayerReady) (const char*);
    inline SetPlayerReady setPlayerReady;

    inline uintptr_t radarIsHltvCheck;

    typedef void (*InitKeyValues)(KeyValues*, const char*);
    inline InitKeyValues initKeyValues;

    typedef void (*LoadFromBuffer)(KeyValues*, const char*, const char*, void*, const char*, void*);
    inline LoadFromBuffer loadFromBuffer;

    typedef bool (*SetNamedSkybox)(const char *);
    inline SetNamedSkybox setNamedSkybox;

    typedef bool (*LineGoesThroughSmoke) (Vector, Vector, int16_t);
    inline LineGoesThroughSmoke lineGoesThroughSmoke;

    typedef BaseClientState* (*GetLocalClient) (int);
    inline GetLocalClient getLocalClient;

    inline int* predictionSeed;
    inline unsigned int animState;
    inline CMoveData* moveData;

    typedef void (*SaveData)(void*, const char*, int , int);
    inline SaveData saveData;

    typedef void (*RestoreData)(void*, const char*, int , int);
    inline RestoreData restoreData;

    typedef void (*OnPostRestoreData)(void*);
    inline OnPostRestoreData onPostRestoreData;

    typedef void (*RestoreEntityToPredictedFrame)(void*, int, int);
    inline RestoreEntityToPredictedFrame restoreEntityToPredictedFrame;
}

#define GETNETVAROFFSET(table, prop) Netvar::offsets.at({table, prop})
#define NETVAR( table, prop, func, type ) type& func() {return *reinterpret_cast<type*>(uintptr_t(this) + GETNETVAROFFSET(table, prop));}; type* func##_ptr() {return reinterpret_cast<type*>(uintptr_t(this) + GETNETVAROFFSET(table, prop));}
