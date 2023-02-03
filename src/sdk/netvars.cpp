#include "../includes.hpp"
#include "interfaces/ibaseclientdll.hpp"
#include "interfaces/interfaces.hpp"
#include "netvars.hpp"
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
        Log::log(LOG, " %s %s | %lx", nvar.first.first.data(), nvar.first.second.data(), nvar.second);
    }

    Log::log(LOG, "Testing netvars by getting m_iHealth from DT_BasePlayer (%lx)", GETNETVAROFFSET("DT_BasePlayer", "m_iHealth"));
    if (GETNETVAROFFSET("DT_BasePlayer", "m_iHealth") != 0x138) {
        Log::log(WARN, "When getting m_iHealth from DT_BasePlayer the value isnt as expected, this could mean there is a problem in getting netvars or the game has just updated.");
    }

    Log::log(LOG, "Initialising offsets");

    // xref: "ClanTagChanged"
    Offsets::sendClantag = (Offsets::SendClantag)PatternScan::findFirstInModule("engine_client.so",
            "55 48 89 E5 41 55 49 89 FD BF ? ? ? ? 41 54 49 89 F4 53 48 83 EC 08 E8 ? ? ? ? 31 C9");
    Log::log(LOG, " sendClantag | %lx", Offsets::sendClantag);

    Offsets::setPlayerReady = (Offsets::SetPlayerReady)PatternScan::findFirstInModule("/client_client.so",
            "55 48 89 F7 48 8D 35 ? ? ? ? 48 89 E5 E8 ? ? ? ? 85 C0");
    Log::log(LOG, " setPlayerReady | %lx", Offsets::setPlayerReady);

    /**
     * Find a sub with "mp_radar_showall" lea'd into rsi.
     * The find a test al, al; jz there. You want the test insn.
     * lea     rax, qword_6D1D528
     * mov     rbx, [rax]
     * test    rbx, rbx
     * jz      short loc_105C560
     * lea     rax, qword_2373E10
     * mov     rdi, [rax]
     * mov     rax, [rdi]
     * call    qword ptr [rax+2E8h]
     * test    al, al // <--- This insn
     * jz      short loc_105C530 
     */
    Offsets::radarIsHltvCheck = PatternScan::findFirstInModule("/client_client.so", "48 8D 05 ? ? ? ? 48 8B 38 48 8B 07 FF 90 E8 02 00 00 84 C0 74");
    Log::log(LOG, " radarIsHltvCheck | %lx", Offsets::radarIsHltvCheck);

    Offsets::initKeyValues = (Offsets::InitKeyValues)PatternScan::findFirstInModule("/client_client.so",
            "81 27 00 00 00 FF 55 31 C0 48 89 E5 5D");
    Log::log(LOG, " initKeyValues | %lx", Offsets::initKeyValues);

    // xref: _MemFreeScratch, the first call above it is to the sub we want
    Offsets::loadFromBuffer = (Offsets::LoadFromBuffer)PatternScan::findFirstInModule("/client_client.so", 
            "55 48 89 E5 41 57 41 56 41 55 41 54 53 48 81 EC ? ? ? ? 48 85 D2"),
    Log::log(LOG, " loadFromBuffer | %lx", Offsets::loadFromBuffer);

    Offsets::setNamedSkybox = (Offsets::SetNamedSkybox)PatternScan::findFirstInModule("engine_client.so", 
            "55 4C 8D 05 ? ? ? ? 48 89 E5 41");
    Log::log(LOG, " setNamedSkybox | %lx", Offsets::setNamedSkybox);

    Offsets::lineGoesThroughSmoke = (Offsets::LineGoesThroughSmoke)PatternScan::findFirstInModule("/client_client.so", 
            "55 48 89 E5 41 56 41 55 41 54 53 48 83 EC 30 8B 05 ? ? ? ? 66");
    Log::log(LOG, " lineGoesThroughSmoke | %lx", Offsets::lineGoesThroughSmoke);

    // xref: "CPrediction::ProcessMovement", go up by 2 jmps, find the bottommost lea rcx, off_*
    Offsets::moveData = *reinterpret_cast<CMoveData**>(getAbsoluteAddress(PatternScan::findFirstInModule("/client_client.so", 
            "48 8D 0D ? ? ? ? 4C 8B 01"), 3, 7));
    Log::log(LOG, " moveData | %lx", Offsets::moveData);

    Interfaces::moveHelper = *reinterpret_cast<IMoveHelper **>(getAbsoluteAddress(PatternScan::findFirstInModule("/client_client.so", 
            "00 48 89 3D ? ? ? ? C3") + 1, 3, 7));
    Log::log(LOG, " moveHelper | %lx", Interfaces::moveHelper);

    // xref: _RandomSeed, not in a sub, three calls to _RandomFloat under it
    // find whatever is lea'd into rax above the _RandomSeed call 
    Offsets::predictionSeed = reinterpret_cast<int*>(getAbsoluteAddress(PatternScan::findFirstInModule("/client_client.so", 
            "48 8D 05 ? ? ? ? 8B 38 E8 ? ? ? ? 89 C7"), 3, 7));
    Log::log(LOG, " predictionSeed | %lx", Offsets::predictionSeed);

	Offsets::animState = *reinterpret_cast<unsigned int*>(PatternScan::findFirstInModule("/client_client.so",
			"48 8B BB ? ? ? ? 48 85 FF 74 3E E8") + 3);
    Log::log(LOG, " animState | %lx", Offsets::animState);

	uintptr_t GetLocalPlayer = reinterpret_cast<uintptr_t>(getVTable(Interfaces::engine)[12]);
	Offsets::getLocalClient = reinterpret_cast<Offsets::GetLocalClient>(getAbsoluteAddress(GetLocalPlayer + 9, 1, 5));
    Log::log(LOG, " getLocalClient | %lx", Offsets::getLocalClient);

    // xref: "C_BaseEntity::SaveData", go up to the start of the sub
    Offsets::saveData = (Offsets::SaveData)PatternScan::findFirstInModule("/client_client.so",
        "55 48 89 E5 41 57 41 89 CF 41 56 41 55 41 54 41 89 D4 53 48 89 FB 48 83 EC");
    Log::log(LOG, " saveData | %lx", Offsets::saveData);

    // xref: "PreEntityPacketReceived(no commands ack)", go down to the next (and only) jmp,
    // that jump is to the sub we want
    Offsets::restoreData = (Offsets::RestoreData)(PatternScan::findFirstInModule("/client_client.so",
        "BA FF FF FF FF 48 8D 35 ? ? ? ? E9") + 13);
    Log::log(LOG, " restoreData | %lx", Offsets::restoreData);

    Offsets::onPostRestoreData = (Offsets::OnPostRestoreData)PatternScan::findFirstInModule("/client_client.so",
        "55 BE ? ? ? ? 48 89 E5 41 54 53 48 89 FB E8");
    Log::log(LOG, " onPostRestoreData | %lx", Offsets::onPostRestoreData);

    // xref: "CPrediction::RestoreEntityToPredictedFrame", go up to the start of the sub
    Offsets::restoreEntityToPredictedFrame = (Offsets::RestoreEntityToPredictedFrame)PatternScan::findFirstInModule("/client_client.so",
        "55 48 89 E5 41 57 41 56 41 55 41 89 F5 41 54 53 48 83 EC 18 48 8B 05 ? ? ? ? 89 55 CC 44 8B B8 ? ? ? ? 45 85 FF 0F 85 ? ? ? ? 44 89 EF");
    Log::log(LOG, " restoreEntityToPredictedFrame | %lx", Offsets::restoreEntityToPredictedFrame);

    return true;
}
