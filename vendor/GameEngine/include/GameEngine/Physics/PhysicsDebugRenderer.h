#pragma once
#include "PhysicsManager.h"
#include "../Components/MeshRenderer.h"
#include "../Rendering/IndexBuffer.h"
#include "../Rendering/VertexBuffer.h"
#include "../Rendering/VertexBufferAttribute.h"
#include "../Rendering/VertexBufferLayout.h"
#include "../Rendering/VertexArrayObject.h"
#include "reactphysics3d/utils/DebugRenderer.h"

namespace GameEngine
{
    namespace Physics
    {
        class PhysicsDebugRenderer final : public Rendering::Renderable
        {
            private:
                const size_t _vertexSize  = sizeof(reactphysics3d::DebugRenderer::DebugTriangle) / 3;
                const size_t _maxVertices = 200000;

                Rendering::VertexBuffer*          _vertexBuffer           = new Rendering::VertexBuffer(nullptr, _vertexSize, _maxVertices, GL_DYNAMIC_DRAW);
                Rendering::IndexBuffer*           _indexBuffer            = new Rendering::IndexBuffer(nullptr, sizeof(unsigned int), _maxVertices, GL_DYNAMIC_DRAW);
                Rendering::VertexBufferAttribute* _vertexBufferAttributes = new Rendering::VertexBufferAttribute[2]
                {
                    Rendering::VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(_vertexSize), nullptr),
                    Rendering::VertexBufferAttribute(1, GL_UNSIGNED_INT, GL_FALSE, static_cast<GLsizei>(_vertexSize), reinterpret_cast<GLvoid*>(3 * sizeof(float))),
                };
                Rendering::VertexBufferLayout* _vertexBufferLayout = new Rendering::VertexBufferLayout(_vertexBufferAttributes, 2);
                Rendering::VertexArrayObject*  _vertexArrayObject  = new Rendering::VertexArrayObject(_vertexBuffer, _indexBuffer, _vertexBufferLayout);

                unsigned char* _vertices = new unsigned char[_maxVertices * _vertexSize];
                unsigned int*  _indices  = new unsigned int[_maxVertices];

                Rendering::Material* _material = nullptr;

            public:
                static void EnableDebugRenderer(bool enable);
                PhysicsDebugRenderer();
                ~PhysicsDebugRenderer() override;

                void Render();

                void                 OnDraw() override;
                Rendering::Material* GetMaterial() override;

                void SetMaterial(Rendering::Material* material);
        };
    }
}
