#pragma once
#include "interfaces/ibaseclientdll.hpp"

namespace Netvar {
    uintptr_t getOffset(RecvTable* table, const char* tableName, const char* netvarName);
    uintptr_t getNetvarOffset(const char* tableName, const char* netvarName);
}

#define NETVAR( table, prop, func, type ) type& func() {static uintptr_t offset = Netvar::getNetvarOffset(table, prop); return *reinterpret_cast<type*>(uintptr_t(this) + offset);}