#pragma once
#include <map>

#include "FrameBuffer.h"
#include "Light.h"
#include "Material.h"
#include "Renderable.h"
#include "Renderable2D.h"
#include "RenderTarget.h"
#include "ShaderUseCallback.h"
#include "CascadedShadowMap.h"
#include "VertexBuffer.h"
#include "SpriteSet.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderer
        {
            public:
                static void Initialize();

                static void SetShadowShader(Shader* shadowShader);
                static void SetShadowSpriteShader(Shader* shadowSpriteShader);
                static void SetCascadedShadowMap(CascadedShadowMap* cascadedShadowMap);

                static void SubmitShadowMap(CascadedShadowMap* shadowMap);
                static void SubmitShaderUseCallback(ShaderUseCallback* shaderUseCallback);
                static void SubmitBatchRenderable2D(Renderable2D* renderable2D);
                static void SubmitRenderable(Renderable* renderable);
                static void SubmitRenderTarget(RenderTarget* renderTarget);

                static unsigned int Render2DBatches(const std::pair<Material*, std::map<Texture2D*, std::vector<Renderable2D*>>>& materialPair);
                static unsigned int RenderDefault(const std::pair<Material*, std::vector<Renderable*>>& materialRenderables);
                static void         RenderSubmitted();
                static void         DrawFrame();

                template <typename T, unsigned int(*RenderFunc)(const std::pair<Material*, T>&)>
                static unsigned int RenderRenderables(RenderTarget* renderTarget, std::map<Material*, T>& map)
                {
                    unsigned int         numDrawCalls      = 0;
                    Shader*              shader            = nullptr;
                    Material::CullFace   currentCullFace   = Material::CullFace::Back;
                    Material::RenderMode currentRenderMode = Material::RenderMode::Fill;
                    Material::DepthFunc  currentDepthFunc  = Material::DepthFunc::Less;
                    bool                 firstLoop         = true;

                    for (auto& pair : map)
                    {
                        const Material*            material   = pair.first;
                        const Material::CullFace   cullFace   = material->GetCullFace();
                        const Material::RenderMode renderMode = material->GetRenderMode();
                        const Material::DepthFunc  depthFunc  = material->GetDepthFunc();

                        // Check if new shader should be activated
                        Shader* newShader = material->GetShader();
                        if (shader == nullptr || shader != newShader)
                        {
                            shader = newShader;
                            shader->Use();

                            _cascadedShadowMap->GetTexture()->Bind(15);


                            for (ShaderUseCallback* shaderUseCallback : _shaderUseCallbacks) { shaderUseCallback->OnShaderUse(shader); }
                        }

                        // Update polygon mode if needed
                        if (renderMode != currentRenderMode || firstLoop)
                        {
                            glPolygonMode(GL_FRONT_AND_BACK, material->GetRenderMode());
                            currentRenderMode = renderMode;
                        }

                        // Update depth func if needed
                        if (depthFunc != currentDepthFunc || firstLoop)
                        {
                            glDepthFunc(depthFunc);
                            currentDepthFunc = depthFunc;
                        }

                        // Update face culling if needed
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
                        material->GetUniformStorage()->Apply();

                        numDrawCalls += RenderFunc(pair);

                        firstLoop = false;
                    }

                    return numDrawCalls;
                }

            private:
                typedef std::map<Layer, std::map<Material*, std::vector<Renderable*>>>                         RenderableStructure;
                typedef std::map<Layer, std::map<Material*, std::map<Texture2D*, std::vector<Renderable2D*>>>> Renderable2DBatchStructure;

                enum StaticTextureBinding
                {
                    SpriteBatchAtlasPage = 14,
                    ShadowMap            = 15,
                };

                static std::vector<ShaderUseCallback*> _shaderUseCallbacks;
                static std::vector<RenderTarget*>      _renderTargets;

                // Shadows
                static Shader* _shadowShader;
                static Shader* _shadowSpriteShader;

                static CascadedShadowMap* _cascadedShadowMap;

                // 3D
                static RenderableStructure _opaqueRenderables;
                static RenderableStructure _transparentRenderables;

                // 2D Batch Vars
                static const size_t Renderable2DBatchMaxQuads;
                static const size_t Renderable2DBatchMaxSize;

                static unsigned char*     _renderable2DBatchVertexData;
                static VertexArrayObject* _renderable2DBatchVertexArrayObject;
                static VertexBuffer*      _renderable2DBatchVertexBuffer;
                static IndexBuffer*       _renderable2DBatchIndexBuffer;

                static Renderable2DBatchStructure _opaqueBatchRenderable2Ds;
                static Renderable2DBatchStructure _transparentBatchRenderable2Ds;
        };
    }
}
