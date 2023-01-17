#pragma once
#include <map>
#include "Material.h"
#include "Renderable.h"
#include "Renderable2D.h"
#include "Sprite.h"
#include "../Components/Light.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderer
        {
            private:
                static std::vector<GameEngine::Components::Light*> _lights;

                // 3D
                static std::map<Material*, std::vector<Renderable*>> _opaqueRenderables;
                static std::map<Material*, std::vector<Renderable*>> _transparentRenderables;

                // 2D
                struct Batch2D
                {
                    std::vector<Renderable2D> Renderable2Ds;
                    std::vector<VertexBuffer> VertexBuffers;
                };

                static unsigned char*     _renderable2DVertexData;
                static VertexArrayObject* _renderable2DVertexArrayObject;
                static VertexBuffer*      _renderable2DVertexBuffer;
                static IndexBuffer*       _renderable2DIndexBuffer;

                static std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>> _opaqueRenderable2Ds;

                static glm::mat4 _viewMatrix;
                static glm::mat4 _projectionMatrix;

            public:
                static void         Initialize();
                static void         SubmitLight(GameEngine::Components::Light* light);
                static void         SubmitRenderable2D(Renderable2D* renderable2D);
                static void         SubmitRenderable(Renderable* renderable);
                static void         SetProjectionMatrix(glm::mat4 projectionMatrix);
                static void         SetViewMatrix(glm::mat4 viewMatrix);
                static unsigned int RenderRenderable2D(const std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>>& map);
                static unsigned int RenderRenderables(const std::map<Material*, std::vector<Renderable*>>& map);
                static void         Draw();
        };
    }
}
