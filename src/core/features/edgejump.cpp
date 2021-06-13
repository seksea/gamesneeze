#include "../../includes.hpp"
#include "features.hpp"

void Features::EdgeJump::prePredCreateMove(CUserCmd* cmd) {
    if (Globals::localPlayer)
        flagsBackup = Globals::localPlayer->flags();
}

void Features::EdgeJump::postPredCreateMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Edge Jump") &&
            Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Edge Jump Key")) &&
            Globals::localPlayer &&
            Globals::localPlayer->moveType() != MOVETYPE_LADDER &&
            Globals::localPlayer->moveType() != MOVETYPE_NOCLIP &&
            flagsBackup & FL_ONGROUND &&
            !(Globals::localPlayer->flags() & FL_ONGROUND))
        cmd->buttons |= IN_JUMP;
}
