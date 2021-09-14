#include "../../includes.hpp"
#include "features.hpp"

void bhop(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Auto Hop")) {
        if (Globals::localPlayer->moveType() == 9)
            return;
        if (CONFIGBOOL("Misc>Misc>Movement>Humanised Bhop")) {
            // https://www.unknowncheats.me/forum/counterstrike-global-offensive/333797-humanised-bhop.html
            static int hopsRestricted = 0;
            static int hopsHit = 0;
            if (!(Globals::localPlayer->flags() & FL_ONGROUND)) {
                cmd->buttons &= ~IN_JUMP;
                hopsRestricted = 0;
            }
            else if ((rand() % 100 > CONFIGINT("Misc>Misc>Movement>Bhop Hitchance") &&
                hopsRestricted < CONFIGINT("Misc>Misc>Movement>Bhop Max Misses")) ||
                (CONFIGINT("Misc>Misc>Movement>Bhop Max Hops Hit") > 0 &&
                    hopsHit > CONFIGINT("Misc>Misc>Movement>Bhop Max Hops Hit"))) {
                cmd->buttons &= ~IN_JUMP;
                hopsRestricted++;
                hopsHit = 0;
            }
            else {
                hopsHit++;
            }
        }
        else {
            if (!(Globals::localPlayer->flags() & FL_ONGROUND)) {
                cmd->buttons &= ~IN_JUMP;
            }
        }
    }
}

void edgeJump(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Edge Jump") &&
            Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Edge Jump Key")) &&
            Features::Movement::flagsBackup & FL_ONGROUND &&
            !(Globals::localPlayer->flags() & FL_ONGROUND))
        cmd->buttons |= IN_JUMP;
}

void jumpBug(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>JumpBug") &&
            Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>JumpBug Key")) &&
            !(Features::Movement::flagsBackup & FL_ONGROUND || Features::Movement::flagsBackup & FL_PARTIALGROUND) &&
            (Globals::localPlayer->flags() & FL_ONGROUND || Globals::localPlayer->flags() & FL_PARTIALGROUND)) {
        cmd->buttons |= IN_DUCK;
        cmd->buttons &= ~IN_JUMP;
        Features::Movement::allowBhop = false;
    }
    else {
        Features::Movement::allowBhop = true;
    }
}

bool checkEdgebug(){ // need to find/get a better edgebug detection method, unsure if this will work on 128tick
    return !(Features::Movement::velBackup.z >= -7 || 
            floor(Globals::localPlayer->velocity().z) != -7 || 
            (Globals::localPlayer->flags() & FL_ONGROUND)) && 
            Globals::localPlayer->velocity().Length2D() >= Features::Movement::velBackup.Length2D();
}

void edgeBugEnforcer(CUserCmd* cmd) {
    static int buttBackup;
    static QAngle viewBackup;
    static Vector2D moveBackup;

    if (!CONFIGBOOL("Misc>Misc>Movement>EdgeBug") ||
            !Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>EdgeBug Key"))) {
        Features::Movement::shouldEdgebug = false;
        return;
    }

    if (Features::Movement::shouldEdgebug) {
        cmd->sidemove = 0;
        cmd->forwardmove = 0;
    }
    else {
        buttBackup = cmd->buttons;
        viewBackup = cmd->viewangles;
        moveBackup.x = cmd->sidemove;
        moveBackup.y = cmd->forwardmove;
    }
}

void Features::Movement::prePredCreateMove(CUserCmd* cmd) {
    if (!Globals::localPlayer)
        return;

    flagsBackup = Globals::localPlayer->flags();
    velBackup = Globals::localPlayer->velocity();

    if (allowBhop)
        bhop(cmd);
    
    edgeBugEnforcer(cmd);
}

void Features::Movement::postPredCreateMove(CUserCmd* cmd) {
    if (!Globals::localPlayer ||
            Globals::localPlayer->moveType() == MOVETYPE_LADDER ||
            Globals::localPlayer->moveType() == MOVETYPE_NOCLIP)
        return;

    edgeJump(cmd);
    jumpBug(cmd);
}

void Features::Movement::edgeBugPredictor(CUserCmd* cmd) {
    if (!CONFIGBOOL("Misc>Misc>Movement>EdgeBug") ||
            !Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>EdgeBug Key")))
        return;

    edgeBugEnforcer(cmd);
    shouldEdgebug = checkEdgebug();
    int predictAmount = 128; // TODO: make amount configurable
    for (int i = 0; i < predictAmount; i++) { // this is roughly the famous 'clarity' edgebug (lol)
        if (shouldEdgebug)
            break;
        Features::Prediction::start(cmd);
        if (Globals::localPlayer->flags() & FL_ONGROUND) {
            break;
        }
        shouldEdgebug = checkEdgebug();
        edgebugPos = Globals::localPlayer->origin();
        Features::Prediction::end();
    }
}

void Features::Movement::draw() {
    if (Features::Movement::shouldEdgebug) {
        Globals::drawList->AddText(ImVec2((Globals::screenSizeX / 2) - (ImGui::CalcTextSize("EdgeBug").x / 2) + 1, (Globals::screenSizeY / 2) + 31), ImColor(0, 0, 0, 255), "EdgeBug");
        Globals::drawList->AddText(ImVec2((Globals::screenSizeX / 2) - (ImGui::CalcTextSize("EdgeBug").x / 2), (Globals::screenSizeY / 2) + 30), ImColor(255, 255, 255, 255), "EdgeBug");

        Vector edgebugPos2D;
        if (worldToScreen(edgebugPos, edgebugPos2D)) {
            Globals::drawList->AddText(ImVec2(edgebugPos2D.x - (ImGui::CalcTextSize("gaming").x / 2) + 1, edgebugPos2D.y + 1), ImColor(0, 0, 0, 255), "gaming");
            Globals::drawList->AddText(ImVec2(edgebugPos2D.x - (ImGui::CalcTextSize("gaming").x / 2), edgebugPos2D.y), ImColor(255, 255, 255, 255), "gaming");
        }
    }
}