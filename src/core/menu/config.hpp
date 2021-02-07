#pragma once
#include <unordered_map>
#include <fstream>
#include "imgui/imgui.h"
#include "../../utils/utils.hpp"

#define CONFIGINT(name) Config::config.at(name).intValue
#define CONFIGBOOL(name) Config::config.at(name).boolValue
#define CONFIGSTR(name) Config::config.at(name).strValue
#define CONFIGCOL(name) Config::config.at(name).colValue

#define CONFIGITEM(name, value) {name, ConfigItem(value)}

enum CONFIGITEMTYPE {
    INT,
    BOOL,
    STR,
    COLOR
};

namespace Config {

    class ConfigItem {
        public:
        ConfigItem(int value) {
            type = INT;
            intValue = value;
        }
        ConfigItem(bool value) {
            type = BOOL;
            boolValue = value;
        }
        ConfigItem(char* value) {
            type = STR;
            strValue = value;
        }
        ConfigItem(ImColor value) {
            type = COLOR;
            colValue = value;
        }
        CONFIGITEMTYPE type;
        int intValue = -1;
        bool boolValue = false;
        char* strValue;
        ImColor colValue = ImColor(255, 255, 255, 255);
    };

    inline std::unordered_map<std::string_view, ConfigItem> config {
        // Visuals {
            // ESP {
                CONFIGITEM("Visuals>Enemies>ESP>Box", false),
                CONFIGITEM("Visuals>Enemies>ESP>Box Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Enemies>ESP>Only When Dead", false),
                CONFIGITEM("Visuals>Enemies>ESP>Name", false),
                CONFIGITEM("Visuals>Enemies>ESP>Health", false),
                CONFIGITEM("Visuals>Enemies>ESP>Health Bar", false),
                CONFIGITEM("Visuals>Enemies>ESP>Money", false),
                CONFIGITEM("Visuals>Teammates>ESP>Box", false),
                CONFIGITEM("Visuals>Teammates>ESP>Box Color", ImColor(10, 161, 32, 255)),
                CONFIGITEM("Visuals>Teammates>ESP>Only When Dead", false),
                CONFIGITEM("Visuals>Teammates>ESP>Name", false),
                CONFIGITEM("Visuals>Teammates>ESP>Health", false),
                CONFIGITEM("Visuals>Teammates>ESP>Health Bar", false),
                CONFIGITEM("Visuals>Teammates>ESP>Money", false),
            // }
            // Chams {
                CONFIGITEM("Visuals>Enemies>Chams>Visible Material", 0),
                CONFIGITEM("Visuals>Enemies>Chams>Visible Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Enemies>Chams>Visible Overlay Material", 0),
                CONFIGITEM("Visuals>Enemies>Chams>Visible Overlay Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Enemies>Chams>Occluded Material", 0),
                CONFIGITEM("Visuals>Enemies>Chams>Occluded Color", ImColor(197, 66, 245, 255)),
                
                CONFIGITEM("Visuals>Teammates>Chams>Visible Material", 0),
                CONFIGITEM("Visuals>Teammates>Chams>Visible Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Teammates>Chams>Visible Overlay Material", 0),
                CONFIGITEM("Visuals>Teammates>Chams>Visible Overlay Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Teammates>Chams>Occluded Material", 0),
                CONFIGITEM("Visuals>Teammates>Chams>Occluded Color", ImColor(197, 66, 245, 255)),

                CONFIGITEM("Visuals>World>Local Player>Weapon Material", 0),
                CONFIGITEM("Visuals>World>Local Player>Weapon Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>World>Local Player>Weapon Overlay Material", 0),
                CONFIGITEM("Visuals>World>Local Player>Weapon Overlay Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>World>Local Player>Arms Material", 0),
                CONFIGITEM("Visuals>World>Local Player>Arms Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>World>Local Player>Arms Overlay Material", 0),
                CONFIGITEM("Visuals>World>Local Player>Arms Overlay Color", ImColor(197, 66, 245, 255)),
            // }
            // World {
                CONFIGITEM("Visuals>World>Local Player>Spread Crosshair", false),
                CONFIGITEM("Visuals>World>Local Player>Recoil Crosshair", false),
                CONFIGITEM("Visuals>World>Local Player>Recoil Crosshair>Only When Shooting", false),
                CONFIGITEM("Visuals>World>Local Player>Crosshair Color", ImColor(0, 0, 0, 100)),
                CONFIGITEM("Visuals>World>Local Player>Crosshair Border Color", ImColor(200, 200, 200, 100)),

                CONFIGITEM("Visuals>World>World>World Color Modulation", ImColor(255, 255, 255, 255)),

                CONFIGITEM("Visuals>World>Items>Weapon Box", false),
                CONFIGITEM("Visuals>World>Items>Weapon Box Color", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Visuals>World>Items>Weapon Label", false),

                CONFIGITEM("Visuals>World>Items>Planted C4 Box", false),
                CONFIGITEM("Visuals>World>Items>Planted C4 Box Color", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Visuals>World>Items>Planted C4 Label", false),

                CONFIGITEM("Visuals>World>Items>Chicken Box", false),
                CONFIGITEM("Visuals>World>Items>Chicken Box Color", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Visuals>World>Items>Chicken Label", false),

                CONFIGITEM("Visuals>World>Items>Fish Box", false),
                CONFIGITEM("Visuals>World>Items>Fish Box Color", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Visuals>World>Items>Fish Label", false),

                CONFIGITEM("Visuals>World>Items>ESP Quite literally everything", false),
            // }
        // }
        // Misc {
            CONFIGITEM("Misc>Movement>Auto Hop", false),

            CONFIGITEM("Misc>Misc>Rank Revealer", false),
            CONFIGITEM("Misc>Misc>Clantag", false),
            CONFIGITEM("Misc>Misc>Clantag Marquee", false),
            CONFIGITEM("Misc>Misc>Spectators", false),
            CONFIGITEM("Misc>Misc>Player List", false),
            CONFIGITEM("Misc>Misc>Auto Accept", false),

        // }
    };

    inline void save() {
        std::ofstream configFile;
        configFile.open("gamesneeze.cfg");
        for (auto i : config) {
            switch (i.second.type) {
                case INT: 
                    configFile << i.second.type << "\t"<< i.first << "\t" << i.second.intValue << "\n";
                break;
                case BOOL: 
                    configFile << i.second.type << "\t" << i.first << "\t" << i.second.boolValue << "\n";
                break;
                case STR: 
                    configFile << i.second.type << "\t" << i.first << "\t" << i.second.strValue << "\n";
                break;
                case COLOR: 
                    configFile << i.second.type << "\t" << i.first << "\t" << i.second.colValue.Value.x << "|" << i.second.colValue.Value.y << "|" << i.second.colValue.Value.z << "|" << i.second.colValue.Value.w << "\n";
                break;
            }
        }
        configFile.close();
    }

    inline void load() {
        std::string line;
        std::ifstream configFile;
        configFile.open("gamesneeze.cfg");
        while(std::getline(configFile, line)) {
            CONFIGITEMTYPE type;
            char name[64];
            char value[64];
            sscanf(line.c_str(), "%d\t%[^\t]\t%[^\t]", (int*)&type, name, value);
            try {
                switch (type) {
                    case INT:
                        CONFIGINT(name) = atoi(value);
                    break;
                    case BOOL:
                        CONFIGBOOL(name) = atoi(value);
                    break;
                    case STR:
                        CONFIGSTR(name) = value;
                    break;
                    case COLOR:
                        float r, g, b, a;
                        sscanf(value, "%f|%f|%f|%f", (float*)&r, (float*)&g, (float*)&b, (float*)&a);
                        CONFIGCOL(name) = ImColor(r, g, b, a);
                    break;
                }
            } catch (std::out_of_range& e) {
                Log::log(ERR, "Failed to load config item %s, probably due to an out of date config, just redo the selected item and save again.", name);
            }
        }
    }
}