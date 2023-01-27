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
    reactphysics3d::PhysicsWorld* physicsWorld = PhysicsManager::GetPhysicsWorld();
    physicsWorld->setIsDebugRenderingEnabled(enable);
    physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_AABB, enable);
    physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, enable);
    physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, enable);
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
    const unsigned int                  numTriangles  = debugRenderer.getNbTriangles();

    // Don't render if there aren't any triangles
    if (numTriangles == 0) { return; }

    const reactphysics3d::DebugRenderer::DebugTriangle* triangles = const_cast<reactphysics3d::DebugRenderer::DebugTriangle*>(debugRenderer.getTrianglesArray());

    const unsigned int numVertices    = std::min(numTriangles * 3, _maxVertices);
    const unsigned int numIndices     = numVertices;
    const unsigned int numVertexBytes = numVertices * _vertexSize;

    _vertexArrayObject->Bind();

    // Update VertexBuffer
    memcpy(_vertices, triangles, numVertexBytes);
    _vertexBuffer->UpdateData(_vertices, numVertices);

    // Update IndexBuffer
    for (unsigned int i = 0; i < numIndices; i++) { _indices[i] = i; }
    _indexBuffer->UpdateData(reinterpret_cast<unsigned char*>(_indices), numIndices);

    // Submit for rendering
    Renderer::SubmitRenderable(this);
    
    _vertexArrayObject->Unbind();
}

void PhysicsDebugRenderer::OnDraw()
{
    _vertexArrayObject->Bind();
    _vertexArrayObject->Render();
}

GameEngine::Rendering::Material* PhysicsDebugRenderer::GetMaterial() { return _material; }

void PhysicsDebugRenderer::SetMaterial(GameEngine::Rendering::Material* material) { _material = material; }
