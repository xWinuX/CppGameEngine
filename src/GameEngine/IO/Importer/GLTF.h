#pragma once
#include <string>
#include <vector>

#include "tiny_gltf.h"
#include "../../Rendering/Mesh.h"

namespace GameEngine
{
    namespace IO
    {
        namespace Importer
        {
            class GLTF
            {
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
                            unsigned int      BufferElementSize;
                            unsigned int      BufferByteOffset;
                    };


                    struct TinyGLTFComponentTypeLookupEntry
                    {
                        public:
                            GLenum       Enum;
                            unsigned int Size;
                    };

                    static const std::vector<std::string>                              GLTFAttributeOrder;
                    static const std::map<int, GLTF::TinyGLTFTypeLookupEntry>          TinyGltfTypeLookup;
                    static const std::map<int, GLTF::TinyGLTFComponentTypeLookupEntry> TinyGltfComponentTypeLookup;

                public:
                    static std::vector<GameEngine::Rendering::Mesh*> ImportModel(std::string filePath);
            };
        }
    }
}
