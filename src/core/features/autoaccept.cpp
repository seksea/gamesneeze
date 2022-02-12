#include "features.hpp"

void Features::AutoAccept::emitSound(const char* pSoundEntry) {
    /* TODO: move to panorama event dispatching in future */
    if (CONFIGBOOL("Misc>Misc>Misc>Auto Accept") && Offsets::setPlayerReady && strcmp(pSoundEntry, "UIPanorama.popup_accept_match_beep") == 0) {
        Features::Notifications::addNotification(ImColor(30, 255, 30), "[gs] Found game, Accepting...");
        int status = system("notify-send \"gamesneeze\" \"Found game!\""); //p
        if(status != 0)
        	Features::Notifications::addNotification(ImColor(255, 0, 0), "[gs] system() failed. Return value: %d", status);
        Offsets::setPlayerReady("");
    }
}
