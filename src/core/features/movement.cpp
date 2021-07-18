#include "../../includes.hpp"
#include "features.hpp"

int flagsBackup = 0;
Vector velBackup;
int buttBackup;
QAngle viewBackup;
Vector2D moveBackup;
bool allowBhop = true;
bool shouldEdgebug;

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
            flagsBackup & FL_ONGROUND &&
            !(Globals::localPlayer->flags() & FL_ONGROUND))
        cmd->buttons |= IN_JUMP;
}

void jumpBug(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>JumpBug") &&
            Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>JumpBug Key")) &&
            !(flagsBackup & FL_ONGROUND || flagsBackup & FL_PARTIALGROUND) &&
            (Globals::localPlayer->flags() & FL_ONGROUND || Globals::localPlayer->flags() & FL_PARTIALGROUND)) {
        cmd->buttons |= IN_DUCK;
        cmd->buttons &= ~IN_JUMP;
        allowBhop = false;
    }
    else {
        allowBhop = true;
    }
}

bool checkEdgebug(){ // need to find/get a better edgebug detection method, unsure if this will work on 128tick
    return !(velBackup.z >= -7 || 
            floor(Globals::localPlayer->velocity().z) != -7 || 
            (Globals::localPlayer->flags() & FL_ONGROUND)) && 
            Globals::localPlayer->velocity().Length2D() >= velBackup.Length2D();
}

void edgeBugEnforcer(CUserCmd* cmd) {
    if (!CONFIGBOOL("Misc>Misc>Movement>EdgeBug") ||
            !Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>EdgeBug Key")))
        return;

    if (shouldEdgebug) {
        cmd->buttons = buttBackup;
        cmd->viewangles = viewBackup; // kinda need to block mouse input properly, but this is ok for now
        cmd->sidemove = moveBackup.x;
        cmd->forwardmove = moveBackup.y;
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
    int predictAmount = 32; // TODO: make amount configurable
    for (int i = 0; i < predictAmount; i++) { // this is roughly the famous 'clarity' edgebug (lol)
        if (shouldEdgebug)
            break;
        Features::Prediction::start(cmd);
        shouldEdgebug = checkEdgebug();
        Features::Prediction::end();
    }
}