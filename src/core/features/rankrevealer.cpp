#include "features.hpp"

void Features::RankReveal::createMove() {
    if (CONFIGBOOL("Misc>Misc>Rank Revealer")) {
        Interfaces::client->DispatchUserMessage(50, 0, 0, nullptr);
    }
}