#include "../../includes.hpp"
#include <cstring>

// p100 flex ur distro
char distro[32];
void getDistro() {
    static bool gotDistro = false;
    if (!gotDistro) {
        std::ifstream osRelease("/etc/os-release");
        if (osRelease.is_open()) {
            std::string line;
            while (getline(osRelease, line)) {
                if (strstr(line.c_str(), "ID=") == line.c_str()) {
                    if (line.substr(3) == "ubuntu") {
                        memcpy(distro, "shitbuntu", sizeof("shitbuntu"));
                    }
                    else {
                        memcpy(distro, line.substr(3).c_str(), 32);
                    }
                }
            }
            osRelease.close();
        }
        gotDistro = true;
    }
}

void Menu::drawOverlay(ImDrawList* drawList) {
    getDistro();

    Globals::drawList = drawList;
    if(!CONFIGBOOL("Misc>Misc>Misc>Disable Watermark")) {
        char watermarkText[64];
        sprintf(watermarkText, "gamesneeze (%s) | %.1f FPS | %i ms", distro, ImGui::GetIO().Framerate, (Interfaces::engine->IsInGame() && playerResource) ? playerResource->GetPing(Interfaces::engine->GetLocalPlayer()) : 0);
        // Hacky way to do black shadow but it works
        Globals::drawList->AddText(ImVec2(4, 4), ImColor(0, 0, 0, 255), watermarkText);
        Globals::drawList->AddText(ImVec2(3, 3), ImColor(255, 255, 255, 255), watermarkText);
    }

    Features::ESP::draw();
    Features::RecoilCrosshair::draw();
    Features::Spectators::draw();
    Features::PlayerList::draw();
    Features::FlappyBird::draw();
    Features::Notifications::draw();
    Features::Hitmarkers::draw();
}