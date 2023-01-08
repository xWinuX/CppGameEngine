#pragma once
#include "Material.h"
#include "Mesh.h"
#include "Renderable.h"
#include "VertexArrayObject.h"

namespace GameEngine
{
    namespace Rendering
    {
        class RenderableMeshPrimitive  : public Renderable
        {
            protected:
                Mesh::Primitive    _primitive;
                Material*          _material;
                VertexArrayObject* _vertexArrayObject;

            public:
                explicit RenderableMeshPrimitive(GameEngine::Rendering::Mesh::Primitive primitive, GameEngine::Rendering::Material* material =nullptr);
                ~RenderableMeshPrimitive() override;
                void      OnDraw() override;
                Material* GetMaterial() override;
                void SetMaterial(Material* material);
        };
    }
}
