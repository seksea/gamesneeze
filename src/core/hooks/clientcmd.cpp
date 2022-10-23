#include "../../includes.hpp"
#include "hooks.hpp"
#include <SDL2/SDL_scancode.h>
#include <algorithm>
#include <cstring>
#include <streambuf>
#include <string>
#include <string_view>

void Hooks::ClientCmd::hook(void* thisptr, char* szCmdString) {
    if (strstr(szCmdString, "say ") && CONFIGBOOL("Misc>Misc>Misc>Chat Filter Bypass")) {
        // https://www.unknowncheats.me/forum/counterstrike-global-offensive/439677-bypass-chat-swear-filter.html
        std::reverse(szCmdString+5, szCmdString + strlen(szCmdString)-1);
        memmove(szCmdString+7, szCmdString+5, strlen(szCmdString)-6);
        szCmdString[4] = '\xE2';
        szCmdString[5] = '\x80';
        szCmdString[6] = '\xAE';
    }

    original(thisptr, szCmdString);
}