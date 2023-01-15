#pragma once
#include <map>
#include "Material.h"
#include "Renderable.h"
#include "Sprite.h"
#include "VertexArrayObject.h"
#include "../Components/Light.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderer
        {
            private:
                static std::vector<GameEngine::Components::Light*>   _lights;
                static std::map<Material*, std::vector<Renderable*>> _opaqueRenderables;
                static std::map<Material*, std::vector<Renderable*>> _transparentRenderables;
                static glm::mat4                                     _viewMatrix;
                static glm::mat4                                     _projectionMatrix;
            public:
                static void Initialize();
                static void SubmitLight(GameEngine::Components::Light* light);
                static void SubmitSprite(Sprite* sprite);
                static void SubmitRenderable(Renderable* renderable);
                static void SetProjectionMatrix(glm::mat4 projectionMatrix);
                static void SetViewMatrix(glm::mat4 viewMatrix);
                static unsigned int RenderRenderables(const std::map<Material*, std::vector<Renderable*>>& map);
                static void Draw();
        };
    }
}
