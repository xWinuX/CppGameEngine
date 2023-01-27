#include "GameEngine/Rendering/Renderer.h"

#include <numeric>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "GameEngine/Window.h"
#include "GameEngine/Rendering/IndexBuffer.h"
#include "GameEngine/Rendering/Material.h"
#include "GameEngine/Rendering/Sprite.h"
#include "GameEngine/Rendering/VertexArrayObject.h"
#include "GameEngine/Rendering/VertexBuffer.h"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

unsigned char*     Renderer::_renderable2DVertexData        = new unsigned char[10000 * sizeof(Sprite::QuadData)];
IndexBuffer*       Renderer::_renderable2DIndexBuffer       = nullptr;
VertexBuffer*      Renderer::_renderable2DVertexBuffer      = nullptr;
VertexArrayObject* Renderer::_renderable2DVertexArrayObject = nullptr;

std::vector<Light*> Renderer::_lights = std::vector<Light*>();

std::map<Material*, std::vector<Renderable*>> Renderer::_opaqueRenderables      = std::map<Material*, std::vector<Renderable*>>();
std::map<Material*, std::vector<Renderable*>> Renderer::_transparentRenderables = std::map<Material*, std::vector<Renderable*>>();

std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>> Renderer::_opaqueRenderable2Ds = std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>>();

glm::vec3 Renderer::_viewPosition     = glm::zero<glm::vec3>();
glm::mat4 Renderer::_projectionMatrix = glm::identity<glm::mat4>();
glm::mat4 Renderer::_viewMatrix       = glm::identity<glm::mat4>();

void Renderer::Initialize()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthRange(0.0, 1.0);
    glLineWidth(2);
    glEnable(GL_CULL_FACE);


    unsigned short* indices = new unsigned short[6]{2, 1, 0, 1, 2, 3};


    _renderable2DIndexBuffer = new IndexBuffer(reinterpret_cast<unsigned char*>(indices), sizeof(unsigned short), 6);

    _renderable2DVertexBuffer      = new VertexBuffer(nullptr, sizeof(Sprite::QuadData), 10000, GL_DYNAMIC_DRAW);
    _renderable2DVertexArrayObject = new VertexArrayObject(_renderable2DVertexBuffer, _renderable2DIndexBuffer, new VertexBufferLayout(new VertexBufferAttribute[12]
                                                           {
                                                               // Transform
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), nullptr, 1),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(4 * sizeof(float)), 1),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(8 * sizeof(float)), 1),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(12 * sizeof(float)), 1),

                                                               // Position and Uv's
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(16 * sizeof(float)), 1),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(20 * sizeof(float)), 1),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(24 * sizeof(float)), 1),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(28 * sizeof(float)), 1),

                                                               // Color
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(32 * sizeof(float)), 1),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(36 * sizeof(float)), 1),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(40 * sizeof(float)), 1),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(44 * sizeof(float)), 1),
                                                           }, 12));

    delete[] indices;
}

void Renderer::SubmitLight(Light* light) { _lights.push_back(light); }

void Renderer::SubmitRenderable2D(Renderable2D* renderable2D)
{
    if (_opaqueRenderable2Ds[renderable2D->GetMaterial()][renderable2D->GetTexture()].empty())
    {
        _opaqueRenderable2Ds[renderable2D->GetMaterial()][renderable2D->GetTexture()].reserve(10000);
    }
    _opaqueRenderable2Ds[renderable2D->GetMaterial()][renderable2D->GetTexture()].push_back(renderable2D);
}

void Renderer::SubmitRenderable(Renderable* renderable)
{
    if (renderable->GetMaterial()->GetTransparent()) { _transparentRenderables[renderable->GetMaterial()].push_back(renderable); }
    else { _opaqueRenderables[renderable->GetMaterial()].push_back(renderable); }
}

void Renderer::SetProjectionMatrix(const glm::mat4 projectionMatrix) { _projectionMatrix = projectionMatrix; }

void Renderer::SetViewMatrix(const glm::mat4 viewMatrix) { _viewMatrix = viewMatrix; }
void Renderer::SetViewPosition(const glm::vec3 viewPosition) { _viewPosition = viewPosition; }

unsigned int Renderer::Render2DBatches(const std::pair<Material* , std::map<Texture*, std::vector<Renderable2D*>>>& materialPair) {
    int numDrawCalls = 0;
    _renderable2DVertexArrayObject->Bind();
    const Material* material = materialPair.first;
    for (const std::pair<Texture* const, std::vector<Renderable2D*>>& texturePair : materialPair.second)
    {
        size_t offset   = 0;
        size_t numQuads = 0;
        for (Renderable2D* renderable2D : texturePair.second)
        {
            renderable2D->CopyQuadData(_renderable2DVertexData + offset);
            offset += renderable2D->GetCopySize();
            numQuads += renderable2D->GetCopySize() / renderable2D->GetQuadSize();
        }
        
        _renderable2DVertexBuffer->UpdateData(_renderable2DVertexData, numQuads);
        material->GetUniformBuffer()->SetUniformInstant<Texture*>("u_Texture", texturePair.first);
        _renderable2DVertexArrayObject->RenderInstanced(6, static_cast<int>(numQuads));
        numDrawCalls++;
    }
    _renderable2DVertexArrayObject->Unbind();
    return numDrawCalls;
}

unsigned int Renderer::RenderDefault(const std::pair<Material*, std::vector<Renderable*>>& materialRenderables)
{
    unsigned int numDrawCalls = 0;
    for (Renderable* renderable : materialRenderables.second)
    {
        renderable->OnBeforeDraw();
        renderable->OnDraw();

        numDrawCalls++;
    }

    return numDrawCalls;
}


void Renderer::Draw()
{
    // Clear TODO: Abstract this away
    glClearColor(0.05f, 0.15f, 0.3f, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    unsigned int numDrawCalls = 0;

    // Opaque
    numDrawCalls += RenderRenderables<std::vector<Renderable*>, &RenderDefault>(_opaqueRenderables);

    // Opaque 2D
    numDrawCalls += RenderRenderables<std::map<Texture*, std::vector<Renderable2D*>>, &Render2DBatches>(_opaqueRenderable2Ds);

    // Transparent
    // TODO: Sort triangles and objects based on distance to camera
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    numDrawCalls += RenderRenderables<std::vector<Renderable*>, &RenderDefault>(_transparentRenderables);
    glDisable(GL_BLEND);

    Debug::Log::Message("Draw Calls: " + std::to_string(numDrawCalls));

    glfwSwapBuffers(Window::GetCurrentWindow()->GetGlWindow());

    // Cleanup lights
    for (Light* light : _lights) { light->OnFrameEnd(); }
    _lights.clear();

    // Cleanup renderables
    _opaqueRenderables.clear();
    _opaqueRenderable2Ds.clear();
    _transparentRenderables.clear();
}
