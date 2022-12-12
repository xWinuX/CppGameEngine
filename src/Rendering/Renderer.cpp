#include "Renderer.h"

std::map<Material*, std::vector<Renderable*>> Renderer::_renderables      = std::map<Material*, std::vector<Renderable*>>();
glm::mat4                                     Renderer::_projectionMatrix = glm::identity<glm::mat4>();
glm::mat4                                     Renderer::_viewMatrix       = glm::identity<glm::mat4>();

void Renderer::Initialize()
{
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
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
        // Choose if new shader should get activated
        const Shader* newShader = materialRenderables.first->GetShader();
        if (shader == nullptr || shader != newShader)
        {
            shader = newShader;
            shader->Use();
            shader->SetViewProjectionMatrix(_projectionMatrix*_viewMatrix);
        }

        // Apply material unique uniforms
        materialRenderables.first->ApplyUniforms();

        // Actually draw the elements
        for (Renderable* renderable : materialRenderables.second)
        {
            shader->SetTransformMatrix(renderable->GetTransform()->GetTRS());
            
            renderable->GetVertexArrayObject()->Bind();
            
            glDrawElements(GL_TRIANGLES, renderable->GetVertexArrayObject()->GetIndexBuffer()->GetNumIndices(), GL_UNSIGNED_BYTE, static_cast<void*>(nullptr));
        }
    }
}
