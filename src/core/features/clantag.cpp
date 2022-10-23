#include "beemovie.hpp"
#include "features.hpp"
#include "beemovie.hpp"
#include <cstring>

void shiftMarquee(char* text, int size) {
    char temp;
    for (int i = 0; i < (size - 1); i++) {
        temp = text[size - 1];
        text[size - 1] = text[i];
        text[i] = temp;
    }
}

void updateClantag() {
    if ((TICKCOUNTWITHPING() % 128) > 96) {
        Offsets::sendClantag(Menu::clantag, "ghub/seksea/gamesneeze\xe2\x80\xa8\xe2\x80\xa8\xe2\x80\xa8");
    }
    else {
        Offsets::sendClantag(Menu::clantag, "gamesneeze beste\xe2\x80\xa8\xe2\x80\xa8\xe2\x80\xa8");
    }
}

void Features::ClantagChanger::frameStageNotify(FrameStage frame) {
    if (CONFIGBOOL("Misc>Misc>Clantag>Clantag") && frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END) {
        if (CONFIGBOOL("Misc>Misc>Clantag>Clantag Marquee")) {
            if(TICKCOUNTWITHPING() % 32 == 0) {
                shiftMarquee((Menu::clantag), strlen(Menu::clantag));
                updateClantag();
            }
        }
        else if (CONFIGBOOL("Misc>Misc>Clantag>Bee Movie Clantag")) {
            if(TICKCOUNTWITHPING() % 16 == 0) {
                memcpy(Menu::clantag, &beeMovieScript[(TICKCOUNTWITHPING() % 55000)/16], 127); // mod it by 55k just as a crude way of looping when it gets to the end, doubt anyone will have it on for 300 mins anyways lmao
                Menu::clantag[127] = '\0';
                updateClantag();
            }
        }
        else {
            if(TICKCOUNTWITHPING() % 128 == 0) {
                updateClantag();
            }
        }
    }
}