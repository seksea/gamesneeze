#include "features.hpp"

void Features::ColorModulation::updateColorModulation() {
    for(auto i = Interfaces::materialSystem->FirstMaterial(); i != Interfaces::materialSystem->InvalidMaterial(); i = Interfaces::materialSystem->NextMaterial(i)) {
        IMaterial* material = Interfaces::materialSystem->GetMaterial(i);
        if (material && (strstr(material->GetTextureGroupName(), "World"))) {
            material->AlphaModulate(CONFIGCOL("Visuals>World>World>World Color Modulation").Value.w);
            material->ColorModulate(CONFIGCOL("Visuals>World>World>World Color Modulation").Value.x,
                                    CONFIGCOL("Visuals>World>World>World Color Modulation").Value.y,
                                    CONFIGCOL("Visuals>World>World>World Color Modulation").Value.z);
        }
        if (material && strstr(material->GetTextureGroupName(), "SkyBox")) {
            material->AlphaModulate(CONFIGCOL("Visuals>World>World>SkyBox Color Modulation").Value.w);
            material->ColorModulate(CONFIGCOL("Visuals>World>World>SkyBox Color Modulation").Value.x,
                                    CONFIGCOL("Visuals>World>World>SkyBox Color Modulation").Value.y,
                                    CONFIGCOL("Visuals>World>World>SkyBox Color Modulation").Value.z);
        }
    }
}
