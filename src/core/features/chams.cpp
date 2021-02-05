#include "../../includes.hpp"
#include "../../sdk/classes/keyvalues.hpp"

IMaterial* shadedMaterial;
IMaterial* flatMaterial;
IMaterial* pulseMaterial;
IMaterial* energyBallMaterial;
IMaterial* glowMaterial;
IMaterial* plasticMaterial;
IMaterial* darudeMaterial;

void createMaterials() {
    static bool init;
    if (!init) {
        shadedMaterial = Interfaces::materialSystem->FindMaterial("debug/debugambientcube", 0);
        flatMaterial = Interfaces::materialSystem->FindMaterial("debug/debugdrawflat", 0);
        pulseMaterial = Interfaces::materialSystem->FindMaterial("dev/screenhighlight_pulse", 0);
        energyBallMaterial = Interfaces::materialSystem->FindMaterial("effects/energyball", 0);
        glowMaterial = Interfaces::materialSystem->FindMaterial("dev/glow_armsrace", 0);
        plasticMaterial = Interfaces::materialSystem->FindMaterial("models/inventory_items/trophy_majors/gloss", 0);
        darudeMaterial = Interfaces::materialSystem->FindMaterial("models/inventory_items/music_kit/darude_01/mp3_detail", 0);
        init = true;
    }
}

void cham(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld, ImColor color, int mat, bool ignoreZ) {
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
    }
    material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignoreZ);
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
            if (p->team() != Globals::localPlayer->team()) {
                /* Visible Enemy */
                cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Enemies>Chams>Visible Color"), CONFIGINT("Visuals>Enemies>Chams>Visible Material"), false);
                /* Visible Enemy Overlay */
                if (CONFIGINT("Visuals>Enemies>Chams>Visible Overlay Material")) {
                    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Enemies>Chams>Visible Overlay Color"), CONFIGINT("Visuals>Enemies>Chams>Visible Overlay Material"), false);
                }
                /* Ignorez Enemy */
                if (CONFIGINT("Visuals>Enemies>Chams>Occluded Material")) {
                    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Enemies>Chams>Occluded Color"), CONFIGINT("Visuals>Enemies>Chams>Occluded Material"), true);
                }
            }
            else {
                /* Visible Teammate */
                cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Teammates>Chams>Visible Color"), CONFIGINT("Visuals>Teammates>Chams>Visible Material"), false);
                /* Visible Teammate Overlay */
                if (CONFIGINT("Visuals>Teammates>Chams>Visible Overlay Material")) {
                    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Teammates>Chams>Visible Overlay Color"), CONFIGINT("Visuals>Teammates>Chams>Visible Overlay Material"), false);
                }
                /* Ignorez Teammate */
                if (CONFIGINT("Visuals>Teammates>Chams>Occluded Material")) {
                    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>Teammates>Chams>Occluded Color"), CONFIGINT("Visuals>Teammates>Chams>Occluded Material"), true);
                }
            }
        }
        else {
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }
    }
}

void chamArms(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>World>Local Player>Arms Color"), CONFIGINT("Visuals>World>Local Player>Arms Material"), false);
    /* Arms Overlay */
    if (CONFIGINT("Visuals>World>Local Player>Arms Overlay Material")) {
        cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>World>Local Player>Arms Overlay Color"), CONFIGINT("Visuals>World>Local Player>Arms Overlay Material"), false);
    }
}

void chamWeapon(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>World>Local Player>Weapon Color"), CONFIGINT("Visuals>World>Local Player>Weapon Material"), false);
    /* Weapon Overlay */
    if (CONFIGINT("Visuals>World>Local Player>Weapon Overlay Material")) {
        cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGCOL("Visuals>World>Local Player>Weapon Overlay Color"), CONFIGINT("Visuals>World>Local Player>Weapon Overlay Material"), false);
    }
}

void Features::Chams::drawModelExecute(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    createMaterials();

	const char* modelName = Interfaces::modelInfo->GetModelName(pInfo.pModel);
	if (strstr(modelName, "models/player") && !strstr(modelName, "shadow")) {
        chamPlayer(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
    else if (strstr(modelName, "models/weapons/v_models/arms")) {
        chamArms(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    } 
    else if (strstr(modelName, "models/weapons")) {
        chamWeapon(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
    else {
        Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
}