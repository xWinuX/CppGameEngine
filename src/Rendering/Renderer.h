#pragma once
#include <map>
#include "Material.h"
#include "Renderable.h"
#include "../Components/Light.h"

class Renderer
{
    private:
        static std::vector<Light*> _lights;
        static std::map<Material*, std::vector<Renderable*>> _renderables;
        static glm::mat4 _viewMatrix;
        static glm::mat4 _projectionMatrix;
    public:
        static void Initialize();
        static void SubmitLight(Light* light);
        static void SubmitRenderable(Renderable* renderable);
        static void SetProjectionMatrix(glm::mat4 projectionMatrix);
        static void SetViewMatrix(glm::mat4 viewMatrix);
        static void Draw();
};
