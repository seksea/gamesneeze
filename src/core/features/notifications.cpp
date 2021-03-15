#include "features.hpp"
#include "../../includes.hpp"
#include <cstdio>
#include <vector>

struct Notification {
    float openTime;
    ImColor color;
    char text[128];
};
std::vector<Notification> notifications = {};

void Features::Notifications::draw() {
    int yOffset = 20;
    for (Notification &notif : notifications) {
        float slideValue = Interfaces::globals->realtime - (notif.openTime + 8.f);
        ImColor shadowColor = ImColor(0, 0, 0, 255);
        notif.color.Value.w = 1.f-(slideValue*3.f);
        shadowColor.Value.w = 1.f-(slideValue*3.f);

        Globals::drawList->AddText(ImVec2((slideValue > 0.f) ? 4 - slideValue*800 : 4, yOffset+1), shadowColor, notif.text);
        Globals::drawList->AddText(ImVec2((slideValue > 0.f) ? 3 - slideValue*800 : 3, yOffset), notif.color, notif.text);

        yOffset+=13;

        if (notif.color.Value.w < 0.f) {
            notifications.erase(notifications.begin());
        }
    }
    while(notifications.size() > 8) {
        notifications.erase(notifications.begin());
    }
}

void Features::Notifications::addNotification(ImColor color, const char* fmt, ...) {
    Notification notif;
    notif.openTime = Interfaces::globals->realtime;
    notif.color = color;

    va_list args;
    va_start(args, fmt);
    vsnprintf(notif.text, sizeof(Notification::text), fmt, args);
    va_end(args);

    notifications.push_back(notif);
}