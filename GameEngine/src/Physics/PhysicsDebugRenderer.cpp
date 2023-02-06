#include "GameEngine/Physics/PhysicsDebugRenderer.h"

#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Physics;
using namespace GameEngine::Rendering;

PhysicsDebugRenderer::PhysicsDebugRenderer() { EnableDebugRenderer(true); }

PhysicsDebugRenderer::~PhysicsDebugRenderer()
{
    EnableDebugRenderer(false);

    delete _indexBuffer;
    delete[] _indices;
    delete _vertexBuffer;
    delete[] _vertices;
    delete _vertexBufferLayout; // Will delete _vertexBufferAttributes
    delete _vertexArrayObject;
}

void PhysicsDebugRenderer::EnableDebugRenderer(const bool enable)
{
    Debug::Log::Message("Enable Debug");
    reactphysics3d::PhysicsWorld* physicsWorld = PhysicsManager::GetPhysicsWorld();
    physicsWorld->setIsDebugRenderingEnabled(enable);
    physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_AABB, enable);
    physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, enable);
    physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, enable);
    Debug::Log::Message("End enable debug");
}

void PhysicsDebugRenderer::Render()
{
    // Can only render with material
    if (_material == nullptr)
    {
        Debug::Log::Error("Please assign a material to the PhysicsDebugRenderer");
        return;
    }

    const reactphysics3d::DebugRenderer debugRenderer = PhysicsManager::GetPhysicsWorld()->getDebugRenderer();
    const size_t                        numTriangles  = debugRenderer.getNbTriangles();

    Debug::Log::Message("num Debug triangles: " + std::to_string(numTriangles));

    // Don't render if there aren't any triangles
    if (numTriangles == 0) { return; }

    const size_t numVertices    = std::min(numTriangles * 3, _maxVertices);
    const size_t numIndices     = std::min(numVertices, _maxVertices);
    const size_t numVertexBytes = numVertices * _vertexSize;

    _vertexArrayObject->Bind();

    // Update VertexBuffer
    memcpy(_vertices, debugRenderer.getTrianglesArray(), numVertexBytes);
    _vertexBuffer->UpdateData(_vertices, numVertices);

    // Update IndexBuffer
    for (size_t i = 0; i < numIndices; i++) { _indices[i] = static_cast<unsigned int>(i); }
    _indexBuffer->UpdateData(reinterpret_cast<unsigned char*>(_indices), numIndices);

    // Submit for rendering
    Renderer::SubmitRenderable(this);

    _vertexArrayObject->Unbind();
}

void PhysicsDebugRenderer::OnDraw()
{
    Debug::Log::Message("Before debug render");
    _vertexArrayObject->Bind();
    Debug::Log::Message("after bind");
    _vertexArrayObject->Render();
    Debug::Log::Message("After debug render");
}

GameEngine::Rendering::Material* PhysicsDebugRenderer::GetMaterial() { return _material; }

void PhysicsDebugRenderer::SetMaterial(GameEngine::Rendering::Material* material) { _material = material; }
