#include "../../includes.hpp"

namespace Features {
    namespace ESP {
        void drawESP();
    }
    namespace Chams {
        void doChams(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld); // DME
    }
    namespace RankReveal {
        void rankReveal(); // CM
    }
    namespace WorldColorModulate {
        void updateColorModulation();
    }
}