#include "../../includes.hpp"
#include "hooks.hpp"

typedef void (*EmitSound2Fn) (void*, void**, int, int, const char*, unsigned int, const char*, float, int, void*, int, int, const Vector*, const Vector*, void*, bool, float, int, void*&);

void Hooks::EmitSound::hook(void* thisptr, void*& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, int nSeed, void* iSoundLevel, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, void*& params) {
	Features::AutoAccept::emitSound(pSoundEntry);
	if(Features::Prediction::inPrediction && iEntIndex == Globals::localPlayer->index())
		return;
	Hooks::EmitSound::original(thisptr, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, nSeed, iSoundLevel, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, params);
}