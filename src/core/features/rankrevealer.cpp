#include "features.hpp"

void Features::RankReveal::rankReveal() {
    if (CONFIGBOOL("Misc:RankReveal")) {
        Interfaces::client->DispatchUserMessage(50, 0, 0, nullptr);
    }
}