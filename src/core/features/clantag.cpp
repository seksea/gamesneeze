#include "features.hpp"

void Features::ClantagChanger::frameStageNotify(FrameStage frame) {
    if (CONFIGBOOL("Misc:Clantag")) {
        if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END) {
            switch (Interfaces::globals->tickcount % 10) {
                case 0: Offsets::sendClantag(Menu::clantag, "gamesneeze beste\xe2\x80\xa8\xe2\x80\xa8\xe2\x80\xa8"); break;
                case 6: Offsets::sendClantag(Menu::clantag, "ghub/seksea/gamesneeze\xe2\x80\xa8\xe2\x80\xa8\xe2\x80\xa8"); break;
            }
        }
    }
}