#include "GameEngine/Rendering/Renderer.h"

#include <complex.h>
#include <numeric>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GameEngine/Window.h"
#include "GameEngine/Rendering/IndexBuffer.h"
#include "GameEngine/Rendering/Material.h"
#include "GameEngine/Rendering/Sprite.h"
#include "GameEngine/Rendering/VertexArrayObject.h"
#include "GameEngine/Rendering/VertexBuffer.h"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

std::vector<ShaderUseCallback*> Renderer::_shaderUseCallbacks = std::vector<ShaderUseCallback*>();
std::vector<RenderTarget*>      Renderer::_renderTargets      = std::vector<RenderTarget*>();

const size_t   Renderer::Renderable2DBatchMaxQuads = 10000;
const size_t   Renderer::Renderable2DBatchMaxSize  = Renderable2DBatchMaxQuads * sizeof(Sprite::QuadData);
unsigned char* Renderer::_renderable2DVertexData   = new unsigned char[Renderable2DBatchMaxSize];

IndexBuffer*       Renderer::_renderable2DIndexBuffer       = nullptr;
VertexBuffer*      Renderer::_renderable2DVertexBuffer      = nullptr;
VertexArrayObject* Renderer::_renderable2DVertexArrayObject = nullptr;

std::vector<Light*> Renderer::_lights = std::vector<Light*>();

std::map<Material*, std::vector<Renderable*>> Renderer::_opaqueRenderables      = std::map<Material*, std::vector<Renderable*>>();
std::map<Material*, std::vector<Renderable*>> Renderer::_transparentRenderables = std::map<Material*, std::vector<Renderable*>>();

std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>> Renderer::_opaqueBatchRenderable2Ds = std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>>();

void Renderer::Initialize()
{
    glDepthRange(0.0, 1.0);
    glLineWidth(2);
    glEnable(GL_CULL_FACE);

    unsigned short* indices = new unsigned short[6]{2, 1, 0, 1, 2, 3};

    _renderable2DIndexBuffer = new IndexBuffer(reinterpret_cast<unsigned char*>(indices), sizeof(unsigned short), 6);

    _renderable2DVertexBuffer      = new VertexBuffer(nullptr, sizeof(Sprite::QuadData), Renderable2DBatchMaxQuads, GL_DYNAMIC_DRAW);
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

void Renderer::SubmitShaderUseCallback(ShaderUseCallback* shaderUseCallback) { _shaderUseCallbacks.push_back(shaderUseCallback); }

void Renderer::SubmitLight(Light* light)
{
    _lights.push_back(light);
    _shaderUseCallbacks.push_back(light);
}

void Renderer::SubmitBatchRenderable2D(Renderable2D* renderable2D)
{
    if (_opaqueBatchRenderable2Ds[renderable2D->GetMaterial()][renderable2D->GetTexture()].empty())
    {
        _opaqueBatchRenderable2Ds[renderable2D->GetMaterial()][renderable2D->GetTexture()].reserve(50000);
    }
    _opaqueBatchRenderable2Ds[renderable2D->GetMaterial()][renderable2D->GetTexture()].push_back(renderable2D);
}

void Renderer::SubmitRenderable(Renderable* renderable)
{
    if (renderable->GetMaterial()->GetTransparent()) { _transparentRenderables[renderable->GetMaterial()].push_back(renderable); }
    else { _opaqueRenderables[renderable->GetMaterial()].push_back(renderable); }
}

void Renderer::SubmitRenderTarget(RenderTarget* renderTarget)
{
    _renderTargets.push_back(renderTarget);
    _shaderUseCallbacks.push_back(renderTarget);
}

unsigned int Renderer::Render2DBatches(const std::pair<Material*, std::map<Texture*, std::vector<Renderable2D*>>>& materialPair)
{
    int numDrawCalls = 0;
    _renderable2DVertexArrayObject->Bind();
    const Material* material = materialPair.first;
    for (const std::pair<Texture* const, std::vector<Renderable2D*>>& texturePair : materialPair.second)
    {
        unsigned int               renderable2DIndex = 0;
        std::vector<Renderable2D*> renderable2Ds     = texturePair.second;

        // Loop until all renderables have been rendered
        while (renderable2DIndex < renderable2Ds.size())
        {
            size_t offset   = 0;
            size_t numQuads = 0;

            // Loop trough as many renderables until the buffer is full
            while (renderable2DIndex < renderable2Ds.size())
            {
                Renderable2D* renderable2D = renderable2Ds[renderable2DIndex];
                const size_t  copySize     = renderable2D->GetCopySize();

                if (offset + copySize > Renderable2DBatchMaxSize) { break; }

                renderable2D->CopyQuadData(_renderable2DVertexData + offset);
                offset += copySize;
                numQuads += copySize / renderable2D->GetQuadSize();

                renderable2DIndex++;
            }

            // Render the batch
            _renderable2DVertexBuffer->UpdateData(_renderable2DVertexData, numQuads);
            material->GetUniformStorage()->SetSamplerUniformInstantly<Texture*>("u_Texture", texturePair.first);
            _renderable2DVertexArrayObject->RenderInstanced(6, static_cast<int>(numQuads));
            numDrawCalls++;
        }
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


void Renderer::RenderSubmitted()
{
    unsigned int numDrawCalls = 0;

    for (RenderTarget* renderTarget : _renderTargets)
    {
        renderTarget->Bind();

        // Clear TODO: Abstract this away
        glClearColor(0.05f, 0.15f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glDepthFunc(GL_LESS);

        // Opaque
        numDrawCalls += RenderRenderables<std::vector<Renderable*>, &RenderDefault>(renderTarget, _opaqueRenderables);

        // Opaque 2D
        numDrawCalls += RenderRenderables<std::map<Texture*, std::vector<Renderable2D*>>, &Render2DBatches>(renderTarget, _opaqueBatchRenderable2Ds);

        // Transparent
        // TODO: Sort triangles and objects based on distance to camera
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        numDrawCalls += RenderRenderables<std::vector<Renderable*>, &RenderDefault>(renderTarget, _transparentRenderables);
        glDisable(GL_BLEND);

        glDisable(GL_DEPTH_TEST);
        renderTarget->Unbind();
        glEnable(GL_DEPTH_TEST);
    }


    // Cleanup lights
    _lights.clear();

    // Cleanup render target
    _renderTargets.clear();

    // Cleanup renderables
    _opaqueRenderables.clear();
    _opaqueBatchRenderable2Ds.clear();
    _transparentRenderables.clear();

    // Clear callbacks
    _shaderUseCallbacks.clear();
}

void Renderer::DrawFrame() { glfwSwapBuffers(Window::GetCurrentWindow()->GetGlWindow()); }
