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

            InterfaceReg* cur;
            for (cur = interfaceReg; cur; cur = cur->m_pNext) {
                Log::log(cur->m_pName);
            }
        }
        Log::err(std::string("Failed to find interface ") + name + " -> " + file);
        dlclose(lib);
        return nullptr;
    }
}