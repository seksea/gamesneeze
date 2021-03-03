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
        // Legit {
            // LegitBot {
                // Default {
                    CONFIGITEM("Legit>LegitBot>Default>Key", 0),
                    CONFIGITEM("Legit>LegitBot>Default>Always on", false),
                    CONFIGITEM("Legit>LegitBot>Default>FOV", 0),
                    CONFIGITEM("Legit>LegitBot>Default>Smoothing", 0),
                    CONFIGITEM("Legit>LegitBot>Default>Recoil Compensation", false),
                //}
                // Pistol {
                    CONFIGITEM("Legit>LegitBot>Pistol>Override", false),
                    CONFIGITEM("Legit>LegitBot>Pistol>FOV", 0),
                    CONFIGITEM("Legit>LegitBot>Pistol>Smoothing", 0),
                //}
                // Heavy Pistol {
                    CONFIGITEM("Legit>LegitBot>Heavy Pistol>Override", false),
                    CONFIGITEM("Legit>LegitBot>Heavy Pistol>FOV", 0),
                    CONFIGITEM("Legit>LegitBot>Heavy Pistol>Smoothing", 0),
                //}
                // Rifle {
                    CONFIGITEM("Legit>LegitBot>Rifle>Override", false),
                    CONFIGITEM("Legit>LegitBot>Rifle>FOV", 0),
                    CONFIGITEM("Legit>LegitBot>Rifle>Smoothing", 0),
                    CONFIGITEM("Legit>LegitBot>Rifle>Recoil Compensation", false),
                //}
                // SMG {
                    CONFIGITEM("Legit>LegitBot>SMG>Override", false),
                    CONFIGITEM("Legit>LegitBot>SMG>FOV", 0),
                    CONFIGITEM("Legit>LegitBot>SMG>Smoothing", 0),
                    CONFIGITEM("Legit>LegitBot>SMG>Recoil Compensation", false),
                //}
                // Scout {
                    CONFIGITEM("Legit>LegitBot>Scout>Override", false),
                    CONFIGITEM("Legit>LegitBot>Scout>FOV", 0),
                    CONFIGITEM("Legit>LegitBot>Scout>Smoothing", 0),
                //}
                // AWP {
                    CONFIGITEM("Legit>LegitBot>AWP>Override", false),
                    CONFIGITEM("Legit>LegitBot>AWP>FOV", 0),
                    CONFIGITEM("Legit>LegitBot>AWP>Smoothing", 0),
                //}
                // Heavy {
                    CONFIGITEM("Legit>LegitBot>Heavy>Override", false),
                    CONFIGITEM("Legit>LegitBot>Heavy>FOV", 0),
                    CONFIGITEM("Legit>LegitBot>Heavy>Smoothing", 0),
                    CONFIGITEM("Legit>LegitBot>Heavy>Recoil Compensation", false),
                //}
            // }


            // Backtrack {
                CONFIGITEM("Legit>Backtrack>Backtrack", false),
                CONFIGITEM("Legit>Backtrack>Backtrack Ticks", 12),
                CONFIGITEM("Legit>Backtrack>Simple Forwardtracking", false),
            // }
            // Triggerbot {
                CONFIGITEM("Legit>Triggerbot>Key", 0),
                CONFIGITEM("Legit>Triggerbot>Triggerbot", false),
                CONFIGITEM("Legit>Triggerbot>Head Hitchance", 0),
                CONFIGITEM("Legit>Triggerbot>Body Hitchance", 0),
            // }
        // }
        // RageBot {
            // Default {
                CONFIGITEM("Rage>Enabled", false),
                CONFIGITEM("Rage>RageBot>Default>Resolver", false),
                CONFIGITEM("Rage>RageBot>Default>FOV", 0),

                CONFIGITEM("Rage>AntiAim>AntiAim", 0),
                CONFIGITEM("Rage>AntiAim>Pitch", 89),
                CONFIGITEM("Rage>AntiAim>Offset", 180),
                CONFIGITEM("Rage>AntiAim>FakeLag", 0),
                // Static {
                    CONFIGITEM("Rage>AntiAim>Static>Desync", 0),
                // }

                // Jitter {
                    CONFIGITEM("Rage>AntiAim>Jitter>Desync", 0),
                    CONFIGITEM("Rage>AntiAim>Jitter>Jitter Amount", 0),
                    CONFIGITEM("Rage>AntiAim>Jitter>Jitter Delay", 1),
                    CONFIGITEM("Rage>AntiAim>Jitter>Random", false),
                    CONFIGITEM("Rage>AntiAim>Jitter>Random Min", 0),
                    CONFIGITEM("Rage>AntiAim>Jitter>Random Max", 0),
                // }

                // Fake Jitter {
                    CONFIGITEM("Rage>AntiAim>Fake Jitter>Jitter Amount", 0),
                    CONFIGITEM("Rage>AntiAim>Fake Jitter>Jitter Delay", 1),
                    CONFIGITEM("Rage>AntiAim>Fake Jitter>Random", false),
                    CONFIGITEM("Rage>AntiAim>Fake Jitter>Random Min", 0),
                    CONFIGITEM("Rage>AntiAim>Fake Jitter>Random Max", 0),
                // }

                // Real Jitter {
                    CONFIGITEM("Rage>AntiAim>Real Jitter>Jitter Amount", 0),
                    CONFIGITEM("Rage>AntiAim>Real Jitter>Jitter Delay", 1),
                    CONFIGITEM("Rage>AntiAim>Real Jitter>Random", false),
                    CONFIGITEM("Rage>AntiAim>Real Jitter>Random Min", 0),
                    CONFIGITEM("Rage>AntiAim>Real Jitter>Random Max", 0),
                // }

                // Spin {
                    CONFIGITEM("Rage>AntiAim>Spin>Desync", 0),
                // }
            //}
        // }
        // Visuals {
            // ESP {
                CONFIGITEM("Visuals>Players>Enemies>Box", false),
                CONFIGITEM("Visuals>Players>Enemies>Box Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>Enemies>Skeleton", false),
                CONFIGITEM("Visuals>Players>Enemies>Skeleton Color", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Visuals>Players>Enemies>Name", false),
                CONFIGITEM("Visuals>Players>Enemies>Health", false),
                CONFIGITEM("Visuals>Players>Enemies>Health Bar Color", ImColor(0, 240, 0, 255)),
                CONFIGITEM("Visuals>Players>Enemies>Health Bar", false),
                CONFIGITEM("Visuals>Players>Enemies>Dynamic Color", false),
                CONFIGITEM("Visuals>Players>Enemies>Money", false),
                CONFIGITEM("Visuals>Players>Enemies>Radar", false),
                CONFIGITEM("Visuals>Players>Enemies>Forwardtrack Dots", false),
                CONFIGITEM("Visuals>Players>Enemies>Vis Check", false),
                CONFIGITEM("Visuals>Players>Enemies>Only When Dead", false),

                CONFIGITEM("Visuals>Players>Teammates>Box", false),
                CONFIGITEM("Visuals>Players>Teammates>Box Color", ImColor(10, 161, 32, 255)),
                CONFIGITEM("Visuals>Players>Teammates>Skeleton", false),
                CONFIGITEM("Visuals>Players>Teammates>Skeleton Color", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Visuals>Players>Teammates>Name", false),
                CONFIGITEM("Visuals>Players>Teammates>Health", false),
                CONFIGITEM("Visuals>Players>Teammates>Health Bar Color", ImColor(0, 240, 0, 255)),
                CONFIGITEM("Visuals>Players>Teammates>Health Bar", false),
                CONFIGITEM("Visuals>Players>Teammates>Dynamic Color", false),
                CONFIGITEM("Visuals>Players>Teammates>Money", false),
                CONFIGITEM("Visuals>Players>Teammates>Only When Dead", false),
            // }
            // Chams {
                CONFIGITEM("Visuals>Players>Enemies>Chams>Visible Material", 0),
                CONFIGITEM("Visuals>Players>Enemies>Chams>Visible Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>Enemies>Chams>Visible Overlay Material", 0),
                CONFIGITEM("Visuals>Players>Enemies>Chams>Visible Overlay Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>Enemies>Chams>Occluded Material", 0),
                CONFIGITEM("Visuals>Players>Enemies>Chams>Occluded Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>Enemies>Chams>Backtrack Material", 0),
                CONFIGITEM("Visuals>Players>Enemies>Chams>Backtrack Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>Enemies>Chams>Trail", false),
                
                CONFIGITEM("Visuals>Players>Teammates>Chams>Visible Material", 0),
                CONFIGITEM("Visuals>Players>Teammates>Chams>Visible Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>Teammates>Chams>Visible Overlay Material", 0),
                CONFIGITEM("Visuals>Players>Teammates>Chams>Visible Overlay Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>Teammates>Chams>Occluded Material", 0),
                CONFIGITEM("Visuals>Players>Teammates>Chams>Occluded Color", ImColor(197, 66, 245, 255)),

                CONFIGITEM("Visuals>Players>LocalPlayer>Weapon Material", 0),
                CONFIGITEM("Visuals>Players>LocalPlayer>Weapon Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>LocalPlayer>Weapon Overlay Material", 0),
                CONFIGITEM("Visuals>Players>LocalPlayer>Weapon Overlay Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>LocalPlayer>Arms Material", 0),
                CONFIGITEM("Visuals>Players>LocalPlayer>Arms Color", ImColor(197, 66, 245, 255)),
                CONFIGITEM("Visuals>Players>LocalPlayer>Arms Overlay Material", 0),
                CONFIGITEM("Visuals>Players>LocalPlayer>Arms Overlay Color", ImColor(197, 66, 245, 255)),
            // }
            // World {
                CONFIGITEM("Visuals>Players>LocalPlayer>Spread Crosshair", false),
                CONFIGITEM("Visuals>Players>LocalPlayer>Recoil Crosshair", false),
                CONFIGITEM("Visuals>Players>LocalPlayer>Recoil Crosshair>Only When Shooting", false),
                CONFIGITEM("Visuals>Players>LocalPlayer>Crosshair Color", ImColor(0, 0, 0, 100)),
                CONFIGITEM("Visuals>Players>LocalPlayer>Crosshair Border Color", ImColor(200, 200, 200, 100)),

                CONFIGITEM("Visuals>World>World>World Color Modulation", ImColor(255, 255, 255, 255)),
                CONFIGITEM("Visuals>World>World>Nightmode", 0),
                CONFIGITEM("Visuals>World>World>Skybox", 0),
                CONFIGITEM("Visuals>World>World>FOV", 90),
                CONFIGITEM("Visuals>World>World>Third Person", false),
                CONFIGITEM("Visuals>World>World>Third Person Shows Fake", false),

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
            CONFIGITEM("Misc>Misc>Movement>Auto Hop", false),
            CONFIGITEM("Misc>Misc>Movement>Humanised Bhop", 100),
            CONFIGITEM("Misc>Misc>Movement>Bhop Hitchance", 100),
            CONFIGITEM("Misc>Misc>Movement>Bhop Max Misses", 0),
            CONFIGITEM("Misc>Misc>Movement>Bhop Max Hops Hit", 0),
            CONFIGITEM("Misc>Misc>Movement>Fast Duck", false),

            CONFIGITEM("Misc>Misc>Hitmarkers>Hitlogs", false),
            
            CONFIGITEM("Misc>Misc>Misc>Disable Watermark", false),
            CONFIGITEM("Misc>Misc>Misc>Force square radar", false),
            CONFIGITEM("Misc>Misc>Misc>Rank Revealer", false),
            CONFIGITEM("Misc>Misc>Clantag>Clantag", false),
            CONFIGITEM("Misc>Misc>Clantag>Clantag Marquee", false),
            CONFIGITEM("Misc>Misc>Clantag>Bee Movie Clantag", false),
            CONFIGITEM("Misc>Misc>Misc>Spectators", false),
            CONFIGITEM("Misc>Misc>Misc>Player List", false),
            CONFIGITEM("Misc>Misc>Misc>Flappy Birb", false),
            CONFIGITEM("Misc>Misc>Misc>Auto Accept", false),
            CONFIGITEM("Misc>Misc>Misc>Auto Defuse", false),
            CONFIGITEM("Misc>Misc>Misc>Latest Defuse", false),
            CONFIGITEM("Misc>Misc>Misc>Chat Filter Bypass", false),

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