#pragma once
#include <map>
#include "Material.h"
#include "Renderable.h"

class Renderer
{
    private:
        static std::map<Material*, std::vector<Renderable*>> _renderables;
        static glm::mat4 _viewMatrix;
        static glm::mat4 _projectionMatrix;
    public:
        static void Submit(Renderable* renderable);
        static void SetProjectionMatrix(glm::mat4 projectionMatrix);
        static void SetViewMatrix(glm::mat4 viewMatrix);
        static void Draw();
};
