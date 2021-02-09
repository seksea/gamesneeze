#include "../menu.hpp"
#include <filesystem>
#include "../config.hpp"

void Menu::drawMiscTab() {
    ImGui::Text("Misc");
    ImGui::SameLine();ImGui::PopStyleVar(); 
    ImGui::TextDisabled("Credits!");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("sekc (ofcourse)\nAll other contributors on GitHub (cristeigabriel, crazily, luk1337 & tango1337)\nand ocornut for his great ImGui UI framework");

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
            char radioMessage[128];
            snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8%s :\x01 %s\"", victim, message);
            Interfaces::engine->ExecuteClientCmd(radioMessage);
        }
        ImGui::SameLine();
        if (ImGui::Button("Server")) {
            char radioMessage[128];
            snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x01""Console: %s\"", message);
            Interfaces::engine->ExecuteClientCmd(radioMessage);
        }
        ImGui::SameLine();
        if (ImGui::Button("VAC")) {
            char radioMessage[128];
            snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x02""%s has been permanently banned from official CS:GO servers.\"", victim);
            Interfaces::engine->ExecuteClientCmd(radioMessage);
        }
        ImGui::SameLine();
        if (ImGui::Button("Kick")) {
            char radioMessage[128];
            snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x01""Player %s left the game (Kicked from the session)\"", victim);
            Interfaces::engine->ExecuteClientCmd(radioMessage);
        }
        ImGui::SameLine();
        if (ImGui::Button("Unbox")) {
            char radioMessage[128];
            snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x0B""%s \x01 has opened a container and found: \x02%s\"", victim, skinName);
            Interfaces::engine->ExecuteClientCmd(radioMessage);
        }
        ImGui::SameLine();
        ImGui::TextDisabled("?");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Sends a fake message into the chat via a radio message that uses\nchars to create a newline and change colours (pastebin.com/pZvCnGaC),\nyou can do this legit too via the 'playerchatwheel . \"\"' command!\n\nOnly works if you are alive and only teammates can see the message :(");

        ImGui::EndChild();
    }
    ImGui::SameLine();
    ImGui::BeginChild("Config", ImVec2(0, 260), true); {
        ImGui::Text("Config");
        ImGui::Separator();
        if (ImGui::Button("Save")) {
            Config::save();
        };
        if (ImGui::Button("Load")) {
            Config::load();            
        };
        ImGui::EndChild();
    }
    ImGui::BeginChild("Movement", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.35f, 260), true); {
        ImGui::Text("Movement");
        ImGui::Separator();
        ImGui::Checkbox("Auto Hop", &CONFIGBOOL("Misc>Movement>Auto Hop"));
        ImGui::EndChild();
    }
    ImGui::SameLine();
    ImGui::BeginChild("Misc", ImVec2(0, 263), true); {
        ImGui::Text("Misc");
        ImGui::Separator();
        ImGui::Checkbox("Developer window", &devWindow);
        ImGui::Checkbox("Force square radar", &CONFIGBOOL("Misc>Misc>Force square radar"));
        ImGui::Checkbox("Rank Revealer", &CONFIGBOOL("Misc>Misc>Rank Revealer"));

        ImGui::InputText("##clantag-tbox", clantag, IM_ARRAYSIZE(clantag));
        ImGui::SameLine();
        ImGui::Checkbox("Clantag", &CONFIGBOOL("Misc>Misc>Clantag"));
        ImGui::Checkbox("Clantag Marquee", &CONFIGBOOL("Misc>Misc>Clantag Marquee"));
        ImGui::Checkbox("Bee Movie Clantag", &CONFIGBOOL("Misc>Misc>Bee Movie Clantag"));
        ImGui::Checkbox("Spectators", &CONFIGBOOL("Misc>Misc>Spectators"));
        ImGui::Checkbox("Player List", &CONFIGBOOL("Misc>Misc>Player List"));
        ImGui::Checkbox("Auto Accept", &CONFIGBOOL("Misc>Misc>Auto Accept"));
        ImGui::Checkbox("Auto Defuse", &CONFIGBOOL("Misc>Misc>Auto Defuse"));
        if (CONFIGBOOL("Misc>Misc>Auto Defuse")) {
            ImGui::SameLine();
            ImGui::Checkbox("Latest Defuse", &CONFIGBOOL("Misc>Misc>Latest Defuse"));
        }
        ImGui::Checkbox("Fast Duck", &CONFIGBOOL("Misc>Misc>Fast Duck"));
        ImGui::EndChild();
    }
}
