#include "../../includes.hpp"
#include "../../sdk/classes/keyvalues.hpp"
#include "features.hpp"
#include <cstring>

IMaterial* shadedMaterial;
IMaterial* flatMaterial;
IMaterial* pulseMaterial;
IMaterial* energyBallMaterial;
IMaterial* glowMaterial;
IMaterial* plasticMaterial;
IMaterial* darudeMaterial;
IMaterial* oilMaterial;

IMaterial* createMaterial(const char* materialName, const char* materialType, const char* material) {
	KeyValues* keyValues = new KeyValues(materialName);

	Offsets::initKeyValues(keyValues, materialType, 0, 0);
	Offsets::loadFromBuffer(keyValues, materialName, material, nullptr, nullptr, nullptr);

	return Interfaces::materialSystem->CreateMaterial(materialName, keyValues);
}

void createMaterials() {
    static bool init;
    if (!init) {
        shadedMaterial = Interfaces::materialSystem->FindMaterial("debug/debugambientcube", 0);
        flatMaterial = Interfaces::materialSystem->FindMaterial("debug/debugdrawflat", 0);
        pulseMaterial = Interfaces::materialSystem->FindMaterial("dev/screenhighlight_pulse", 0);
        energyBallMaterial = Interfaces::materialSystem->FindMaterial("effects/energyball", 0);
        plasticMaterial = Interfaces::materialSystem->FindMaterial("models/inventory_items/trophy_majors/gloss", 0);
        darudeMaterial = Interfaces::materialSystem->FindMaterial("models/inventory_items/music_kit/darude_01/mp3_detail", 0);

        glowMaterial = createMaterial("glow", "VertexLitGeneric",
        R"#("VertexLitGeneric" {
            "$additive" "1"
            "$envmap" "models/effects/cube_white"
            "$envmaptint" "[1 1 1]"
            "$envmapfresnel" "1"
            "$envmapfresnelminmaxexp" "[0 1 2]"
            "$alpha" "0.8"
        })#");

        oilMaterial = createMaterial("pearlescent", "VertexLitGeneric",
        R"#("VertexLitGeneric"
        {
            "$basetexture" "vgui/white_additive"
            "$nocull" "1"
            "$nofog" "1"
            "$model" "1"
            "$nocull" "0"
            "$phong" "1"
            "$phongboost" "0"
            "$basemapalphaphongmask" "1"
            "$pearlescent" "6"
        })#");

        init = true;
    }
}

void cham(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld, ImColor color, int mat, bool ignoreZ, bool wireframe = false) {
    static IMaterial* material;
    switch(mat) {
        case 0: Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld); return;
        case 1: material = shadedMaterial;  break;
        case 2: material = flatMaterial;  break;
        case 3: material = pulseMaterial; break;
        case 4: material = energyBallMaterial; break;
        case 5: material = glowMaterial; break;
        case 6: material = plasticMaterial; break;
        case 7: material = darudeMaterial; break;
        case 8: material = oilMaterial; break;
    }
    material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignoreZ);
    material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, wireframe);
    material->AlphaModulate(color.Value.w);
    material->ColorModulate(color.Value.x, color.Value.y, color.Value.z);
    bool found;
    IMaterialVar* var = material->FindVar("$envmaptint", &found);
    if (found) {
        var->SetVecValue(color.Value.x, color.Value.y, color.Value.z);
    }
    Interfaces::modelRender->ForcedMaterialOverride(material);
    Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    Interfaces::modelRender->ForcedMaterialOverride(0);
}

