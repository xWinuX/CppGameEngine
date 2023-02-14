#pragma once
#include <string>
#include <tiny_gltf.h>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

#include "GameEngine/Rendering/Mesh.h"

namespace GameEngine
{
    namespace IO
    {
        namespace Importer
        {
            class GLTF
            {
                public:
                    static std::vector<GameEngine::Rendering::Mesh*> ImportModel(const std::string& filePath, bool createCollider = false);

                private:
                    struct TinyGLTFTypeLookupEntry
                    {
                        public:
                            GLint NumComponents;
                    };


                    struct BufferInfo
                    {
                        public:
                            tinygltf::Buffer* PBuffer;
                            size_t            BufferElementSize;
                            size_t            BufferByteOffset;
                    };


                    struct TinyGLTFComponentTypeLookupEntry
                    {
                        public:
                            GLenum Enum;
                            size_t Size;
                    };

                    static const std::vector<std::string>                              GLTFAttributeOrder;
                    static const std::map<int, GLTF::TinyGLTFTypeLookupEntry>          TinyGltfTypeLookup;
                    static const std::map<int, GLTF::TinyGLTFComponentTypeLookupEntry> TinyGltfComponentTypeLookup;
            };
        }
    }
}
