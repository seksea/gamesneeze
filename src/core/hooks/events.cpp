#include "../../includes.hpp"
#include "hooks.hpp"

Hooks::Events::EventListener::EventListener() {
    Interfaces::eventManager->AddListener(this, "player_hurt", false);
    Interfaces::eventManager->AddListener(this, "player_death", false);
    Interfaces::eventManager->AddListener(this, "bullet_impact", false);
}

Hooks::Events::EventListener::~EventListener() {
    Interfaces::eventManager->RemoveListener(this);
}

void Hooks::Events::EventListener::FireGameEvent(IGameEvent *event) {
    if (strstr(event->GetName(), "player_hurt")) {
        Player* attacker = (Player*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetPlayerForUserID(event->GetInt("attacker")));
        Player* victim = (Player*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetPlayerForUserID(event->GetInt("userid")));
        if (attacker && victim && attacker == Globals::localPlayer) {
            player_info_t info;
            Interfaces::engine->GetPlayerInfo(victim->index(), &info);

            if (CONFIGBOOL("Misc>Misc>Hitmarkers>Hitlogs")) {
                if (CONFIGBOOL("Legit>Backtrack>Backtrack") && Features::Backtrack::lastBacktrack > 4) {
                    Features::Notifications::addNotification(ImColor(220, 220, 40), "[gs] backtracked %s %i ticks for %i health", info.name, Features::Backtrack::lastBacktrack, event->GetInt("dmg_health"));
                }
                else {
                    Features::Notifications::addNotification(ImColor(220, 220, 40), "[gs] hit %s for %i health", info.name, event->GetInt("dmg_health"));
                }
            }

            if (CONFIGBOOL("Misc>Misc>Hitmarkers>Hitmarkers")) {
                Features::Hitmarkers::drawHitmarkerTill = Interfaces::globals->curtime + 0.7f;
            }

            if (CONFIGBOOL("Misc>Misc>Hitmarkers>Hitsound")) {
                Interfaces::engine->ExecuteClientCmd("play buttons/arena_switch_press_02"); // TODO: play sound via a better method
            }

            if (CONFIGBOOL("Misc>Misc>Hitmarkers>Damage Markers")) {
                Features::Hitmarkers::DamageMarker damageMarker;
                damageMarker.drawHitmarkerTill = Interfaces::globals->curtime + 4.f;
                damageMarker.headshot = event->GetInt("hitgroup") == HITGROUP_HEAD;
                damageMarker.damage = event->GetInt("dmg_health");
                switch (event->GetInt("hitgroup")) {
                    case HITGROUP_HEAD: damageMarker.position = victim->getBonePos(8); break;
                    case HITGROUP_CHEST: damageMarker.position = victim->getBonePos(6); break;
                    case HITGROUP_STOMACH: damageMarker.position = victim->getBonePos(4); break;
                    default:
                        damageMarker.position = victim->getBonePos(3); break;
                }
                Features::Hitmarkers::damageMarkers.push_back(damageMarker);
            }
        }
    }
    else if (strstr(event->GetName(), "player_death")) {
        Entity* attacker = (Entity*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetPlayerForUserID(event->GetInt("attacker")));
        Entity* victim = (Entity*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetPlayerForUserID(event->GetInt("userid")));
        if (attacker && victim && attacker == Globals::localPlayer) {
            player_info_t info;
            Interfaces::engine->GetPlayerInfo(victim->index(), &info);

            if (CONFIGBOOL("Misc>Misc>Hitmarkers>Hitlogs")) {
                Features::Notifications::addNotification(ImColor(220, 40, 40), "[gs] killed %s", info.name);
            }
        }
    }
    Features::BulletTracers::event(event);
}

int Hooks::Events::EventListener::GetEventDebugID() {
    return EVENT_DEBUG_ID_INIT;
}