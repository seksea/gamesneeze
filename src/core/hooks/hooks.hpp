#pragma once

namespace Hooks {
    bool init();
    bool unload();

    /* VMT HOOKS */
    namespace CreateMove {
        using func = bool(*)(void* , float, CUserCmd*);
        inline func original;
        bool hook(void* thisptr, float flInputSampleTime, CUserCmd* cmd);
    }
    namespace PaintTraverse {
        using func = void(*)(void* thisptr, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
        inline func original;
        void hook(void* thisptr, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
    }

    /* SDL HOOKS */
    bool initSDL();
    inline uintptr_t swapWindowAddr;
    inline std::add_pointer_t<void(SDL_Window*)> swapWindow;
    inline uintptr_t pollEventAddr;
    inline std::add_pointer_t<int(SDL_Event*)> pollEvent;
    void SwapWindow(SDL_Window* window);
    int PollEvent(SDL_Event* event);
    bool unloadSDL();
}