#pragma once
#include "PhysicsManager.h"
#include "../Components/MeshRenderer.h"
#include "../Rendering/Buffers/IndexBuffer.h"
#include "../Rendering/Buffers/VertexBuffer.h"
#include "../Rendering/Buffers/VertexBufferAttribute.h"
#include "../Rendering/Buffers/VertexBufferLayout.h"
#include "reactphysics3d/utils/DebugRenderer.h"

namespace GameEngine
{
    namespace Physics
    {
        class PhysicsDebugRenderer final : public GameEngine::Rendering::Renderable
        {
            private:
                const unsigned int _vertexSize  = sizeof(reactphysics3d::DebugRenderer::DebugTriangle) / 3;
                const unsigned int _maxVertices = 1024 * 3;
            
                GameEngine::Rendering::VertexBuffer*          _vertexBuffer = new GameEngine::Rendering::VertexBuffer(nullptr, _vertexSize, _maxVertices, GL_DYNAMIC_DRAW);
                GameEngine::Rendering::IndexBuffer*           _indexBuffer = new GameEngine::Rendering::IndexBuffer(nullptr, GL_UNSIGNED_INT, _maxVertices, GL_DYNAMIC_DRAW);
                GameEngine::Rendering::VertexBufferAttribute* _vertexBufferAttributes = new GameEngine::Rendering::VertexBufferAttribute[2]
                {
                    GameEngine::Rendering::VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, _vertexSize, nullptr),
                    GameEngine::Rendering::VertexBufferAttribute(1, GL_UNSIGNED_INT, GL_FALSE, _vertexSize, reinterpret_cast<GLvoid*>(3 * sizeof(float))),
                };
                GameEngine::Rendering::VertexBufferLayout* _vertexBufferLayout = new GameEngine::Rendering::VertexBufferLayout(_vertexBufferAttributes, 2);
                GameEngine::Rendering::VertexArrayObject*  _vertexArrayObject  = new GameEngine::Rendering::VertexArrayObject(_vertexBuffer, _indexBuffer, _vertexBufferLayout);

                unsigned char* _vertices = new unsigned char[_maxVertices * _vertexSize];
                unsigned int*  _indices  = new unsigned int[_maxVertices];

                GameEngine::Rendering::Material* _material = nullptr;

            public:
                static void EnableDebugRenderer(bool enable);
                PhysicsDebugRenderer();
                ~PhysicsDebugRenderer() override;

                void Render();

                void                             OnDraw() override;
                GameEngine::Rendering::Material* GetMaterial() override;

                void SetMaterial(GameEngine::Rendering::Material* material);
        };
    }
}
