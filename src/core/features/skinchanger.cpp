#include "features.hpp"
#include "../../includes.hpp"

void Features::SkinChanger::frameStageNotify(FrameStage frame) {
    if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
        if (Globals::localPlayer) {
            if (Interfaces::engine->IsInGame()) {
                if (Globals::localPlayer->health() > 0) {
                    Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
                    // TODO: per weapon skin changer configging
                    if (weapon) {
                        player_info_t info;
                        Interfaces::engine->GetPlayerInfo(Interfaces::engine->GetLocalPlayer(), &info);
                        *weapon->accountID_ptr() = info.xuid;
                        *weapon->itemIDHigh_ptr() = -1;
                        *weapon->paintKit_ptr() = CONFIGINT("Misc>Skins>Skins>PaintKit");
                        *weapon->wear_ptr() = (float)CONFIGINT("Misc>Skins>Skins>Wear")/100.f;
                        *weapon->statTrack_ptr() = CONFIGINT("Misc>Skins>Skins>StatTrack");
                    }
                }
            }
        }
    }
}