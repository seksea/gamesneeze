#pragma once

#include <iostream>
#include <thread>
#include <string>
#include <dlfcn.h>
#include <SDL2/SDL.h>
#include <cstdint>

#include "core/menu/imgui/imgui.h"
#include "core/menu/imgui/GL/gl3w.h"
#include "core/menu/imgui/imgui_impl_sdl.h"
#include "core/menu/imgui/imgui_impl_opengl3.h"

#include "core/menu/config.hpp"
#include "utils/utils.hpp"
#include "sdk/sdk.hpp"
#include "core/features/features.hpp"
#include "core/hooks/hooks.hpp"
#include "core/menu/menu.hpp"

namespace Globals {
    inline VMatrix worldToScreenMatrix;
    inline int screenSizeX;
    inline int screenSizeY;
    inline ImDrawList* drawList;
    inline bool* sendPacket;
    inline float FOV;

    inline Player* localPlayer;
}
