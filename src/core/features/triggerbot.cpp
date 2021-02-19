#include "features.hpp"

void Features::Triggerbot::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Legit>Triggerbot>Triggerbot")) {
        if (Menu::CustomWidgets::isKeyDown(CONFIGINT("Legit>Triggerbot>Key"))) {
            if (Globals::localPlayer) {
                int indexAtCrosshair = Globals::localPlayer->crosshair();
                if (indexAtCrosshair && indexAtCrosshair <= 64) {
                    Player* p = (Player*)Interfaces::entityList->GetClientEntity(indexAtCrosshair);
                    if (p->team() != Globals::localPlayer->team()) {
                        cmd->buttons |= (1 << 0);
                    }
                }
            }
        }
    }
}