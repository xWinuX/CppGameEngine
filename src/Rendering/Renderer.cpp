#include "Renderer.h"

#include <GLFW/glfw3.h>

#include "Shader.h"
#include "../Application.h"
#include "glm/ext/matrix_transform.hpp"

std::vector<Light*>                           Renderer::_lights           = std::vector<Light*>();
std::map<Material*, std::vector<Renderable*>> Renderer::_renderables      = std::map<Material*, std::vector<Renderable*>>();
glm::mat4                                     Renderer::_projectionMatrix = glm::identity<glm::mat4>();
glm::mat4                                     Renderer::_viewMatrix       = glm::identity<glm::mat4>();

void Renderer::Initialize()
{
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0, 1.0);
}

void Renderer::SubmitLight(Light* light) { _lights.push_back(light); }

void Renderer::SubmitRenderable(Renderable* renderable) { _renderables[renderable->GetMaterial()].push_back(renderable); }

void Renderer::SetProjectionMatrix(const glm::mat4 projectionMatrix) { _projectionMatrix = projectionMatrix; }

void Renderer::SetViewMatrix(const glm::mat4 viewMatrix) { _viewMatrix = viewMatrix; }

void Renderer::Draw()
{
    // Clear
    glClearColor(0.05f, 0.15f, 0.3f, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Shader* shader = nullptr;

    unsigned int numDrawCalls = 0;
    for (const auto& materialRenderables : _renderables)
    {
        const Material* material = materialRenderables.first;

        // Choose if new shader should get activated
        const Shader* newShader = material->GetShader();
        if (shader == nullptr || shader != newShader)
        {
            shader = newShader;
            shader->Use();

            for (Light*& light : _lights) { light->OnShaderUse(); }

            // TODO: Somehow abstract this away
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
    }

    Debug::Log::Message("Draw Calls: " + std::to_string(numDrawCalls));

    glfwSwapBuffers(Application::GetWindow().GetGlWindow());

    // Cleanup lights
    for (Light* light : _lights) { light->OnFrameEnd(); }
    _lights.clear();

    // Cleanup renderables
    _renderables.clear();
}
