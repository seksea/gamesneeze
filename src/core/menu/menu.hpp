#pragma once
#include "../../includes.hpp"
#include "imgui/imgui.h"
#include <cstdint>
#include <filesystem>
#include <string>

namespace Menu {
    inline bool open = true;
    inline bool initialised = false;
    inline int tabSelected = 0;

    inline bool devWindow = false;
    inline bool demoWindow = false;


    inline char clantag[128] = "gamesneeze";
    void drawMenu();
    void drawLegitTab();
    void drawRageTab();
    void drawVisualsTab();
    void drawMiscTab();
    void drawDevWindow();
    void drawOverlay(ImDrawList* drawList);
    void onPollEvent(SDL_Event* event, const int result);
    void onSwapWindow(SDL_Window* window);
    
    namespace CustomWidgets {
        void drawKeyBinder(const char* label, int* key, bool* toggled);
        bool isKeyDown(int key);
    }
}