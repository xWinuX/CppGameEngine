#pragma once
#include "Component.h"
#include "../Rendering/Mesh.h"

class MeshRenderer final : Component
{
    private:
        Mesh* _pMesh;
        Material* _pMaterial;
    public:
        MeshRenderer(Mesh* pMesh, Material* pMaterial);
};
