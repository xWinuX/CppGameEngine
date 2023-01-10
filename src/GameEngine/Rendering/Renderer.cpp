#include "Renderer.h"

#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexArrayObject.h"
#include "../Core/Window.h"
#include "../Utils/Time.h"
#include "glm/ext/matrix_transform.hpp"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;


std::vector<Light*>                           Renderer::_lights                 = std::vector<Light*>();
std::map<Material*, std::vector<Renderable*>> Renderer::_opaqueRenderables      = std::map<Material*, std::vector<Renderable*>>();
std::map<Material*, std::vector<Renderable*>> Renderer::_transparentRenderables = std::map<Material*, std::vector<Renderable*>>();
glm::mat4                                     Renderer::_projectionMatrix       = glm::identity<glm::mat4>();
glm::mat4                                     Renderer::_viewMatrix             = glm::identity<glm::mat4>();

void Renderer::Initialize()
{
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0, 1.0);
    glLineWidth(2);
    glEnable(GL_CULL_FACE);
}

void Renderer::SubmitLight(Light* light) { _lights.push_back(light); }

void Renderer::SubmitRenderable(Renderable* renderable)
{
    if (renderable->GetMaterial()->GetTransparent()) { _transparentRenderables[renderable->GetMaterial()].push_back(renderable); }
    else { _opaqueRenderables[renderable->GetMaterial()].push_back(renderable); }
}

void Renderer::SetProjectionMatrix(const glm::mat4 projectionMatrix) { _projectionMatrix = projectionMatrix; }

void Renderer::SetViewMatrix(const glm::mat4 viewMatrix) { _viewMatrix = viewMatrix; }

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

        // Update polygon mode if needed
        if (cullFace != currentCullFace || renderMode != currentRenderMode || firstLoop)
        {
            glPolygonMode(material->GetCullFace(), material->GetRenderMode());
            currentCullFace   = cullFace;
            currentRenderMode = renderMode;
        }

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
    _transparentRenderables.clear();
}
