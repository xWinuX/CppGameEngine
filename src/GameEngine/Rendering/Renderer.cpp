#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <numeric>

#include "Shader.h"
#include "VertexArrayObject.h"
#include "../Core/Window.h"
#include "../Utils/Time.h"
#include "glm/ext/matrix_transform.hpp"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

unsigned char*     Renderer::_renderable2DVertexData        = new unsigned char[4000 * sizeof(Sprite::VertexData)];
IndexBuffer*       Renderer::_renderable2DIndexBuffer       = nullptr;
VertexBuffer*      Renderer::_renderable2DVertexBuffer      = nullptr;
VertexArrayObject* Renderer::_renderable2DVertexArrayObject = nullptr;

std::vector<Light*> Renderer::_lights = std::vector<Light*>();

std::map<Material*, std::vector<Renderable*>> Renderer::_opaqueRenderables      = std::map<Material*, std::vector<Renderable*>>();
std::map<Material*, std::vector<Renderable*>> Renderer::_transparentRenderables = std::map<Material*, std::vector<Renderable*>>();

std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>> Renderer::_opaqueRenderable2Ds = std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>>();

glm::mat4 Renderer::_projectionMatrix = glm::identity<glm::mat4>();
glm::mat4 Renderer::_viewMatrix       = glm::identity<glm::mat4>();

void Renderer::Initialize()
{
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0, 1.0);
    glLineWidth(2);
    glEnable(GL_CULL_FACE);

    unsigned short* indices = new unsigned short[6000];
    for (unsigned short i = 0; i < 1000; i++)
    {
        indices[(i*6)] = i*4 + 2;
        indices[(i*6)+1] = i*4 + 1;
        indices[(i*6)+2] = i*4;
        indices[(i*6)+3] = i*4 + 1;
        indices[(i*6)+4] = i*4 + 2;
        indices[(i*6)+5] = i*4 + 3;
    }
    _renderable2DIndexBuffer       = new IndexBuffer(reinterpret_cast<unsigned char*>(indices), sizeof(unsigned short), 6000);
    _renderable2DVertexBuffer      = new VertexBuffer(nullptr, sizeof(Sprite::VertexData), 4000, GL_DYNAMIC_DRAW);
    _renderable2DVertexArrayObject = new VertexArrayObject(_renderable2DVertexBuffer, _renderable2DIndexBuffer, new VertexBufferLayout(new VertexBufferAttribute[4]
                                                           {
                                                               VertexBufferAttribute(1, GL_FLOAT, GL_FALSE, sizeof(Sprite::VertexData), nullptr),
                                                               VertexBufferAttribute(1, GL_FLOAT, GL_FALSE, sizeof(Sprite::VertexData), (GLvoid*)(1 * sizeof(float))),
                                                               VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Sprite::VertexData), (GLvoid*)(2 * sizeof(float))),
                                                               VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::VertexData), (GLvoid*)(4 * sizeof(float))),
                                                           }, 4));
}

void Renderer::SubmitLight(Light* light) { _lights.push_back(light); }

void Renderer::SubmitRenderable2D(Renderable2D* renderable2D) { _opaqueRenderable2Ds[renderable2D->GetMaterial()][renderable2D->GetTexture()].push_back(renderable2D); }

void Renderer::SubmitRenderable(Renderable* renderable)
{
    if (renderable->GetMaterial()->GetTransparent()) { _transparentRenderables[renderable->GetMaterial()].push_back(renderable); }
    else { _opaqueRenderables[renderable->GetMaterial()].push_back(renderable); }
}

void Renderer::SetProjectionMatrix(const glm::mat4 projectionMatrix) { _projectionMatrix = projectionMatrix; }

void Renderer::SetViewMatrix(const glm::mat4 viewMatrix) { _viewMatrix = viewMatrix; }

