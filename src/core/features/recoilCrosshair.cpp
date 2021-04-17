#include "features.hpp"
#include "../../includes.hpp"

float spread;
float innacuracy;

void Features::RecoilCrosshair::draw() {
    if (Globals::localPlayer && Interfaces::engine->IsInGame() && 
            Globals::localPlayer->health() > 0 &&
            (CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair") ||
            CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair"))) {
        float rad;
        int x = Globals::screenSizeX / 2;
        int y = Globals::screenSizeY / 2;
        int dx = Globals::screenSizeX / Globals::FOV;
        int dy = Globals::screenSizeY / Globals::FOV;
        QAngle punchAngle = Globals::localPlayer->aimPunch();
        if (CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair")) {
            rad = 5;
            x = (int)(x - (dx * punchAngle.y));
            y = (int)(y + (dy * punchAngle.x));
        }
        if (CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair")) {
            rad = ((spread + innacuracy) * Globals::screenSizeY) / 1.5f;
        }
        if (CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair>Only When Shooting")) {
            if (Globals::localPlayer->aimPunch().IsZero() && !CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair"))
                return;
        }
        if (CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair") &&
            !CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair")) {
            Globals::drawList->AddRectFilled(ImVec2(x - 4, y - 1), ImVec2(x + 5, y + 2), CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Border Color"));
            Globals::drawList->AddRectFilled(ImVec2(x - 1, y - 4), ImVec2(x + 2, y + 5), CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Border Color"));
            Globals::drawList->AddLine(ImVec2(x - 3, y), ImVec2(x + 4, y), CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Color"));
            Globals::drawList->AddLine(ImVec2(x, y + 3), ImVec2(x, y - 4), CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Color"));
        }
        else {
            Globals::drawList->AddCircleFilled(ImVec2(x, y), rad, CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Color"));
            Globals::drawList->AddCircle(ImVec2(x, y), rad, CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Border Color"));
        }
    }
}

void Features::RecoilCrosshair::frameStageNotify(FrameStage frame) {
    if (Globals::localPlayer && Interfaces::engine->IsInGame() && 
            Globals::localPlayer->health() > 0 && frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END &&
            (CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair") ||
            CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair"))) {
        Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
        if (weapon) {
            // get spread and inaccuracy in FSN as if you do it when you draw sometimes you can run it too early and the game will crash
            spread = weapon->GetSpread();
            innacuracy = weapon->GetInaccuracy();
        }
    }
}