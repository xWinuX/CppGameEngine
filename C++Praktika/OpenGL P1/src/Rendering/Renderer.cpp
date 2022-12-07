#include "Renderer.h"

std::map<Material*, std::vector<Renderable*>> Renderer::_renderables      = std::map<Material*, std::vector<Renderable*>>();
glm::mat4                                     Renderer::_projectionMatrix = glm::identity<glm::mat4>();
glm::mat4                                     Renderer::_viewMatrix       = glm::identity<glm::mat4>();

void Renderer::Submit(Renderable* renderable)
{
    std::cout << "submit" << std::endl;
    _renderables[renderable->GetMaterial()].push_back(renderable);
}

void Renderer::SetProjectionMatrix(const glm::mat4 projectionMatrix) { _projectionMatrix = projectionMatrix; }

void Renderer::SetViewMatrix(const glm::mat4 viewMatrix) { _viewMatrix = viewMatrix; }

void Renderer::Draw()
{
    const Shader* shader = nullptr;
    
    for (const auto& materialRenderables : _renderables)
    {
        std::cout << "material loop" << std::endl;
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
        std::cout << "in material loop" << std::endl;
        for (Renderable* renderable : materialRenderables.second)
        {
            std::cout << "renderable" << std::endl;
            shader->SetTransformMatrix(renderable->GetTransform()->GetTRS());

            const VertexArrayObject* vao = renderable->GetVertexArrayObject();
            const IndexBuffer*       indexBuffer = vao->GetIndexBuffer();
            const unsigned int numIndices  = indexBuffer->GetNumIndices();
            std::cout << vao->GetVertexBuffer()->NumVertices() << std::endl;

            for (int i = 0; i < vao->GetVertexBuffer()->NumVertices(); i++)
            {
                std::cout << vao->GetVertexBuffer()->PVertices()[i].Position.x << "," << vao->GetVertexBuffer()->PVertices()[i].Position.y << "," << vao->GetVertexBuffer()->PVertices()[i].Position.z << "," << std::endl;
            }
            vao->Bind();
            
            glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_BYTE, static_cast<void*>(nullptr));


            std::cout << "aaaaa" << std::endl;
        }
    }
}
