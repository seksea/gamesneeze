#include "features.hpp"

void Features::WorldColorModulate::updateColorModulation() {
    for(auto i = Interfaces::materialSystem->FirstMaterial(); i != Interfaces::materialSystem->InvalidMaterial(); i = Interfaces::materialSystem->NextMaterial(i)) {
        IMaterial* material = Interfaces::materialSystem->GetMaterial(i);
        if (material) {
            if(strstr(material->GetTextureGroupName(), "World")) {
                material->AlphaModulate(CONFIGCOL("World:WorldColorModulation").Value.w);
                material->ColorModulate(CONFIGCOL("World:WorldColorModulation").Value.x, CONFIGCOL("World:WorldColorModulation").Value.y, CONFIGCOL("World:WorldColorModulation").Value.z);
            }
        }
    }
}