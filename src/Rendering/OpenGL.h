#pragma once
#include <map>

#include "glad/glad.h"

namespace GameEngine
{
    namespace Rendering
    {
        class OpenGL
        {
            private:
                struct TypeEnumLookupEntry
                {
                    public:
                        unsigned int Size;
                };

            public:
                static const std::map<GLenum, OpenGL::TypeEnumLookupEntry> TypeEnumLookup;
        };
    }
}
