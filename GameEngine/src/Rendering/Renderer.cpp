#include "GameEngine/Rendering/Renderer.h"

#include <numeric>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "GameEngine/Window.h"
#include "GameEngine/Rendering/IndexBuffer.h"
#include "GameEngine/Rendering/Light.h"
#include "GameEngine/Rendering/Material.h"
#include "GameEngine/Rendering/CascadedShadowMap.h"
#include "GameEngine/Rendering/Sprite.h"
#include "GameEngine/Rendering/VertexArrayObject.h"
#include "GameEngine/Rendering/VertexBuffer.h"

#define RENDER_CALL(renderStructure, call) \
for (auto pair : (renderStructure)) \
{ \
    if (!renderTarget->HasActiveLayer(pair.first)) { continue; } \
    ##call## \
}


using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

std::vector<CascadedShadowMap*>         Renderer::_shadowMaps         = std::vector<CascadedShadowMap*>();
std::vector<ShaderUseCallback*> Renderer::_shaderUseCallbacks = std::vector<ShaderUseCallback*>();
std::vector<RenderTarget*>      Renderer::_renderTargets      = std::vector<RenderTarget*>();

const size_t   Renderer::Renderable2DBatchMaxQuads = 10000;
const size_t   Renderer::Renderable2DBatchMaxSize  = Renderable2DBatchMaxQuads * sizeof(Sprite::QuadData);
unsigned char* Renderer::_renderable2DVertexData   = new unsigned char[Renderable2DBatchMaxSize];

Shader*            Renderer::_shadowShader                  = nullptr;
Shader*            Renderer::_shadowSpriteShader            = nullptr;
IndexBuffer*       Renderer::_renderable2DIndexBuffer       = nullptr;
VertexBuffer*      Renderer::_renderable2DVertexBuffer      = nullptr;
VertexArrayObject* Renderer::_renderable2DVertexArrayObject = nullptr;

Renderer::RenderableStructure Renderer::_opaqueRenderables      = Renderer::RenderableStructure();
Renderer::RenderableStructure Renderer::_transparentRenderables = Renderer::RenderableStructure();

Renderer::Renderable2DBatchStructure Renderer::_opaqueBatchRenderable2Ds      = Renderer::Renderable2DBatchStructure();
Renderer::Renderable2DBatchStructure Renderer::_transparentBatchRenderable2Ds = Renderer::Renderable2DBatchStructure();

void Renderer::Initialize()
{
    glDepthRange(0.0, 1.0);
    glLineWidth(2);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    
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

    Light::Initialize();
}

void Renderer::SetShadowShader(Shader* shadowShader) { _shadowShader = shadowShader; }
void Renderer::SetShadowSpriteShader(Shader* shadowSpriteShader) { _shadowSpriteShader = shadowSpriteShader; }

void Renderer::SubmitShadowMap(CascadedShadowMap* shadowMap) { _shadowMaps.push_back(shadowMap); }

void Renderer::SubmitShaderUseCallback(ShaderUseCallback* shaderUseCallback) { _shaderUseCallbacks.push_back(shaderUseCallback); }

void Renderer::SubmitBatchRenderable2D(Renderable2D* renderable2D)
{
    Renderable2DBatchStructure& structure = renderable2D->GetMaterial()->GetTransparent() ? _transparentBatchRenderable2Ds : _opaqueBatchRenderable2Ds;

    std::vector<Renderable2D*>& vector = structure[renderable2D->GetLayer()][renderable2D->GetMaterial()][renderable2D->GetTexture()];
    if (vector.empty()) { vector.reserve(10000); }
    vector.push_back(renderable2D);
}

void Renderer::SubmitRenderable(Renderable* renderable)
{
    RenderableStructure& structure = renderable->GetMaterial()->GetTransparent() ? _transparentRenderables : _opaqueRenderables;

    auto& vector = structure[renderable->GetLayer()][renderable->GetMaterial()];
    if (vector.empty()) { vector.reserve(1000); }
    vector.push_back(renderable);
}

void Renderer::SubmitRenderTarget(RenderTarget* renderTarget)
{
    _renderTargets.push_back(renderTarget);
    _shaderUseCallbacks.push_back(renderTarget);
}

unsigned int Renderer::Render2DBatches(const std::pair<Material*, std::map<Texture2D*, std::vector<Renderable2D*>>>& materialPair)
{
    int numDrawCalls = 0;
    _renderable2DVertexArrayObject->Bind();
    for (const std::pair<Texture2D* const, std::vector<Renderable2D*>>& texturePair : materialPair.second)
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
            Shader::GetCurrentActiveShader()->GetUniformStorage()->SetUniformInstant<Texture2D*>("u_Texture", texturePair.first);
            _renderable2DVertexArrayObject->DrawInstanced(6, static_cast<int>(numQuads));
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

glm::vec3 lightInvDir = glm::vec3(0, 5, 20);

void Renderer::RenderSubmitted()
{
    unsigned int numDrawCalls = 0;

    // Update Light
    Light::Update();
    
    for (RenderTarget* renderTarget : _renderTargets)
    {
        // Render Shadows
        if (renderTarget->_renderShadows)
        {
            glCullFace(GL_FRONT);
  
            const CascadedShadowMap* shadowMap = _shadowMaps[0];
            shadowMap->Bind();
            
            _shadowShader->Use();
            RENDER_CALL(
                        _opaqueRenderables,
                        for (auto p : pair.second) { RenderDefault(p); }
                       )

            //_shadowSpriteShader->Use();
            RENDER_CALL(
                        _opaqueBatchRenderable2Ds,
                        for (auto p : pair.second) { Render2DBatches(p); }
                       )

            shadowMap->Unbind();
         
            glCullFace(GL_BACK);
        }

        renderTarget->Bind();

        glDepthFunc(GL_LESS);

        // Opaque
        RENDER_CALL(
                    _opaqueRenderables,
                    (numDrawCalls += RenderRenderables<std::vector<Renderable*>, &RenderDefault>(renderTarget, pair.second));
                   )

        RENDER_CALL(
                    _opaqueBatchRenderable2Ds,
                    (numDrawCalls += RenderRenderables<std::map<Texture2D*, std::vector<Renderable2D*>>, &Render2DBatches>(renderTarget, pair.second));
                   )


        // Transparent
        // TODO: Sort triangles and objects based on distance to camera
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        RENDER_CALL(
                    _transparentRenderables,
                    (numDrawCalls += RenderRenderables<std::vector<Renderable*>, &RenderDefault>(renderTarget, pair.second));
                   )

        RENDER_CALL(
                    _transparentBatchRenderable2Ds,
                    (numDrawCalls += RenderRenderables<std::map<Texture2D*, std::vector<Renderable2D*>>, &Render2DBatches>(renderTarget, pair.second));
                   )
        glDisable(GL_BLEND);

        glDisable(GL_DEPTH_TEST);
        renderTarget->Unbind();
        renderTarget->Draw();
        glEnable(GL_DEPTH_TEST);
    }


    // Cleanup
    _shadowMaps.clear();
    _renderTargets.clear();
    _opaqueRenderables.clear();
    _opaqueBatchRenderable2Ds.clear();
    _transparentRenderables.clear();
    _transparentBatchRenderable2Ds.clear();
    _shaderUseCallbacks.clear();
}

void Renderer::DrawFrame() { glfwSwapBuffers(Window::GetCurrentWindow()->GetGlWindow()); }
