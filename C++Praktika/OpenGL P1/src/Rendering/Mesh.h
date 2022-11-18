#pragma once
#include "MeshData.h"

class Material;

struct Mesh
{
    public:
        const MeshData* PMeshData;
        const Material* PMaterial;
};
