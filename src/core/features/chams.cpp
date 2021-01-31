#include "../../includes.hpp"
#include "../../sdk/classes/keyvalues.hpp"

IMaterial* shadedMaterial;
IMaterial* flatMaterial;
IMaterial* pulseMaterial;
IMaterial* energyBallMaterial;

void createMaterials() {
    static bool init;
    if (!init) {
        shadedMaterial = Interfaces::materialSystem->FindMaterial("debug/debugambientcube", 0);
        flatMaterial = Interfaces::materialSystem->FindMaterial("debug/debugdrawflat", 0);
        pulseMaterial = Interfaces::materialSystem->FindMaterial("dev/screenhighlight_pulse", 0);
        energyBallMaterial = Interfaces::materialSystem->FindMaterial("effects/energyball", 0);
        init = true;
    }
}

void chamPlayer(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    static IMaterial* ignoreZMaterial;
    static IMaterial* material;
    Player* p = (Player*)Interfaces::entityList->GetClientEntity(pInfo.entity_index);
    if (Globals::localPlayer) {
        bool ignoreZChams;
        ImColor primaryColour;
        ImColor primaryIgnoreZColour;

        if (p->team() != Globals::localPlayer->team()) {
            primaryColour = CONFIGCOL("Enemy:ChamsPrimaryColor");
            primaryIgnoreZColour = CONFIGCOL("Enemy:IgnoreZChamsPrimaryColor");
            ignoreZChams = CONFIGINT("Enemy:IgnoreZChamsMaterial") != 0;
            switch(CONFIGINT("Enemy:IgnoreZChamsMaterial")) {
                case 1: ignoreZMaterial = shadedMaterial;  break;
                case 2: ignoreZMaterial = flatMaterial;  break;
                case 3: ignoreZMaterial = pulseMaterial; break;
                case 4: ignoreZMaterial = energyBallMaterial; break;
            }
            switch(CONFIGINT("Enemy:ChamsMaterial")) { // Visible
                case 0: Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld); return;
                case 1: material = shadedMaterial;  break;
                case 2: material = flatMaterial;  break;
                case 3: material = pulseMaterial; break;
                case 4: material = energyBallMaterial; break;
            }
        }
        else {
            primaryColour = CONFIGCOL("Team:ChamsPrimaryColor");
            primaryIgnoreZColour = CONFIGCOL("Team:IgnoreZChamsPrimaryColor");
            ignoreZChams = CONFIGINT("Team:IgnoreZChamsMaterial") != 0;
            switch(CONFIGINT("Team:IgnoreZChamsMaterial")) {
                case 1: ignoreZMaterial = shadedMaterial;  break;
                case 2: ignoreZMaterial = flatMaterial;  break;
                case 3: ignoreZMaterial = pulseMaterial; break;
                case 4: ignoreZMaterial = energyBallMaterial; break;
            }
            switch(CONFIGINT("Team:ChamsMaterial")) { // Visible
                case 0: Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld); return;
                case 1: material = shadedMaterial;  break;
                case 2: material = flatMaterial;  break;
                case 3: material = pulseMaterial; break;
                case 4: material = energyBallMaterial; break;
            }
        }
        if(ignoreZChams) { // IgnoreZ
            ignoreZMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
            ignoreZMaterial->AlphaModulate(primaryIgnoreZColour.Value.w);
            ignoreZMaterial->ColorModulate(primaryIgnoreZColour.Value.x, primaryIgnoreZColour.Value.y, primaryIgnoreZColour.Value.z);
            Interfaces::modelRender->ForcedMaterialOverride(ignoreZMaterial);
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
            Interfaces::modelRender->ForcedMaterialOverride(0);
        }
        material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
        material->AlphaModulate(primaryColour.Value.w);
        material->ColorModulate(primaryColour.Value.x, primaryColour.Value.y, primaryColour.Value.z);
        Interfaces::modelRender->ForcedMaterialOverride(material);
        Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        Interfaces::modelRender->ForcedMaterialOverride(0);
    }
}

void chamArms(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    static IMaterial* material;
    switch(CONFIGINT("Arms:ChamsMaterial")) { // Visible
        case 0: Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld); return;
        case 1: material = shadedMaterial;  break;
        case 2: material = flatMaterial;  break;
        case 3: material = pulseMaterial; break;
        case 4: material = energyBallMaterial; break;
    }
    material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
    material->AlphaModulate(CONFIGCOL("Arms:ChamsPrimaryColor").Value.w);
    material->ColorModulate(CONFIGCOL("Arms:ChamsPrimaryColor").Value.x, CONFIGCOL("Arms:ChamsPrimaryColor").Value.y, CONFIGCOL("Arms:ChamsPrimaryColor").Value.z);
    Interfaces::modelRender->ForcedMaterialOverride(material);
    Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    Interfaces::modelRender->ForcedMaterialOverride(0);
}

void chamWeapon(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    static IMaterial* material;
    switch(CONFIGINT("Weapon:ChamsMaterial")) { // Visible
        case 0: Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld); return;
        case 1: material = shadedMaterial;  break;
        case 2: material = flatMaterial;  break;
        case 3: material = pulseMaterial; break;
        case 4: material = energyBallMaterial; break;
    }
    material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
    material->AlphaModulate(CONFIGCOL("Weapon:ChamsPrimaryColor").Value.w);
    material->ColorModulate(CONFIGCOL("Weapon:ChamsPrimaryColor").Value.x, CONFIGCOL("Weapon:ChamsPrimaryColor").Value.y, CONFIGCOL("Weapon:ChamsPrimaryColor").Value.z);
    Interfaces::modelRender->ForcedMaterialOverride(material);
    Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    Interfaces::modelRender->ForcedMaterialOverride(0);
}

void Features::Chams::doChams(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
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