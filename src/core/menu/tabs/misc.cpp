#include "../menu.hpp"
#include <filesystem>
#include "../config.hpp"

void Menu::drawMiscTab() {
    ImGui::Text("Misc");
    ImGui::SameLine();ImGui::PopStyleVar(); 
    ImGui::TextDisabled("Credits!");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("sekc (ofcourse)\nAll other contributors on GitHub (sadly none as of right now ;'( )\nand ocornut for his great ImGui UI framework");

    ImGui::BeginChild("Trolling", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 260), true); {
        ImGui::Text("Trolling");
        ImGui::Separator();
        ImGui::Text("Radio Exploit");
        static char victim[128] = "";
        ImGui::InputText("Victim's name", victim, IM_ARRAYSIZE(victim));
        static char message[128] = "";
        ImGui::InputText("Message##tbox", message, IM_ARRAYSIZE(message));
        static char skinName[128] = "★ M9 Bayonet | Doppler";
        ImGui::InputText("Skin/Weapon##tbox", skinName, IM_ARRAYSIZE(skinName));
        ImGui::Text("Send fake: ");
        ImGui::SameLine();
        if (ImGui::Button("Message##btn")) {
            Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer! \xe2\x80\xa8") + victim + " :""\x01"" " + message + "\"").c_str());
        }
        ImGui::SameLine();
        if (ImGui::Button("Server")) {
            Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer! \xe2\x80\xa8""\x01""Console: ") + message + "\"").c_str());
        }
        ImGui::SameLine();
        if (ImGui::Button("VAC")) {
            Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer! \xe2\x80\xa8""\x02""") + victim + " has been permanently banned from official CS:GO servers.\"").c_str());
        }
        ImGui::SameLine();
        if (ImGui::Button("Kick")) {
            Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer! \xe2\x80\xa8""\x01""Player ") + victim + " left the game (Kicked from the session)\"").c_str());
        }
        ImGui::SameLine();
        if (ImGui::Button("Unbox")) {
            Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer! \xe2\x80\xa8""\x0B""") + victim + """\x01"" has opened a container and found:""\x02"" " + skinName + "\"").c_str());
        }
        ImGui::SameLine();
        ImGui::TextDisabled("?");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Sends a fake message into the chat via a radio message that uses\nchars to create a newline and change colours (pastebin.com/pZvCnGaC),\nyou can do this legit too via the 'playerchatwheel . \"\"' command!\n\nOnly works if you are alive and only teammates can see the message :(");

        ImGui::EndChild();
    }
    ImGui::SameLine();
    ImGui::BeginChild("Config", ImVec2(0, 263), true); {
        ImGui::Text("Config");
        ImGui::Separator();
        if (ImGui::Button("Save")) {

        };
        if (ImGui::Button("Load")) {
            
        };
        ImGui::EndChild();
    }
    ImGui::BeginChild("Movement", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.35f, 260), true); {
        ImGui::Text("Movement");
        ImGui::Separator();
        ImGui::EndChild();
    }
    ImGui::SameLine();
    ImGui::BeginChild("Misc", ImVec2(0, 263), true); {
        ImGui::Text("Misc");
        ImGui::Separator();
        ImGui::Checkbox("Developer window", &devWindow);
        ImGui::EndChild();
    }
}