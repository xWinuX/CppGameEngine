#include "GameEngine/IO/Importer/GLTF.h"

#include <tiny_gltf.h>

#include "GameEngine/Physics/PhysicsManager.h"
#include "GameEngine/Rendering/Mesh.h"
#include "glm/gtx/string_cast.hpp"

using namespace GameEngine::Rendering;
using namespace GameEngine::IO::Importer;


const std::vector<std::string> GLTF::GLTFAttributeOrder = {"POSITION", "NORMAL", "TANGENT", "TEXCOORD_0", "COLOR_0"};

const std::map<int, GLTF::TinyGLTFTypeLookupEntry> GLTF::TinyGltfTypeLookup = {
    {TINYGLTF_TYPE_VEC4, {4}},
    {TINYGLTF_TYPE_VEC3, {3}},
    {TINYGLTF_TYPE_VEC2, {2}},
    {TINYGLTF_TYPE_SCALAR, {1}},
};

const std::map<int, GLTF::TinyGLTFComponentTypeLookupEntry> GLTF::TinyGltfComponentTypeLookup = {
    {TINYGLTF_COMPONENT_TYPE_FLOAT, {GL_FLOAT, sizeof(GLfloat)}},
    {TINYGLTF_COMPONENT_TYPE_BYTE, {GL_BYTE, sizeof(GLbyte)}},
    {TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE, {GL_UNSIGNED_BYTE, sizeof(GLubyte)}},
    {TINYGLTF_COMPONENT_TYPE_INT, {GL_INT, sizeof(GLint)}},
    {TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT, {GL_UNSIGNED_INT, sizeof(GLuint)}},
    {TINYGLTF_COMPONENT_TYPE_SHORT, {GL_SHORT, sizeof(GLshort)}},
    {TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, {GL_UNSIGNED_SHORT, sizeof(GLushort)}},
};

