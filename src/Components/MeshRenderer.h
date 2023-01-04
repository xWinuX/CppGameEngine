#pragma once
#include "Component.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"
#include "../Rendering/Renderable.h"
#include "../Rendering/VertexArrayObject.h"

namespace GameEngine
{
    namespace Components
    {
        class MeshRenderer final : public Component, public GameEngine::Rendering::Renderable
        {
            private:
                GameEngine::Rendering::Mesh*              _pMesh;
                GameEngine::Rendering::Material*          _pMaterial;
                GameEngine::Rendering::VertexArrayObject* _pVertexArrayObject;
                bool                                      _visible = true;

            public:
                MeshRenderer(GameEngine::Rendering::Mesh* pMesh, GameEngine::Rendering::Material* pMaterial);
                ~MeshRenderer() override;
                GameEngine::Rendering::Mesh*     GetMesh() const;
                GameEngine::Rendering::Material* GetMaterial() override;
                void                             OnBeforeRender() override;
                void                             OnDraw() override;
                void                             OnBeforeDraw() override;
                void                             OnStart() override;

                bool GetVisible() const { return _visible; }
                void SetVisible(const bool value) { _visible = value; }
        };
    }
}
