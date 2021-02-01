#include "../includes.hpp"
#include "interfaces/ibaseclientdll.hpp"
#include "interfaces/interfaces.hpp"
#include <cstdint>
#include <cstring>

uintptr_t getOffset(RecvTable* table, const char* tableName, const char* netvarName) {
    for (int i = 0; i < table->m_nProps; i++) {
        RecvProp prop = table->m_pProps[i];

        if (!strcmp(prop.m_pVarName, netvarName)) {
            return prop.m_Offset;
        }

        if (prop.m_pDataTable) {
            uintptr_t offset = getOffset(prop.m_pDataTable, tableName, netvarName);

            if (offset) {
                return offset + prop.m_Offset;
            }
        }
    }
    return 0;
}

uintptr_t getNetvarOffset(const char* tableName, const char* netvarName) {
    for (ClientClass* cur = Interfaces::client->GetAllClasses(); cur; cur = cur->m_pNext) {
        if (!strcmp(tableName, cur->m_pRecvTable->m_pNetTableName)) {
            return getOffset(cur->m_pRecvTable, tableName, netvarName);
        }
    }
    return 0;
}

bool Netvar::init() {
    Log::log(LOG, "Initialising Netvars...");
    for (auto& nvar: offsets) {
        nvar.second = getNetvarOffset(nvar.first.first.data(), nvar.first.second.data());
        Log::log(LOG, " %s %s | %x", nvar.first.first.data(), nvar.first.second.data(), nvar.second);
    }

    Log::log(LOG, "Testing offsets by getting m_iHealth from DT_BasePlayer (%x)", GETNETVAROFFSET("DT_BasePlayer", "m_iHealth"));
    if (GETNETVAROFFSET("DT_BasePlayer", "m_iHealth") != 0x138) {
        Log::log(WARN, "When getting m_iHealth from DT_BasePlayer the value isnt as expected, this could mean there is a problem in getting netvars or the game has just updated.");
    }
    return true;
}