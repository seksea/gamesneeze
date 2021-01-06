#pragma once
#include "interfaces/ibaseclientdll.hpp"

namespace Netvar {
    uintptr_t getOffset(RecvTable* table, const char* tableName, const char* netvarName);
    uintptr_t getNetvarOffset(const char* tableName, const char* netvarName);
}