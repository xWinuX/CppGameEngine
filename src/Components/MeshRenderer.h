#pragma once
#include "Component.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"
#include "../Rendering/Renderable.h"
#include "../Rendering/VertexArrayObject.h"

class MeshRenderer final : public Component, public Renderable
{
    private:
        Mesh*              _pMesh;
        Material*          _pMaterial;
        VertexArrayObject* _pVertexArrayObject;
        bool               _visible = true;

    public:
        MeshRenderer(Mesh* pMesh, Material* pMaterial);
        ~MeshRenderer() override;
        Mesh*     GetMesh() const;
        Material* GetMaterial() override;
        void      OnBeforeRender() override;
        void      OnDraw() override;
        void      OnBeforeDraw() override;
        void      OnStart() override;

        bool GetVisible() const { return _visible; }
        void SetVisible(const bool value) { _visible = value; }
};
