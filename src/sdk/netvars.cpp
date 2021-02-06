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

    Log::log(LOG, "Testing netvars by getting m_iHealth from DT_BasePlayer (%x)", GETNETVAROFFSET("DT_BasePlayer", "m_iHealth"));
    if (GETNETVAROFFSET("DT_BasePlayer", "m_iHealth") != 0x138) {
        Log::log(WARN, "When getting m_iHealth from DT_BasePlayer the value isnt as expected, this could mean there is a problem in getting netvars or the game has just updated.");
    }

    Log::log(LOG, "Initialising offsets");

    Offsets::sendClantag = (Offsets::SendClantag)PatternScan::patternScan("engine_client.so", 
        (unsigned char*)    "\x55\x48\x89\xE5\x41\x55\x49\x89\xFD\x41\x54\xBF\x48\x00\x00\x00\x49\x89\xF4\x53\x48\x83\xEC\x08\xE8"
                            "\x00\x00\x00\x00"
                            "\x48\x8D\x35"
                            "\x00\x00\x00\x00"
                            "\x48\x89\xC7\x48\x89\xC3\xE8"
                            "\x00\x00\x00\x00"
                            "\x48\x8D\x35"
                            "\x00\x00\x00\x00"
                            "\x4C\x89\xEA", 
                            "xxxxxxxxxxxxxxxxxxxxxxxxx"
                            "????"
                            "xxx"
                            "????"
                            "xxxxxxx"
                            "????"
                            "xxx"
                            "????"
                            "xxx");
    Log::log(LOG, " sendClantag | %x", Offsets::sendClantag);

    Offsets::setPlayerReady = (Offsets::SetPlayerReady)PatternScan::patternScan("/client_client.so",
		(unsigned char*)    "\x55\x48\x89\xF7\x48\x8D\x35\x00\x00\x00\x00\x48\x89\xE5\xE8\x00\x00\x00\x00\x85\xC0",
							"xxxxxxx????xxxx????xx");
    Log::log(LOG, " setPlayerReady | %x", Offsets::setPlayerReady);

    return true;
}