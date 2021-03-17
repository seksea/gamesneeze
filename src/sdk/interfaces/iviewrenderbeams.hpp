#pragma once
#include <cstddef>

struct BeamInfo {
    int	type;
    Entity* startEnt;
    int startAttachment;
    Entity* endEnt;
    int	endAttachment;
    Vector start;
    Vector end;
    int modelIndex;
    const char* modelName;
    int haloIndex;
    const char* haloName;
    float haloScale;
    float life;
    float width;
    float endWidth;
    float fadeLength;
    float amplitude;
    float brightness;
    float speed;
    int	startFrame;
    float frameRate;
    float red;
    float green;
    float blue;
    bool renderable;
    int segments;
    int	flags;
    Vector ringCenter;
    float ringStartRadius;
    float ringEndRadius;
};

struct Beam {
    char a[76];
    int flags;
    char b[144];
    float die;
};

class ViewRenderBeams {
public:	
    Beam* createBeamPoints(BeamInfo& beamInfo) {
		typedef Beam* (*Fn)(void*, BeamInfo&);
		return getVirtualFunc<Fn>(this, 9)(this, beamInfo);
	}
};