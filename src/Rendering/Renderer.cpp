#include "Renderer.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include "../Application.h"

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

void Renderer::Submit(Renderable* renderable)
{
    std::cout << "submit" << std::endl;
    _renderables[renderable->GetMaterial()].push_back(renderable);
}

void Renderer::SetProjectionMatrix(const glm::mat4 projectionMatrix) { _projectionMatrix = projectionMatrix; }

void Renderer::SetViewMatrix(const glm::mat4 viewMatrix) { _viewMatrix = viewMatrix; }

void Renderer::Draw()
{
    // Clear
    glClearColor(0.05f, 0.15f, 0.3f, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    const Shader* shader = nullptr;
    
    for (const auto& materialRenderables : _renderables)
    {
        const Material* material = materialRenderables.first;
        
        // Choose if new shader should get activated
        const Shader* newShader = material->GetShader();
        if (shader == nullptr || shader != newShader)
        {
            shader = newShader;
            shader->Use();

        }

        // Apply material unique uniforms
        material->GetUniformBuffer()->Apply();
        material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_ViewProjection", _projectionMatrix*_viewMatrix);

        // Actually draw the elements
        for (Renderable* renderable : materialRenderables.second)
        {
            material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_Transform", renderable->GetTransform()->GetTRS());

            renderable->GetVertexArrayObject()->Bind();
            
            glDrawElements(GL_TRIANGLES, renderable->GetVertexArrayObject()->GetIndexBuffer()->GetNumIndices(), GL_UNSIGNED_INT, static_cast<void*>(nullptr));
        }
    }

    glfwSwapBuffers(Application::GetWindow().GetGlWindow());
}
