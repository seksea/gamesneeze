#pragma once
#include <cstdint>
#include "../../utils/utils.hpp"

// https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/mp/src/public/vgui/IPanel.h#L37
class IPanel {
public:
	void SetKeyBoardInputEnabled(unsigned int vguiPanel, bool state) {
		typedef void (*Fn)(void*, unsigned int, bool state);
		return getVirtualFunc<Fn>(this, 32)(this, vguiPanel, state);
	}

	void SetMouseInputEnabled(unsigned int vguiPanel, bool state) {
		typedef void (*Fn)(void*, unsigned int, bool state);
		return getVirtualFunc<Fn>(this, 33)(this, vguiPanel, state);
	}

	const char* GetName(unsigned int vguiPanel) {
		typedef const char* (*Fn)(void*, unsigned int);
		return getVirtualFunc<Fn>(this, 37)(this, vguiPanel);
	}
};