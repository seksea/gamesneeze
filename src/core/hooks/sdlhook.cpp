#include "../../includes.hpp"

template <typename T>
static constexpr auto relativeToAbsolute(std::uintptr_t address) noexcept
{
    return (T)(address + 4 + *reinterpret_cast<std::int32_t*>(address));
}

int Hooks::PollEvent(SDL_Event* event) {
    const auto result = pollEvent(event);
    if (Menu::initialised) {
        Menu::onPollEvent(event, result);
    }
    return result;
    return 1;
}

void Hooks::SwapWindow(SDL_Window* window) {
    Menu::onSwapWindow(window);
    swapWindow(window);
}

/* Initialise SDL hooks */
bool Hooks::initSDL() {
    Log::log(" initialising SDL Hooks...");
    const auto libSDL = dlopen("libSDL2-2.0.so.0", RTLD_LAZY | RTLD_NOLOAD);

    swapWindowAddr = relativeToAbsolute<uintptr_t>(uintptr_t(dlsym(libSDL, "SDL_GL_SwapWindow")) + 3);
    if (swapWindowAddr) {
        swapWindow = *reinterpret_cast<decltype(swapWindow)*>(swapWindowAddr);
        *reinterpret_cast<decltype(SwapWindow)**>(swapWindowAddr) = SwapWindow;
    }
    else {
        Log::err("Failed to initialise SwapWindow hook!");
        return false;
    }

    Log::log(std::string("  swapwindow      | ") + std::to_string(swapWindowAddr));

    pollEventAddr = relativeToAbsolute<uintptr_t>(uintptr_t(dlsym(libSDL, "SDL_PollEvent")) + 3);
    if (pollEventAddr) {
        pollEvent = *reinterpret_cast<decltype(pollEvent)*>(pollEventAddr);
        *reinterpret_cast<decltype(PollEvent)**>(pollEventAddr) = PollEvent;
    }
    else {
        Log::err("Failed to initialise PollEvent hook!");
        return false;
    }

    Log::log(std::string("  pollevent       | ") + std::to_string(pollEventAddr));
    Log::log(" initialised SDL Hooks!");
    return true;
}

/* Unload SDL hooks */
bool Hooks::unloadSDL() {
    Log::log("unloading OpenGL Hooks...");
    *reinterpret_cast<decltype(swapWindow)*>(swapWindowAddr) = swapWindow;
    *reinterpret_cast<decltype(pollEvent)*>(pollEventAddr) = pollEvent;
    if (*reinterpret_cast<decltype(swapWindow)*>(swapWindowAddr)!=swapWindow || *reinterpret_cast<decltype(pollEvent)*>(pollEventAddr)!=pollEvent) {
        Log::err("Failed to unload SDL hooks!");
        return false;
    }
    return true;
}