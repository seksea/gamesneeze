#include "features.hpp"
#include "../../includes.hpp"
#include <cstring>

void Features::PlayerList::draw() {
    if (CONFIGBOOL("Misc>Misc>Misc>Player List") && (CONFIGBOOL("Misc>Misc>Misc>Player List Only When Menu Open") ? Menu::open : true)) {
        ImGui::Begin("Player List", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | (Menu::open ? 0 : ImGuiWindowFlags_NoMouseInputs));
        ImGui::Text("Players");
        ImGui::Separator();
        if (Interfaces::engine->IsInGame() && Globals::localPlayer) {
            ImGui::Columns(3, NULL);
            ImGui::Text("Name");
            ImGui::NextColumn();
            ImGui::Text("Health");
            ImGui::NextColumn();
            ImGui::Text("Money");
            ImGui::NextColumn();
            static Player* selectedPlayer;
            static player_info_t selectedPlayerInfo;
            for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                if (p) {
                    ImGui::Separator();
                    player_info_t info;
                    Interfaces::engine->GetPlayerInfo(i, &info);

                    ImGui::TextColored(p->team() == 2 ? ImColor(229, 189, 94, 255) : ImColor(110, 149, 215, 255), "%s", info.name);
                    if (ImGui::IsItemClicked()) {
                        selectedPlayer = p;
                        selectedPlayerInfo = info;
                        ImGui::OpenPopup("Player Popup");
                    }
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetTooltip("Click for player settings!");
                    }

                    ImGui::NextColumn();
                    ImColor healthColor = ImColor(0, 255, 0);
                    ImGui::ColorConvertHSVtoRGB(((float)p->health()-20.f)/255.f, 1.f, 1.f, healthColor.Value.x, healthColor.Value.y, healthColor.Value.z);
                    ImGui::TextColored(healthColor, "%d", p->health());
                    ImGui::NextColumn();
                    ImGui::TextColored(ImColor(100, 200, 0, 255), "$%d", p->money());
                    ImGui::NextColumn();
                }
            }
            if (ImGui::BeginPopup("Player Popup")){
                ImGui::Text("Player Options | %s", selectedPlayerInfo.name);
                ImGui::Separator();
                if (selectedPlayer) {
                    ImGui::Text("Name: %s", selectedPlayerInfo.name); ImGui::SameLine(); if (ImGui::Button("Steal Name")) {
                        static auto nameConvar = Interfaces::convar->FindVar("name");
                        nameConvar->fnChangeCallback = 0;
                        
                        char* name = selectedPlayerInfo.name;
                        strcat(name, " ");
                        nameConvar->SetValue(name);
                    }
                    ImGui::Text("GUID: %s", selectedPlayerInfo.guid);
                    ImGui::Text("XUID: %li", selectedPlayerInfo.xuid);
                    
                    ImGui::Separator();
                    static char message[128] = "";
                    ImGui::InputText("Message##tbox", message, IM_ARRAYSIZE(message));
                    static char skinName[128] = "★ M9 Bayonet | Doppler";
                    ImGui::InputText("Skin/Weapon##tbox", skinName, IM_ARRAYSIZE(skinName));
                    ImGui::Text("Send fake: ");
                    ImGui::SameLine();
                    if (ImGui::Button("Message##btn")) {
                        char radioMessage[512];
                        snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8%s :\x01 %s\"", selectedPlayerInfo.name, message);
                        Interfaces::engine->ExecuteClientCmd(radioMessage);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("VAC")) {
                        char radioMessage[512];
                        snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x02""%s has been permanently banned from official CS:GO servers.\"", selectedPlayerInfo.name);
                        Interfaces::engine->ExecuteClientCmd(radioMessage);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Kick")) {
                        char radioMessage[512];
                        snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x01""Player %s left the game (Kicked from the session)\"", selectedPlayerInfo.name);
                        Interfaces::engine->ExecuteClientCmd(radioMessage);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Unbox")) {
                        char radioMessage[512];
                        snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x0B""%s \x01 has opened a container and found: \x02%s\"", selectedPlayerInfo.name, skinName);
                        Interfaces::engine->ExecuteClientCmd(radioMessage);
                    }
                    ImGui::SameLine();
                    ImGui::TextDisabled("?");
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip("Sends a fake message into the chat via a radio message that uses\nchars to create a newline and change colours (pastebin.com/pZvCnGaC),\nyou can do this legit too via the 'playerchatwheel . \"\"' command!\n\nOnly works if you are alive and only teammates can see the message :(");
                }
                ImGui::EndPopup();
            }
            ImGui::Separator();
            ImGui::Columns(1);
        }
        ImGui::End();
    }
}
