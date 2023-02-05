#pragma once
#include <map>

#include "FrameBuffer.h"
#include "Light.h"
#include "Material.h"
#include "Renderable.h"
#include "Renderable2D.h"
#include "RenderTarget.h"
#include "ShaderUseCallback.h"
#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "SpriteSet.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderer
        {
            private:
                static std::vector<ShaderUseCallback*>             _shaderUseCallbacks;
                static std::vector<RenderTarget*>                  _renderTargets;

                // 3D
                static std::map<Material*, std::vector<Renderable*>> _opaqueRenderables;
                static std::map<Material*, std::vector<Renderable*>> _transparentRenderables;

                // 2D Batch Vars
                static const size_t Renderable2DBatchMaxQuads;
                static const size_t Renderable2DBatchMaxSize;

                static unsigned char*     _renderable2DVertexData;
                static VertexArrayObject* _renderable2DVertexArrayObject;
                static VertexBuffer*      _renderable2DVertexBuffer;
                static IndexBuffer*       _renderable2DIndexBuffer;

                static std::map<Material*, std::map<Texture*, std::vector<Renderable2D*>>> _opaqueBatchRenderable2Ds;

            public:
                static void Initialize();

                static void SubmitShaderUseCallback(ShaderUseCallback* shaderUseCallback);
                static void SubmitBatchRenderable2D(Renderable2D* renderable2D);
                static void SubmitRenderable(Renderable* renderable);
                static void SubmitRenderTarget(RenderTarget* renderTarget);

                static unsigned int Render2DBatches(const std::pair<Material*, std::map<Texture*, std::vector<Renderable2D*>>>& materialPair);
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

                        // Choose if new shader should get activated
                        Shader* newShader = material->GetShader();
                        if (shader == nullptr || shader != newShader)
                        {
                            shader = newShader;
                            shader->Use();
                            
                            for (ShaderUseCallback* shaderUseCallback : _shaderUseCallbacks) { shaderUseCallback->OnShaderUse(shader); }
                        }

                        // Update polygon mode if needed
                        if (renderMode != currentRenderMode || firstLoop)
                        {
                            glPolygonMode(GL_FRONT_AND_BACK, material->GetRenderMode());
                            currentRenderMode = renderMode;
                        }

                        // Depth func
                        if (depthFunc != currentDepthFunc || firstLoop)
                        {
                            glDepthFunc(depthFunc);
                            currentDepthFunc = depthFunc;
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
                        material->GetUniformStorage()->Apply();

                        numDrawCalls += RenderFunc(pair);

                        firstLoop = false;
                    }

                    return numDrawCalls;
                }
        };
    }
}
