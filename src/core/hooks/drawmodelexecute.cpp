#include "../../includes.hpp"
#include "hooks.hpp"


void Hooks::DrawModelExecute::hook(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    Features::Chams::drawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
}