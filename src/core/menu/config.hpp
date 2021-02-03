#pragma once
#include <unordered_map>
#include <fstream>
#include "imgui/imgui.h"

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
                CONFIGITEM("Team:Money", false),
            // }
            // Chams {
                CONFIGITEM("Enemy:ChamsMaterial", 0),
                CONFIGITEM("Enemy:ChamsPrimaryColor", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Enemy:IgnoreZChamsMaterial", 0),
                CONFIGITEM("Enemy:IgnoreZChamsPrimaryColor", ImColor(197, 66, 245, 255)),
                
                CONFIGITEM("Team:ChamsMaterial", 0),
                CONFIGITEM("Team:ChamsPrimaryColor", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Team:IgnoreZChamsMaterial", 0),
                CONFIGITEM("Team:IgnoreZChamsPrimaryColor", ImColor(197, 66, 245, 255)),

                CONFIGITEM("Weapon:ChamsMaterial", 0),
                CONFIGITEM("Weapon:ChamsPrimaryColor", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Arms:ChamsMaterial", 0),
                CONFIGITEM("Arms:ChamsPrimaryColor", ImColor(197, 66, 245, 255)),
            // }
            // World {
                CONFIGITEM("World:SpreadCrosshair", false),
                CONFIGITEM("World:WorldColorModulation", ImColor(255, 255, 255, 255)),

                CONFIGITEM("Weapon:Box", false),
                CONFIGITEM("Weapon:BoxColor", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Weapon:Name", false),

                CONFIGITEM("PlantedC4:Box", false),
                CONFIGITEM("PlantedC4:BoxColor", ImColor(255, 255, 255, 255)),
                CONFIGITEM("PlantedC4:Name", false),

                CONFIGITEM("Chicken:Box", false),
                CONFIGITEM("Chicken:BoxColor", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Chicken:Name", false),

                CONFIGITEM("Fish:Box", false),
                CONFIGITEM("Fish:BoxColor", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Fish:Name", false),

                CONFIGITEM("Debug:EspAll", false),
            // }
        // }
        // Misc {
            CONFIGITEM("Misc:RankReveal", false),
            CONFIGITEM("Misc:Clantag", false),

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
            sscanf(line.c_str(), "%d\t%s\t%s", (int*)&type, name, value);
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
        }
    }
}