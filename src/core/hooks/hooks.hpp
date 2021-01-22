#pragma once
#include "../../includes.hpp"

namespace Hooks {
    bool init();
    bool unload();

    /* VMT HOOKS */
    namespace CreateMove {
        using func = bool(*)(void* thisptr, float flInputSampleTime, CUserCmd* cmd);
        inline func original;
        bool hook(void* thisptr, float flInputSampleTime, CUserCmd* cmd);
    }
    namespace PaintTraverse {
        using func = void(*)(void* thisptr, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
        inline func original;
        void hook(void* thisptr, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
    }
    namespace Paint {
        using func = void(*)(void* thisptr, PaintMode_t mode);
        inline func original;
        void hook(void* thisptr, PaintMode_t mode);
    }
    namespace DrawModelExecute {
        using func = void(*)(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
        inline func original;
        void hook(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);

    }

    /* SDL HOOKS */
    namespace SDL {
        bool initSDL();
        inline uintptr_t swapWindowAddr;
        inline std::add_pointer_t<void(SDL_Window*)> swapWindow;
        inline uintptr_t pollEventAddr;
        inline std::add_pointer_t<int(SDL_Event*)> pollEvent;
        void SwapWindow(SDL_Window* window);
        int PollEvent(SDL_Event* event);
        bool unloadSDL();
    }
}