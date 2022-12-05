#include "Renderer.h"

std::map<Material*, std::vector<Renderable*>> Renderer::_renderables      = std::map<Material*, std::vector<Renderable*>>();
glm::mat4                                     Renderer::_projectionMatrix = glm::identity<glm::mat4>();
glm::mat4                                     Renderer::_viewMatrix       = glm::identity<glm::mat4>();

void Renderer::Submit(Renderable* renderable) { _renderables[renderable->GetMaterial()].push_back(renderable); }

void Renderer::SetProjectionMatrix(const glm::mat4 projectionMatrix) { _projectionMatrix = projectionMatrix; }

void Renderer::SetViewMatrix(const glm::mat4 viewMatrix) { _viewMatrix = viewMatrix; }

void Renderer::Draw()
{
    const Shader* shader = nullptr;
    for (const auto& materialRenderables : _renderables)
    {
        // Choose if new shader should get activated
        const Shader* newShader = materialRenderables.first->GetShader();
        if (shader == nullptr || shader != newShader)
        {
            shader = newShader;
            shader->Use();
            shader->SetViewProjectionMatrix(_viewMatrix * _projectionMatrix);
        }

        // Apply material unique uniforms
        materialRenderables.first->ApplyUniforms();

        // Actually draw the elements
        for (Renderable* renderable : materialRenderables.second)
        {
            renderable->GetVertexArrayObject()->Bind();
            glDrawElements(GL_TRIANGLES, renderable->GetVertexArrayObject()->GetIndexBuffer()->GetNumIndices(), GL_UNSIGNED_BYTE, static_cast<void*>(nullptr));
        }
    }
}