void chamPlayer(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    Player* p = (Player*)Interfaces::entityList->GetClientEntity(pInfo.entity_index);
    if (Globals::localPlayer) {
        if (p->health() > 0) {
            if (p->isEnemy()) {
                /* Ignorez Enemy */
                if (CONFIGINT("Visuals>Players>Enemies>Chams>Occluded Material")) {
                    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>Enemies>Chams>Occluded Color"), CONFIGINT("Visuals>Players>Enemies>Chams>Occluded Material"), true);
                }
                /* Visible Enemy */
                cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>Enemies>Chams>Visible Color"), CONFIGINT("Visuals>Players>Enemies>Chams>Visible Material"), false, CONFIGBOOL("Visuals>Players>Enemies>Chams>Visible Wireframe"));
                /* Visible Enemy Overlay */
                if (CONFIGINT("Visuals>Players>Enemies>Chams>Visible Overlay Material")) {
                    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>Enemies>Chams>Visible Overlay Color"), CONFIGINT("Visuals>Players>Enemies>Chams>Visible Overlay Material"), false, CONFIGBOOL("Visuals>Players>Enemies>Chams>Visible Overlay Wireframe"));
                }

                if (CONFIGBOOL("Legit>Backtrack>Backtrack") && !CONFIGBOOL("Rage>Enabled")) {
                    if (Features::Backtrack::backtrackTicks.size() > 2) {
                        if (CONFIGINT("Visuals>Players>Enemies>Chams>Backtrack Material")) {
                            if (CONFIGBOOL("Visuals>Players>Enemies>Chams>Trail")) {
                                for (Features::Backtrack::BackTrackTick tick : Features::Backtrack::backtrackTicks) {
                                    if (tick.tickCount % 2 == 0) { // only draw every other tick to reduce lag
                                        if (tick.players.find(p->index()) != tick.players.end()) {
                                            if (abs((tick.players.at(p->index()).playerHeadPos - p->getBonePos(8)).Length()) > 2) {
                                                cham(thisptr, ctx, state, pInfo, tick.players.at(p->index()).boneMatrix, CONFIGCOL("Visuals>Players>Enemies>Chams>Backtrack Color"), CONFIGINT("Visuals>Players>Enemies>Chams>Backtrack Material"), false);
                                            }
                                        }
                                    }
                                }
                            }
                            else {
                                Features::Backtrack::BackTrackTick tick = Features::Backtrack::backtrackTicks.at(Features::Backtrack::backtrackTicks.size()-1);
                                if (tick.players.find(p->index()) != tick.players.end()) {
                                    if (abs((tick.players.at(p->index()).playerHeadPos - p->getBonePos(8)).Length()) > 2) {
                                        cham(thisptr, ctx, state, pInfo, tick.players.at(p->index()).boneMatrix, CONFIGCOL("Visuals>Players>Enemies>Chams>Backtrack Color"), CONFIGINT("Visuals>Players>Enemies>Chams>Backtrack Material"), false);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else {
                /* Ignorez Teammate */
                if (CONFIGINT("Visuals>Players>Teammates>Chams>Occluded Material")) {
                    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>Teammates>Chams>Occluded Color"), CONFIGINT("Visuals>Players>Teammates>Chams>Occluded Material"), true);
                }
                /* Visible Teammate */
                cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>Teammates>Chams>Visible Color"), CONFIGINT("Visuals>Players>Teammates>Chams>Visible Material"), false, CONFIGBOOL("Visuals>Players>Teammates>Chams>Visible Wireframe"));
                /* Visible Teammate Overlay */
                if (CONFIGINT("Visuals>Players>Teammates>Chams>Visible Overlay Material")) {
                    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>Teammates>Chams>Visible Overlay Color"), CONFIGINT("Visuals>Players>Teammates>Chams>Visible Overlay Material"), false, CONFIGBOOL("Visuals>Players>Teammates>Chams>Visible Overlay Wireframe"));
                }
            }
        }
        else {
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }
    }
}

void chamArms(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>LocalPlayer>Arms Color"), CONFIGINT("Visuals>Players>LocalPlayer>Arms Material"), false, CONFIGBOOL("Visuals>Players>LocalPlayer>Arms Wireframe"));
    /* Arms Overlay */
    if (CONFIGINT("Visuals>Players>LocalPlayer>Arms Overlay Material")) {
        cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>LocalPlayer>Arms Overlay Color"), CONFIGINT("Visuals>Players>LocalPlayer>Arms Overlay Material"), false, CONFIGBOOL("Visuals>Players>LocalPlayer>Arms Overlay Wireframe"));
    }
}

void chamSleeves(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>LocalPlayer>Sleeve Color"), CONFIGINT("Visuals>Players>LocalPlayer>Sleeve Material"), false, CONFIGBOOL("Visuals>Players>LocalPlayer>Sleeve Wireframe"));
    /* Arms Overlay */
    if (CONFIGINT("Visuals>Players>LocalPlayer>Sleeve Overlay Material")) {
        cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>LocalPlayer>Sleeve Overlay Color"), CONFIGINT("Visuals>Players>LocalPlayer>Sleeve Overlay Material"), false, CONFIGBOOL("Visuals>Players>LocalPlayer>Sleeve Overlay Wireframe"));
    }
}

void chamWeapon(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    if (Globals::localPlayer) {
        if (!Globals::localPlayer->scoped()) {
            cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>LocalPlayer>Weapon Color"), CONFIGINT("Visuals>Players>LocalPlayer>Weapon Material"), false, CONFIGBOOL("Visuals>Players>LocalPlayer>Weapon Wireframe"));
            /* Weapon Overlay */
            if (CONFIGINT("Visuals>Players>LocalPlayer>Weapon Overlay Material")) {
                cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Players>LocalPlayer>Weapon Overlay Color"), CONFIGINT("Visuals>Players>LocalPlayer>Weapon Overlay Material"), false, CONFIGBOOL("Visuals>Players>LocalPlayer>Weapon Overlay Wireframe"));
            }
        }
        else {
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }

    }
}

void Features::Chams::drawModelExecute(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    createMaterials();

	const char* modelName = Interfaces::modelInfo->GetModelName(pInfo.pModel);
	if (strstr(modelName, "models/player") && !strstr(modelName, "shadow")) {
        chamPlayer(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
    else if (strstr(modelName, "models/weapons/v_")) {
        if (strstr(modelName, "sleeve")) {
            chamSleeves(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }
        else if (strstr(modelName, "arms")) {
            chamArms(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }
        else {
            chamWeapon(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }
    }
    else if (strstr(modelName, "models/weapons/v_")) {
        chamWeapon(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
    else {
        Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
}
