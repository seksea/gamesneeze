#include <cstdint>

class IClientEntityList {
public:
    // NOTE: This function is only a convenience wrapper.
    // It returns GetClientNetworkable( entnum )->GetIClientEntity().   
	uintptr_t GetClientEntity(int entnum) {
		typedef uintptr_t (*Fn)(void*, int);
		return getVirtualFunc<Fn>(this, 3)(this, entnum);
	}
	void* GetClientEntityFromHandle(void* handle) {
		typedef void* (*Fn)(void*, void*);
		return getVirtualFunc<Fn>(this, 4)(this, handle);
	}
	int GetHighestEntityIndex() {
		typedef int (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 6)(this);
	}
};