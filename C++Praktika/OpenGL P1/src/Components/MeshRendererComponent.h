﻿#pragma once
#include "Component.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"
#include "../Rendering/Renderable.h"

class MeshRendererComponent final : public Component, public Renderable
{
    private:
        Mesh&              _pMesh;
        Material*          _pMaterial;
        VertexArrayObject _vertexArrayObject;
    public:
        MeshRendererComponent(Mesh& pMesh, Material* pMaterial);
        Mesh&              GetMesh() const;
        Material*          GetMaterial() override;
        VertexArrayObject* GetVertexArrayObject() override;
        const Transform* GetTransform() override { return Component::GetTransform(); }
        void OnStart() override;
};