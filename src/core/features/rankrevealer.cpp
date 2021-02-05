#include "features.hpp"
#include "../../sdk/sdk.hpp"
 
void Features::RankReveal::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Rank Revealer")) {
        if (cmd->tick_count % 64 == 0 && !(cmd->buttons & (1 << 16))) { // IN_SCORE
            Interfaces::client->DispatchUserMessage(50, 0, 0, nullptr);
        }
    }
}