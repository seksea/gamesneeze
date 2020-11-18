#pragma once
#include <dlfcn.h>

namespace Interfaces {
    bool init();
    bool unload();


    

    typedef void* (*InstantiateInterfaceFn)();
    // https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/public/tier1/interface.h#L72
    class InterfaceReg {
    public:
        InstantiateInterfaceFn m_CreateFn;
        const char* m_pName;
        InterfaceReg* m_pNext;
    };

    template <typename T>
    T* getInterface(const char* file, const char* name) {
	    void* lib = dlopen(file, RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL);
        if (lib) {
            InterfaceReg* interfaceReg = *reinterpret_cast<InterfaceReg**>(dlsym(lib, "s_pInterfaceRegs"));
            dlclose(lib);

            // loop through interfaceReg
            for (InterfaceReg* cur = interfaceReg; cur; cur = cur->m_pNext) {
                // If current interface equals input name without the 3 version numbers so if an interface version changes we dont have to care
                if (strstr(cur->m_pName, name) && strlen(cur->m_pName)-3 == strlen(name)) {
                    Log::log(std::string("Found interface ") + name + " (" + cur->m_pName + ")");
                    return reinterpret_cast<T*>(cur->m_CreateFn());
                }
            }
        }
        Log::err(std::string("Failed to find interface ") + name + " -> " + file);
        dlclose(lib);
        return nullptr;
    }
}