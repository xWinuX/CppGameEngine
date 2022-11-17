#pragma once
#include "MeshData.h"

class Material;

struct Mesh
{
    public:
        const MeshData* pMeshData;
        const Material* pMaterial;
};
