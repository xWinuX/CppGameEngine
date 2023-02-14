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
            public:
                explicit CubeMap(const std::string& filePathWithoutExtension, const std::string& extension);

            private:
                static const std::vector<std::string> SuffixOrder;
        };
    }
}
