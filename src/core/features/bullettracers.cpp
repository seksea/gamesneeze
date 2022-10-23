#include "features.hpp"

void Features::BulletTracers::event(IGameEvent* event) {
    if (strstr(event->GetName(), "bullet_impact") && CONFIGBOOL("Visuals>World>World>Bullet Tracers")) {
        Player* attacker = (Player*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetPlayerForUserID(event->GetInt("userid")));
        if (attacker && !attacker->dormant()) {
            BeamInfo beamInfo;

            beamInfo.start = attacker->eyePos();
            beamInfo.start.x += randFloat(-1, 1);
            beamInfo.start.y += randFloat(-1, 1);
            beamInfo.start.z += randFloat(-1, 1);

            beamInfo.end.x = event->GetFloat("x");
            beamInfo.end.y = event->GetFloat("y");
            beamInfo.end.z = event->GetFloat("z");

            beamInfo.modelName = CONFIGBOOL("Visuals>World>World>Bullet Tracers Laser") ? "sprites/purplelaser1.vmt" : "sprites/physbeam.vmt";
            beamInfo.modelIndex = -1;
            beamInfo.haloName = nullptr;
            beamInfo.haloIndex = -1;

            beamInfo.red = 255.0f * CONFIGCOL("Visuals>World>World>Bullet Tracers Color").Value.x;
            beamInfo.green = 255.0f * CONFIGCOL("Visuals>World>World>Bullet Tracers Color").Value.y;
            beamInfo.blue = 255.0f * CONFIGCOL("Visuals>World>World>Bullet Tracers Color").Value.z;
            beamInfo.brightness = 255.0f * CONFIGCOL("Visuals>World>World>Bullet Tracers Color").Value.w;
            
            beamInfo.type = 0;
            beamInfo.life = 0.0f;
            beamInfo.amplitude = 0.0f;
            beamInfo.segments = -1;
            beamInfo.renderable = true;
            beamInfo.speed = 0.2f;
            beamInfo.startFrame = 0;
            beamInfo.frameRate = 0.0f;
            beamInfo.width = 2.0f;
            beamInfo.endWidth = 2.0f;
            beamInfo.flags = 0x40;
            beamInfo.fadeLength = 20.0f;

            if (const auto beam = Interfaces::renderBeams->createBeamPoints(beamInfo)) {
                constexpr auto FBEAM_FOREVER = 0x4000;
                beam->flags &= ~FBEAM_FOREVER;
                beam->die = Interfaces::globals->curtime + 2.f;
            }
        }
    }
}