#pragma once
#include "tiny_gltf.h"
#include "glad/glad.h"

namespace GameEngine
{
    namespace Rendering
    {
        class CubeMap
        {
            private:
                GLuint                                _textureID = 0;
                static const std::vector<std::string> SuffixOrder;

            public:
                explicit CubeMap(const std::string& filePathWithoutExtension, const std::string& extension);
                ~CubeMap();
                void        Bind(unsigned int slot) const;
                static void Unbind();
                GLuint      GetTextureID() const;
        };
    }
}
