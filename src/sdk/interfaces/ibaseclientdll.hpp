#pragma once
#include <cstdint>
#include "../definitions.hpp"

struct RecvProp;

struct RecvTable{
	RecvProp *m_pProps;
	int m_nProps;
	void *m_pDecoder;
	char *m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

class IClientNetworkable;
typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();

class ClientClass {
public:
	CreateClientClassFn m_pCreateFn;
	CreateEventFn *m_pCreateEventFn;
	char* m_pNetworkName;
	RecvTable *m_pRecvTable;
	ClientClass* m_pNext;
	EClassIds m_ClassID;
};

// https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/public/cdll_int.h#L577
class IBaseClientDLL {
public:
	// Request a pointer to the list of client datatable classes
    ClientClass* GetAllClasses() {
		typedef ClientClass* (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 8)(this);
	}

	// The engine has received the specified user message, this code is used to dispatch the message handler
    bool DispatchUserMessage(int msg_type, int a, int b, void* msg_data) {
		
		typedef bool (*Fn)(void*, int, int, int, void*);
		return getVirtualFunc<Fn>(this, 38)(this, msg_type, a, b, msg_data);
	}
};