#pragma once
#include <vector>

#include "SpriteAtlas.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace GameEngine
{
    namespace Rendering
    {
        class Sprite
        {
            private:
                struct VertexData
                {
                    public:
                        int       VertexIndex;
                        float     AspectRatio;
                        glm::vec2 UV;
                        glm::vec4 Color;
                };

                void AddSpriteQuad(const float aspectRatio, const glm::vec2 uvStep, const glm::ivec2 offset);

                Texture*                  _texture;
                glm::vec2                 _frameSize;
                std::vector<VertexData>   _vertexData;
                std::vector<unsigned int> _indices;
                SpriteAtlas*              _spriteAtlas       = nullptr;
                unsigned int              _numFrames         = 1;
                VertexArrayObject*        _vertexArrayObject = nullptr;

            public:
                explicit Sprite(Texture* texture);
                Sprite(Texture* texture, unsigned int numFrames, glm::vec2 frameSize);

                void Finalize();

                VertexArrayObject* GetVertexArrayObject() const;
        };
    }
}
