#include "features.hpp"
#include "../../includes.hpp"

void Features::Spectators::draw() {
    if (CONFIGBOOL("Misc>Misc>Misc>Spectators")) {
        ImGui::Begin("Spectator List", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | (Menu::open ? 0 : ImGuiWindowFlags_NoMouseInputs));
        ImGui::Text("Spectators");
        ImGui::Separator();
        if (Interfaces::engine->IsInGame() && Globals::localPlayer) {
            for (int i = 0; i < Interfaces::globals->maxClients; i++) {
                if (i != Interfaces::engine->GetLocalPlayer()) {
                    Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                    if (p && !p->dormant() && ((int)((uintptr_t)p->observerTarget() & 0xFFF) == Interfaces::engine->GetLocalPlayer())) {
                        player_info_t info;
                        Interfaces::engine->GetPlayerInfo(i, &info);
                        ImGui::Text("%s", info.name);
                    }
                }
            }
        }
        ImGui::End();
    }
}