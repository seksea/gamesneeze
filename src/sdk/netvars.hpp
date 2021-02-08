#pragma once
#include "interfaces/ibaseclientdll.hpp"
#include <map>

namespace Netvar {
    inline std::map<std::pair<std::string_view, std::string_view>, uintptr_t> offsets {
        /* Entity */
        {std::make_pair("DT_BaseEntity", "m_Collision"), 0},
        {std::make_pair("DT_BaseEntity", "m_iTeamNum"), 0},
        {std::make_pair("DT_BaseEntity", "m_bSpotted"), 0},

        /* Player */
        {std::make_pair("DT_CSPlayer", "m_iAccount"), 0},
        {std::make_pair("DT_BasePlayer", "m_iHealth"), 0},
        {std::make_pair("DT_CSPlayer", "m_fFlags"), 0},
        {std::make_pair("DT_BasePlayer", "m_aimPunchAngle"), 0},
        {std::make_pair("DT_CSPlayer", "m_hActiveWeapon"), 0},
        {std::make_pair("DT_CSPlayer", "m_hObserverTarget"), 0},

        /* Item */
        {std::make_pair("DT_BaseAttributableItem", "m_iItemDefinitionIndex"), 0},

        /* Weapon */
        {std::make_pair("DT_BaseCombatWeapon", "m_hOwner"), 0},

        /* Bomb */
        {std::make_pair("DT_PlantedC4", "m_flC4Blow"), 0},
    };
    bool init();
}

namespace Offsets {
    typedef void (*SendClantag) (const char*, const char*);
    inline SendClantag sendClantag;

    typedef void (*SetPlayerReady) (const char*);
    inline SetPlayerReady setPlayerReady;

    inline uintptr_t radarIsHltvCheck;
}

#define GETNETVAROFFSET(table, prop) Netvar::offsets.at({table, prop})
#define NETVAR( table, prop, func, type ) type& func() {return *reinterpret_cast<type*>(uintptr_t(this) + GETNETVAROFFSET(table, prop));}; type* func##_ptr() {return reinterpret_cast<type*>(uintptr_t(this) + GETNETVAROFFSET(table, prop));}