﻿#pragma once
#include <functional>
#include <map>
#include "Material.h"
#include "Renderable.h"
#include "Renderable2D.h"
#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "SpriteSet.h"
#include "../Components/Light.h"
#include "../Time.h"

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

                static glm::vec3 _viewPosition;
                static glm::mat4 _viewMatrix;
                static glm::mat4 _projectionMatrix;

            public:
                static void         Initialize();
                static void         SubmitLight(GameEngine::Components::Light* light);
                static void         SubmitRenderable2D(Renderable2D* renderable2D);
                static void         SubmitRenderable(Renderable* renderable);
                static void         SetProjectionMatrix(glm::mat4 projectionMatrix);
                static void         SetViewMatrix(glm::mat4 viewMatrix);
                static void         SetViewPosition(glm::vec3 viewPosition);
                static unsigned int Render2DBatches(const std::pair<Material*, std::map<Texture*, std::vector<Renderable2D*>>>& materialPair);
                static unsigned int RenderDefault(const std::pair<Material*, std::vector<Renderable*>>& materialRenderables);
                static void         Draw();

                template <typename T, unsigned int(*RenderFunc)(const std::pair<Material*, T>&)>
                static unsigned int RenderRenderables(std::map<Material*, T>& map)
                {
                    unsigned int         numDrawCalls      = 0;
                    Shader*              shader            = nullptr;
                    Material::CullFace   currentCullFace   = Material::CullFace::Back;
                    Material::RenderMode currentRenderMode = Material::RenderMode::Fill;
                    bool                 firstLoop         = true;

                    for (auto& pair : map)
                    {
                        const Material*            material   = pair.first;
                        const Material::CullFace   cullFace   = material->GetCullFace();
                        const Material::RenderMode renderMode = material->GetRenderMode();

                        // Choose if new shader should get activated
                        Shader* newShader = material->GetShader();
                        if (shader == nullptr || shader != newShader)
                        {
                            shader = newShader;
                            shader->Use();

                            for (Components::Light*& light : _lights) { light->OnShaderUse(shader); }

                            // TODO: Somehow abstract this away
                            material->GetUniformBuffer()->SetUniformInstant<float>("u_Time", Time::GetTimeSinceStart());
                            material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_ViewProjection", _projectionMatrix * _viewMatrix);
                            material->GetUniformBuffer()->SetUniformInstant<glm::vec3>("u_ViewPosition", _viewPosition);
                        }

                        // Update polygon mode if needed
                        if (renderMode != currentRenderMode || firstLoop)
                        {
                            glPolygonMode(GL_FRONT_AND_BACK, material->GetRenderMode());
                            currentRenderMode = renderMode;
                        }

                        // Face Culling
                        if (cullFace != currentCullFace || firstLoop)
                        {
                            if (cullFace == Material::CullFace::None)
                            {
                                glDisable(GL_CULL_FACE);
                                glCullFace(GL_BACK);
                            }
                            else
                            {
                                glEnable(GL_CULL_FACE);
                                glCullFace(cullFace);
                            }

                            currentCullFace = cullFace;
                        }

                        // Apply material uniforms that are in the queue
                        material->GetUniformBuffer()->Apply();

                        numDrawCalls += RenderFunc(pair);

                        firstLoop = false;
                    }

                    return numDrawCalls;
                }
        };
    }
}