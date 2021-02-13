#include "features.hpp"

void Features::AutoAccept::emitSound(const char* pSoundEntry) {
    /* TODO: move to panorama event dispatching in future */
    if (CONFIGBOOL("Misc>Misc>Misc>Auto Accept") && Offsets::setPlayerReady) {
        if (strcmp(pSoundEntry, "UIPanorama.popup_accept_match_beep") == 0) {
            Log::log(LOG, "Found a game, accepting...");
            Offsets::setPlayerReady("");
        }
    }
}