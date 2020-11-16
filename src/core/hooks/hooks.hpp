#pragma once

namespace Hooks {
    bool init();
    bool unload();

    void initSDL();
    inline uintptr_t swapWindowAddr;
    inline std::add_pointer_t<void(SDL_Window*)> swapWindow;
    void SwapWindow(SDL_Window* window);
    void unloadSDL();
}