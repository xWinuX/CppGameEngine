#pragma once
#include "Texture.h"
#include "tiny_gltf.h"
#include "glad/glad.h"

namespace GameEngine
{
    namespace Rendering
    {
        class CubeMap : public Texture<GL_TEXTURE_CUBE_MAP>
        {
            private:
                static const std::vector<std::string> SuffixOrder;

            public:
                explicit CubeMap(const std::string& filePathWithoutExtension, const std::string& extension);
        };
    }
}