std::vector<GameEngine::Rendering::Mesh*> GLTF::ImportModel(const std::string& filePath, bool createCollider)
{
    std::vector<GameEngine::Rendering::Mesh*>  meshes;
    std::vector<reactphysics3d::TriangleMesh*> colliderMeshes;

    tinygltf::TinyGLTF loader;
    tinygltf::Model    model;
    std::string        error;
    std::string        warning;

    const bool result = loader.LoadASCIIFromFile(&model, &error, &warning, filePath);

    if (!warning.empty()) { Debug::Log::Error("GLTF Import Warning: " + warning); }

    if (!error.empty()) { Debug::Log::Error("GLTF Import Error: " + error); }

    if (!result)
    {
        GameEngine::Debug::Log::Error("GLTF Import Error: Failed to parse gltf file");
        return meshes;
    }

    for (tinygltf::Node node : model.nodes)
    {
        glm::vec3 translation = glm::zero<glm::vec3>();
        if (node.translation.size() >= 3) { translation = glm::vec3(node.translation[0], node.translation[1], node.translation[2]); }

        Mesh*                         mesh         = new Mesh(node.name, translation);
        tinygltf::Mesh                tinyGLTFMesh = model.meshes[node.mesh];
        reactphysics3d::TriangleMesh* triangleMesh;
        if (createCollider) { triangleMesh = Physics::PhysicsManager::GetPhysicsCommon()->createTriangleMesh(); }
        for (const tinygltf::Primitive& primitive : tinyGLTFMesh.primitives)
        {
            std::vector<BufferInfo> bufferInfos = std::vector<BufferInfo>();

            std::vector<tinygltf::Buffer*>     buffers           = std::vector<tinygltf::Buffer*>();
            std::vector<unsigned int>          bufferElementSize = std::vector<unsigned int>();
            std::vector<VertexBufferAttribute> attributes;

            size_t numVertices = 0;

            std::vector<int> sortedAttributeValues;

            for (const std::string& key : GLTFAttributeOrder)
            {
                auto it = primitive.attributes.find(key);
                if (it != primitive.attributes.end()) { sortedAttributeValues.push_back(it->second); }
            }

            // Calculate final vertex size
            unsigned int vertexSize = 0;
            for (const int attributeValue : sortedAttributeValues)
            {
                const tinygltf::Accessor accessor      = model.accessors[attributeValue];
                const GLint              attributeSize = TinyGltfTypeLookup.at(accessor.type).NumComponents;

                vertexSize += TinyGltfComponentTypeLookup.at(accessor.componentType).Size * attributeSize;
            }

            Debug::Log::Message("Vertex size is: " + std::to_string(vertexSize));

            unsigned int offset = 0;
            for (const int attributeValue : sortedAttributeValues)
            {
                const tinygltf::Accessor         accessor      = model.accessors[attributeValue];
                TinyGLTFTypeLookupEntry          type          = TinyGltfTypeLookup.at(accessor.type);
                TinyGLTFComponentTypeLookupEntry typeComponent = TinyGltfComponentTypeLookup.at(accessor.componentType);

                attributes.emplace_back(type.NumComponents, typeComponent.Enum, accessor.normalized, vertexSize, reinterpret_cast<void*>(offset));

                size_t size = typeComponent.Size * type.NumComponents;
                offset += size;

                const tinygltf::BufferView view = model.bufferViews[accessor.bufferView];
                bufferInfos.push_back({&model.buffers[view.buffer], size, (accessor.byteOffset + view.byteOffset)});

                Debug::Log::Message("accessor count: " + std::to_string(accessor.count));
                numVertices = accessor.count;
            }

            // Create vertex buffer layout
            VertexBufferAttribute* vertexBufferAttributes = new VertexBufferAttribute[attributes.size()];
            std::copy(attributes.begin(), attributes.end(), vertexBufferAttributes);

            VertexBufferLayout* vertexBufferLayout = new VertexBufferLayout(vertexBufferAttributes, attributes.size());

            // Create interleaved buffer
            size_t size = numVertices * vertexSize;

            unsigned char* vertexBufferData = new unsigned char[size];

            unsigned int bufferOffset = 0;
            for (unsigned int vertex = 0; vertex < numVertices; vertex++) // For each vertex
            {
                for (BufferInfo& bufferInfo : bufferInfos) // Go trough each buffer
                {
                    for (unsigned int elementSubOffset = 0; elementSubOffset < bufferInfo.BufferElementSize; elementSubOffset++)
                    // Add the amount of bytes that each attribute contains
                    {
                        // To the buffer
                        vertexBufferData[bufferOffset] = bufferInfo.PBuffer->data[bufferInfo.BufferByteOffset + (vertex * bufferInfo.BufferElementSize) + elementSubOffset];

                        bufferOffset++;
                    }
                }
            }

            tinygltf::Accessor   indicesAccessor   = model.accessors[primitive.indices];
            tinygltf::BufferView indicesBufferView = model.bufferViews[indicesAccessor.bufferView];
            tinygltf::Buffer     indicesBuffer     = model.buffers[indicesBufferView.buffer];

            size_t         indexSize = TinyGltfComponentTypeLookup.at(indicesAccessor.componentType).Size;
            unsigned char* indices   = new unsigned char[indicesAccessor.count * indexSize];

            auto start = indicesBuffer.data.begin() + static_cast<long long>(indicesAccessor.byteOffset + indicesBufferView.byteOffset);
            std::copy_n(start, (indicesAccessor.count * indexSize), indices);


            if (createCollider)
            {
                reactphysics3d::TriangleVertexArray::IndexDataType indexType = indexSize == 2
                                                                                   ? reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_SHORT_TYPE
                                                                                   : reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE;
                Debug::Log::Message("num vertices = " + std::to_string(numVertices));
                Debug::Log::Message("num triangles = " + std::to_string(static_cast<reactphysics3d::uint32>(indicesAccessor.count) / 3));

                reactphysics3d::TriangleVertexArray* triangleVertexArray = new reactphysics3d::TriangleVertexArray(
                                                                                                                   static_cast<reactphysics3d::uint32>(numVertices),
                                                                                                                   vertexBufferData,
                                                                                                                   vertexSize,
                                                                                                                   vertexBufferData + sizeof(glm::vec3),
                                                                                                                   vertexSize,
                                                                                                                   indicesAccessor.count / 3,
                                                                                                                   indices,
                                                                                                                   static_cast<reactphysics3d::uint32>(indexSize) * 3,
                                                                                                                   reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                                                                                                                   reactphysics3d::TriangleVertexArray::NormalDataType::NORMAL_FLOAT_TYPE,
                                                                                                                   indexType
                                                                                                                  );


                for (size_t i = 0; i < numVertices; i++)
                {
                    reactphysics3d::Vector3 pNormal;
                    triangleVertexArray->getNormal(i, &pNormal);
                    glm::vec3 normal = glm::vec3(pNormal.x, pNormal.y, pNormal.z);
                    if (glm::length(normal) < 0.01f) { Debug::Log::Message("normal after insertion: " + glm::to_string(normal)); }
                }

                triangleMesh->addSubpart(triangleVertexArray);
            }
            mesh->AddPrimitive(
                               new VertexBuffer(vertexBufferData, vertexSize, numVertices),
                               new IndexBuffer(indices, TinyGltfComponentTypeLookup.at(indicesAccessor.componentType).Size, indicesAccessor.count),
                               vertexBufferLayout
                              );

            //delete[] vertexBufferData;
            //delete[] indices;
        }
        if (createCollider) { mesh->SetColliderMesh(triangleMesh); }
        meshes.push_back(mesh);
    }

    return meshes;
}
