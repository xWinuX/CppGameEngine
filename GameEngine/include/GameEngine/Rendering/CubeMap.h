#pragma once
#include <tiny_gltf.h>
#include <glad/glad.h>

#include "Sampler.h"

namespace GameEngine
{
    namespace Rendering
    {
        class CubeMap : public Sampler
        {
            private:
                GLuint                                _textureID = 0;
                static const std::vector<std::string> SuffixOrder;

            public:
                explicit CubeMap(const std::string& filePathWithoutExtension, const std::string& extension);
                ~CubeMap();
                void   Bind(const unsigned int slot) const override;
                void   Unbind() override;
                GLuint GetTextureID() const;
        };
    }
}