unsigned int Renderer::RenderRenderable2D(const std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>>& map)
{
    unsigned int         numDrawCalls      = 0;
    const Shader*        shader            = nullptr;
    Material::CullFace   currentCullFace   = Material::CullFace::Back;
    Material::RenderMode currentRenderMode = Material::RenderMode::Fill;
    bool                 firstLoop         = true;

    for (const std::pair<Material* const, std::map<Texture*, std::vector<Renderable2D*>>>& materialPair : map)
    {
        const Material*            material   = materialPair.first;
        const Material::CullFace   cullFace   = material->GetCullFace();
        const Material::RenderMode renderMode = material->GetRenderMode();

        // Choose if new shader should get activated
        const Shader* newShader = material->GetShader();
        if (shader == nullptr || shader != newShader)
        {
            shader = newShader;
            shader->Use();

            for (Light*& light : _lights) { light->OnShaderUse(); }

            // TODO: Somehow abstract this away
            material->GetUniformBuffer()->SetUniformInstant<float>("u_Time", Time::GetTimeSinceStart());
            material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_ViewProjection", _projectionMatrix * _viewMatrix);
        }

        // Update polygon mode if needed
        if (renderMode != currentRenderMode || firstLoop)
        {
            glPolygonMode(GL_FRONT_AND_BACK, material->GetRenderMode());
            currentRenderMode = renderMode;
        }

        // Face Culling
        if (cullFace != currentCullFace || firstLoop)
        {
            if (cullFace == Material::CullFace::None)
            {
                glDisable(GL_CULL_FACE);
                glCullFace(GL_BACK);
            }
            else
            {
                glEnable(GL_CULL_FACE);
                glCullFace(cullFace);
            }

            currentCullFace = cullFace;
        }

        // Apply material uniforms that are in the queue
        material->GetUniformBuffer()->Apply();

        // Actually draw the elements
        _renderable2DVertexArrayObject->Bind();
        for (const std::pair<Texture* const, std::vector<Renderable2D*>>& texturePair : materialPair.second)
        {
            unsigned int offset = 0;
            for (Renderable2D* renderable2D : texturePair.second)
            {
                renderable2D->CopyQuadData(_renderable2DVertexData+offset, 0, 1);
                offset += sizeof(Sprite::VertexData)*4;
            }
            
            _renderable2DVertexBuffer->UpdateData(_renderable2DVertexData, texturePair.second.size()*4);
            material->GetUniformBuffer()->SetUniform<Texture*>("u_Texture", texturePair.first); 
            _renderable2DVertexArrayObject->Render(texturePair.second.size()*6, 0);
            numDrawCalls++;
        }
        _renderable2DVertexArrayObject->Unbind();


        firstLoop = false;
    }

    return numDrawCalls;
}

unsigned int Renderer::RenderRenderables(const std::map<Material*, std::vector<Renderable*>>& map)
{
    unsigned int         numDrawCalls      = 0;
    const Shader*        shader            = nullptr;
    Material::CullFace   currentCullFace   = Material::CullFace::Back;
    Material::RenderMode currentRenderMode = Material::RenderMode::Fill;
    bool                 firstLoop         = true;

    for (const std::pair<Material* const, std::vector<Renderable*>>& materialRenderables : map)
    {
        const Material*            material   = materialRenderables.first;
        const Material::CullFace   cullFace   = material->GetCullFace();
        const Material::RenderMode renderMode = material->GetRenderMode();

        // Choose if new shader should get activated
        const Shader* newShader = material->GetShader();
        if (shader == nullptr || shader != newShader)
        {
            shader = newShader;
            shader->Use();

            for (Light*& light : _lights) { light->OnShaderUse(); }

            // TODO: Somehow abstract this away
            material->GetUniformBuffer()->SetUniformInstant<float>("u_Time", Time::GetTimeSinceStart());
            material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_ViewProjection", _projectionMatrix * _viewMatrix);
        }

        // Update polygon mode if needed
        if (renderMode != currentRenderMode || firstLoop)
        {
            glPolygonMode(GL_FRONT_AND_BACK, material->GetRenderMode());
            currentRenderMode = renderMode;
        }

        // Face Culling
        if (cullFace != currentCullFace || firstLoop)
        {
            if (cullFace == Material::CullFace::None)
            {
                glDisable(GL_CULL_FACE);
                glCullFace(GL_BACK);
            }
            else
            {
                glEnable(GL_CULL_FACE);
                glCullFace(cullFace);
            }

            currentCullFace = cullFace;
        }

        // Apply material uniforms that are in the queue
        material->GetUniformBuffer()->Apply();

        // Actually draw the elements
        for (Renderable* renderable : materialRenderables.second)
        {
            renderable->OnBeforeDraw();
            renderable->OnDraw();

            numDrawCalls++;
        }

        firstLoop = false;
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
    numDrawCalls += RenderRenderables(_opaqueRenderables);

    // Opaque 2D
    numDrawCalls += RenderRenderable2D(_opaqueRenderable2Ds);

        // Transparent
        // TODO: Sort triangles and objects based on distance to camera
        glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    numDrawCalls += RenderRenderables(_transparentRenderables);
    glDisable(GL_BLEND);

    Debug::Log::Message("Draw Calls: " + std::to_string(numDrawCalls));

    glfwSwapBuffers(Core::Window::GetCurrentWindow()->GetGlWindow());

    // Cleanup lights
    for (Light* light : _lights) { light->OnFrameEnd(); }
    _lights.clear();

    // Cleanup renderables
    for (std::pair<Material* const, std::vector<Renderable*>> materialRenderables : _opaqueRenderables) { materialRenderables.second.clear(); }
    for (std::pair<Material* const, std::vector<Renderable*>> materialRenderables : _transparentRenderables) { materialRenderables.second.clear(); }

    _opaqueRenderables.clear();
    _opaqueRenderable2Ds.clear();
    _transparentRenderables.clear();
}
