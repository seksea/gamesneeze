#include "features.hpp"

void Features::ClantagChanger::frameStageNotify(FrameStage frame) {
    if (CONFIGBOOL("Misc>Misc>Clantag")) {
        if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END) {
            if (CONFIGBOOL("Misc>Misc>Clantag>Marquee")) {
                if(Interfaces::globals->tickcount % 64 == 0) {
                    TextManipulation::marquee((Menu::clantag), strlen(Menu::clantag));
                    Offsets::sendClantag(Menu::clantag, "gamesneeze beste\xe2\x80\xa8\xe2\x80\xa8\xe2\x80\xa8");
                }
            } else {
                switch (Interfaces::globals->tickcount % 10) {
                    case 0:
                        Offsets::sendClantag(Menu::clantag, "gamesneeze beste\xe2\x80\xa8\xe2\x80\xa8\xe2\x80\xa8");
                        break;
                    case 8:
                        Offsets::sendClantag(Menu::clantag, "ghub/seksea/gamesneeze\xe2\x80\xa8\xe2\x80\xa8\xe2\x80\xa8");
                        break;
                }
            }
        }
    }
}