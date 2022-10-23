#pragma once
#include <cstdint>
#include <cstring>
#include <dlfcn.h>
#include <string>

#include "ibaseclientdll.hpp"
#include "ivengineclient.hpp"
#include "ipanel.hpp"
#include "icliententitylist.hpp"
#include "ienginevgui.hpp"
#include "ivmodelrender.hpp"
#include "imaterialsystem.hpp" // Also contains IMaterial
#include "ivmodelinfo.hpp"
#include "ienginesound.hpp"
#include "ienginetrace.hpp"
#include "iprediction.hpp"
#include "input.hpp"
#include "igameevent.hpp"
#include "playerResource.hpp"
#include "icvar.hpp"

#include "iclientmode.hpp"
#include "globalvars.hpp"
#include "iviewrenderbeams.hpp"

#define playerResource ((*Interfaces::_playerResource)) // its annoying to dereference every time

namespace Interfaces {
    bool init();
    bool unload();

    inline IBaseClientDLL* client;
    inline IVEngineClient* engine;
    inline IPanel* panel;
    inline IClientEntityList* entityList;
    inline IEngineVGui* engineVgui;
    inline IVModelRender* modelRender;
    inline IVModelInfo* modelInfo;
    inline IMaterialSystem* materialSystem;
    inline IEngineSound* sound;
    inline IEngineTrace* trace;
    inline IGameMovement* movement;
    inline IMoveHelper* moveHelper;
    inline IPrediction* prediction;
    inline IGameEventManager2* eventManager;
    inline ICvar* convar;

    inline IClientMode* clientMode;
    inline CGlobalVars* globals;
    inline CInput* input;
    inline PlayerResource** _playerResource;
    inline ViewRenderBeams* renderBeams;

    typedef void* (*InstantiateInterfaceFn)();
    // https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/public/tier1/interface.h#L72
    class InterfaceReg {
    public:
        InstantiateInterfaceFn m_CreateFn;
        const char* m_pName;
        InterfaceReg* m_pNext;
    };
    template <typename T>
    T* getInterface(const char* file, const char* name, bool includeVersion = false) {
	    void* lib = dlopen(file, RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL);
        if (lib) {
            // https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/tier1/interface.cpp#L46
            InterfaceReg* interfaceReg = *reinterpret_cast<InterfaceReg**>(dlsym(lib, "s_pInterfaceRegs"));
            dlclose(lib);

            // loop through each interface in interfaceReg linked list
            for (InterfaceReg* cur = interfaceReg; cur; cur = cur->m_pNext) {
                // If current interface equals input name without the 3 version numbers so if an interface version changes we dont have to care
                if ((strstr(cur->m_pName, name) && strlen(cur->m_pName)-3 == strlen(name)) || 
                    (includeVersion && (strstr(cur->m_pName, name) && strlen(cur->m_pName) == strlen(name)))) {
                    T* iface = reinterpret_cast<T*>(cur->m_CreateFn());
                    Log::log(LOG, " %s (%s) %lx", name, cur->m_pName, (uintptr_t)iface);
                    return iface;
                }
            }
        }
        Log::log(ERR, " Failed to find interface %s in %s", name, file);
        dlclose(lib);
        return nullptr;
    }
}