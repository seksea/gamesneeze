#include "features.hpp"
#include "../../includes.hpp"

void Features::SkinChanger::frameStageNotify(FrameStage frame) {
    if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_START && Globals::localPlayer && Interfaces::engine->IsInGame() && Globals::localPlayer->health() > 0) {
        // TODO: get all weapons, not just active weapon
        Weapon* weapon = (Weapon*) Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
        try {
            if (weapon && weapon->itemIndex() != ItemIndex::INVALID) {
                const char* weaponName = itemIndexMap.at(weapon->itemIndex());
                
                char buf[256];
                snprintf(buf, 256, "Misc>Skins>Skins>%s>PaintKit", weaponName);

                char buf2[256];
                snprintf(buf2, 256, "Misc>Skins>Skins>%s>Wear", weaponName);

                char buf3[256];
                snprintf(buf3, 256, "Misc>Skins>Skins>%s>StatTrack", weaponName);

                int paintkit = CONFIGINT(buf);
                float wear = (float)CONFIGINT(buf2)/100.f;
                int statTrack = CONFIGINT(buf3);

                player_info_t info;
                Interfaces::engine->GetPlayerInfo(Interfaces::engine->GetLocalPlayer(), &info);
                *weapon->accountID_ptr() = info.xuid;
                *weapon->itemIDHigh_ptr() = -1;
                *weapon->paintKit_ptr() = paintkit;
                *weapon->wear_ptr() = wear;
                *weapon->statTrack_ptr() = statTrack;
            }
        } catch (std::out_of_range& e) {
            //Log::log(WARN, "itemDefinitionIndex %d not found!", ((Weapon*)ent)->itemIndex());
        }
    }
}