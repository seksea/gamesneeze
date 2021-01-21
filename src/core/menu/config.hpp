#pragma once
#include <unordered_map>
#include "imgui/imgui.h"

#define CONFIGINT(name) Config::config.at(name).intValue
#define CONFIGBOOL(name) Config::config.at(name).boolValue
#define CONFIGSTR(name) Config::config.at(name).strValue
#define CONFIGCOL(name) Config::config.at(name).colValue

#define CONFIGITEM(name, value) {name, ConfigItem(value)}

namespace Config {
    inline void save(char* name) {
        
    }
    inline void load(char* name) {
        
    }

    class ConfigItem {
        public:
        ConfigItem(int value) {
            intValue = value;
        }
        ConfigItem(bool value) {
            boolValue = value;
        }
        ConfigItem(char* value) {
            strValue = value;
        }
        ConfigItem(ImColor value) {
            colValue = value;
        }
        int intValue = -1;
        bool boolValue = false;
        char* strValue;
        ImColor colValue = ImColor(255, 255, 255, 255);
    };

    inline std::unordered_map<const char*, ConfigItem> config {
        CONFIGITEM("Enemy:Box", false),
        CONFIGITEM("Enemy:BoxColor", ImColor(197, 66, 245, 255)),
        CONFIGITEM("Enemy:Name", false),
        CONFIGITEM("Enemy:Health", false),
        CONFIGITEM("Enemy:HealthBar", false),
        CONFIGITEM("Enemy:Money", false),
        CONFIGITEM("Team:Box", false),
        CONFIGITEM("Team:BoxColor", ImColor(10, 161, 32, 255)),
        CONFIGITEM("Team:Name", false),
        CONFIGITEM("Team:Health", false),
        CONFIGITEM("Team:HealthBar", false),
        CONFIGITEM("Team:Money", false)
    };
}