#pragma once

namespace Hooks {
    bool init();
    bool unload();

    void initSDL();
    inline uintptr_t swapWindowAddr;
    inline std::add_pointer_t<void(SDL_Window*)> swapWindow;
    inline uintptr_t pollEventAddr;
    inline std::add_pointer_t<int(SDL_Event*)> pollEvent;
    void SwapWindow(SDL_Window* window);
    int PollEvent(SDL_Event* event);
    void unloadSDL();
}