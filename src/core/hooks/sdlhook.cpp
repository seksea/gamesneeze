#include "../../includes.hpp"

template <typename T>
static constexpr auto relativeToAbsolute(std::uintptr_t address) noexcept
{
    return (T)(address + 4 + *reinterpret_cast<std::int32_t*>(address));
}

int Hooks::SDL::PollEvent(SDL_Event* event) {
    const auto result = pollEvent(event);
    if (Menu::initialised) {
        Menu::onPollEvent(event, result);
    }
    return result;
    return 1;
}

void Hooks::SDL::SwapWindow(SDL_Window* window) {
    Menu::onSwapWindow(window);
    swapWindow(window);
}

/* Initialise SDL hooks */
bool Hooks::SDL::initSDL() {
    Log::log(LOG, " Hooking SDL Hooks...");
    const auto libSDL = dlopen("libSDL2-2.0.so.0", RTLD_LAZY | RTLD_NOLOAD);

    swapWindowAddr = relativeToAbsolute<uintptr_t>(uintptr_t(dlsym(libSDL, "SDL_GL_SwapWindow")) + 2);
    if (swapWindowAddr) {
        swapWindow = *reinterpret_cast<decltype(swapWindow)*>(swapWindowAddr);
        *reinterpret_cast<decltype(SwapWindow)**>(swapWindowAddr) = SwapWindow;
    }
    else {
        Log::log(ERR, "Failed to initialise SwapWindow hook!");
        return false;
    }

    Log::log(LOG, "  SwapWindow      | %lx", swapWindowAddr);

    pollEventAddr = relativeToAbsolute<uintptr_t>(uintptr_t(dlsym(libSDL, "SDL_PollEvent")) + 2);
    if (pollEventAddr) {
        pollEvent = *reinterpret_cast<decltype(pollEvent)*>(pollEventAddr);
        *reinterpret_cast<decltype(PollEvent)**>(pollEventAddr) = PollEvent;
    }
    else {
        Log::log(ERR, "Failed to initialise PollEvent hook!");
        return false;
    }

    Log::log(LOG, "  PollEvent       | %lx", pollEventAddr);
    Log::log(LOG, " Hooked SDL Hooks!");
    return true;
}

/* Unload SDL hooks */
bool Hooks::SDL::unloadSDL() {
    Log::log(LOG, "Unloading SDL Hooks...");
    *reinterpret_cast<decltype(swapWindow)*>(swapWindowAddr) = swapWindow;
    *reinterpret_cast<decltype(pollEvent)*>(pollEventAddr) = pollEvent;
    if (*reinterpret_cast<decltype(swapWindow)*>(swapWindowAddr)!=swapWindow || *reinterpret_cast<decltype(pollEvent)*>(pollEventAddr)!=pollEvent) {
        Log::log(ERR, "Failed to unload SDL hooks!");
        return false;
    }
    return true;
}