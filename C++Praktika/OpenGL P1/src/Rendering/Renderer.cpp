#include "Renderer.h"

std::map<Material*, std::vector<Renderable*>> Renderer::_renderables = std::map<Material*, std::vector<Renderable*>>();

void Renderer::Submit(Renderable* renderable)
{
    _renderables[renderable->GetMaterial()].push_back(renderable);
}

void Renderer::Draw()
{
    /*
    int           offset = 0;
    const Shader* shader = nullptr;
    for (const auto& renderable : _renderables)
    {
        // Choose if new shader should get activated
        const Shader* newShader = renderable.first->GetShader();
        if (shader == nullptr || shader != newShader)
        {
            shader = newShader;
            shader->Use();
        }

        // Apply material unique uniforms
        renderable.first->ApplyUniforms();
        //shader->SetUniformMat4F()

        // Actually draw the elements
        //glDrawElements(GL_TRIANGLES, indicesBatchMap.second, GL_UNSIGNED_BYTE, (void*)offset);
        //offset += indicesBatchMap.second;
    }*/
}
