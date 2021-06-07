#include "../../includes.hpp"
#include "features.hpp"

int flagsBackup = 0;

void Features::EdgeJump::prePredCreateMove(CUserCmd* cmd) {
    if (!CONFIGBOOL("Misc>Misc>Movement>Edge Jump"))
        return;

    if (!Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Edge Jump Key")))
        return;

    if (!Globals::localPlayer)
        return;

    if (Globals::localPlayer->moveType() == MOVETYPE_LADDER)
        return;

    if (Globals::localPlayer->moveType() == MOVETYPE_NOCLIP)
        return;

    flagsBackup = Globals::localPlayer->flags();
}

void Features::EdgeJump::postPredCreateMove(CUserCmd* cmd) {
    if (!CONFIGBOOL("Misc>Misc>Movement>Edge Jump"))
        return;

    if (!Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Edge Jump Key")))
        return;

    if (!Globals::localPlayer)
        return;

    if (Globals::localPlayer->moveType() == MOVETYPE_LADDER)
        return;

    if (Globals::localPlayer->moveType() == MOVETYPE_NOCLIP)
        return;

    if (flagsBackup & FL_ONGROUND && !(Globals::localPlayer->flags() & FL_ONGROUND))
        cmd->buttons |= IN_JUMP;
}
