#include "features.hpp"

void shiftMarquee(char* text, int size) {
    char temp;
    for (int i = 0; i < (size - 1); i++) {
        temp = text[size - 1];
        text[size - 1] = text[i];
        text[i] = temp;
    }
}

void Features::ClantagChanger::frameStageNotify(FrameStage frame) {
    if (CONFIGBOOL("Misc>Misc>Clantag")) {
        if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END) {
            if (CONFIGBOOL("Misc>Misc>Clantag Marquee")) {
                if(Interfaces::globals->tickcount % 64 == 0) {
                    shiftMarquee((Menu::clantag), strlen(Menu::clantag));
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