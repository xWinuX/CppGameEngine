﻿#include "Model.h"
#include <fstream>
#include <numeric>
#include <random>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <typeinfo>

#include "Vertex.h"
#include "../Components/Camera.h"
#include "../Debug/Log.h"
#include "../IO/Stream.h"
#include "tiny_gltf.h"

std::vector<std::string> splitString(const std::string& str, const char delimiter, const unsigned int baseOffset)
{
    std::vector<std::string> split;
    unsigned int             offset         = baseOffset;
    unsigned int             previousOffset = baseOffset;

    while (offset < str.length())
    {
        offset = str.find(delimiter, offset);

        // Break out of the loop if next find can't be found
        if (offset == std::string::npos) { offset = str.length(); }

        std::string sub = str.substr(previousOffset, (offset - previousOffset));
        split.push_back(sub);
        offset++;
        previousOffset = offset;
    }

    return split;
}


template <typename T>
void splitString(const std::string& str, const unsigned int baseOffset, const char delimiter, T** pointerList, const unsigned int pointerListSize)
{
    unsigned int offset         = baseOffset;
    unsigned int previousOffset = baseOffset;
    for (unsigned int i = 0; i < pointerListSize; i++)
    {
        offset = str.find(delimiter, offset);

        if (offset == std::string::npos) { offset = str.length(); }

        if (
            typeid(T) == typeid(int) ||
            typeid(T) == typeid(unsigned) ||
            typeid(T) == typeid(unsigned int)
        ) { **(pointerList + i) = stoi(str.substr(previousOffset, (offset - previousOffset))); }
        else if (typeid(T) == typeid(float)) { **(pointerList + i) = stof(str.substr(previousOffset, (offset - previousOffset))); }
        offset++;
        previousOffset = offset;
    }
}

Model::Model(const std::string& filePath)
{
    const std::string extension = filePath.substr(filePath.find_last_of('.') + 1);

    if (extension == "obj") { ImportObjModel(filePath); }
    else if (extension == "gltf") { ImportGLTFModel(filePath); }
    else { Debug::Log::Error("Model file extension " + extension + " is not supported"); }
}

Model::~Model() { for (const Mesh* mesh : _meshes) { delete mesh; } }

Mesh* Model::GetMesh(const unsigned index) const { return index < _meshes.size() ? _meshes[index] : nullptr; }

void Model::AddMesh(
    std::vector<VertexPositionUVNormal>& vertexBuffer,
    std::vector<unsigned int>&           indexBuffer,
    std::vector<glm::vec3>&              positionList,
    std::vector<glm::vec2>&              uvList,
    std::vector<glm::vec3>&              normalList,
    std::vector<glm::vec4>&              colorList)
{
    // Create new mesh
    unsigned int* indices = new unsigned int[indexBuffer.size()];
    std::copy(indexBuffer.begin(), indexBuffer.end(), indices);

    VertexPositionUVNormal* vertices = new VertexPositionUVNormal[vertexBuffer.size()];
    std::copy(vertexBuffer.begin(), vertexBuffer.end(), vertices);

    _meshes.push_back(new Mesh(
                               new VertexBuffer(reinterpret_cast<unsigned char*>(vertices), sizeof(VertexPositionUVNormal), vertexBuffer.size()),
                               new IndexBuffer(indices, indexBuffer.size()),
                               _vertexBufferLayout));

    vertexBuffer.clear();
    indexBuffer.clear();
    positionList.clear();
    uvList.clear();
    normalList.clear();
    colorList.clear();
}


struct TinyGLTFTypeLookupEntry
{
    public:
        GLint NumComponents;
};

std::map<int, TinyGLTFTypeLookupEntry> tinyGltfTypeLookup = {
    {TINYGLTF_TYPE_VEC4, {4}},
    {TINYGLTF_TYPE_VEC2, {3}},
    {TINYGLTF_TYPE_VEC3, {2}},
    {TINYGLTF_TYPE_SCALAR, {2}},
};


struct TinyGLTFComponentTypeLookupEntry
{
    public:
        GLenum       Enum;
        unsigned int Size;
};

std::map<int, TinyGLTFComponentTypeLookupEntry> tinyGltfComponentTypeLookup = {
    {TINYGLTF_COMPONENT_TYPE_FLOAT, {GL_FLOAT, sizeof(GLfloat)}},
    {TINYGLTF_COMPONENT_TYPE_INT, {GL_INT, sizeof(GLint)}},
    {TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, {GL_SHORT, sizeof(GLshort)}},
};

void Model::ImportGLTFModel(const std::string& filePath)
{
    tinygltf::TinyGLTF loader;
    tinygltf::Model    model;
    std::string        error;
    std::string        warning;

    const bool result = loader.LoadASCIIFromFile(&model, &error, &warning, filePath);

    if (!warning.empty()) { Debug::Log::Error("GLTF Import Warning: " + warning); }

    if (!error.empty()) { Debug::Log::Error("GLTF Import Error: " + error); }

    if (!result)
    {
        Debug::Log::Error("GLTF Import Error: Failed to parse gltf file");
        return;
    }

    for (const tinygltf::Mesh& tinyGLTFMesh : model.meshes)
    {
        for (const tinygltf::Primitive& primitive : tinyGLTFMesh.primitives)
        {
            struct BufferInfo
            {
                public:
                    tinygltf::Buffer* PBuffer;
                    unsigned int BufferElementSize;
                    unsigned int BufferByteOffset;
            };

        
            std::vector<BufferInfo> bufferInfos = std::vector<BufferInfo>();
            
            std::vector<tinygltf::Buffer*> buffers = std::vector<tinygltf::Buffer*>();
            std::vector<unsigned int> bufferElementSize = std::vector<unsigned int>();
            std::vector<VertexBufferAttribute> attributes;

            unsigned int numVertices = 0;

            // Calculate final stride
            unsigned int vertexSize = 0;
            for (const std::pair<const std::string, int>& attribute : primitive.attributes)
            {
                const tinygltf::Accessor accessor      = model.accessors[attribute.second];
                const GLint              attributeSize = tinyGltfTypeLookup[accessor.type].NumComponents;

                vertexSize += tinyGltfComponentTypeLookup[accessor.componentType].Size * attributeSize;
            }

            
            unsigned int offset = 0;
            for (const std::pair<const std::string, int>& attribute : primitive.attributes)
            {
                const tinygltf::Accessor         accessor      = model.accessors[attribute.second];
                TinyGLTFTypeLookupEntry          type          = tinyGltfTypeLookup[accessor.type];
                TinyGLTFComponentTypeLookupEntry typeComponent = tinyGltfComponentTypeLookup[accessor.componentType];
                
                attributes.emplace_back(type.NumComponents, typeComponent.Enum, vertexSize, accessor.normalized, reinterpret_cast<GLvoid*>(offset));

                unsigned int size = typeComponent.Size * type.NumComponents;
                offset += size;

                const tinygltf::BufferView view   = model.bufferViews[accessor.bufferView];
                bufferInfos.push_back({&model.buffers[view.buffer], size, accessor.byteOffset + view.byteOffset});

                numVertices = accessor.count;
            }

            // Create vertex buffer layout
            VertexBufferAttribute* vertexBufferAttributes = new VertexBufferAttribute[attributes.size()];
            std::copy(attributes.begin(), attributes.end(), vertexBufferAttributes);
            
            VertexBufferLayout vertexBufferLayout = VertexBufferLayout(vertexBufferAttributes, attributes.size());

            // Create interleaved buffer
            unsigned int size = std::accumulate(bufferInfos.begin(), bufferInfos.end(), 0, [](int, const BufferInfo bufferInfo) { return bufferInfo.PBuffer->data.size(); });

            unsigned char* vertexBufferData = new unsigned char[size];

            for (unsigned int vertex = 0; vertex < numVertices; vertex++) // For each vertex
            {
                unsigned int elementOffset = 0;      // Size of each previous element
                for (auto& bufferInfo : bufferInfos) // Go trough each buffer
                {
                    for (unsigned int elementSubOffset = 0; elementSubOffset < bufferInfo.BufferElementSize; elementSubOffset++) // Add the amount of bytes that each attribute contains
                    {
                        // To the buffer
                        vertexBufferData[(vertex * vertexSize)+elementOffset+elementSubOffset] = bufferInfo.PBuffer->data[bufferInfo.BufferByteOffset + (vertex * vertexSize)+elementOffset+elementSubOffset];
                    }
                    elementOffset += bufferInfo.BufferElementSize;
                }
            }

            VertexBuffer* vertexBuffer = new VertexBuffer(vertexBufferData, vertexSize, size);


            tinygltf::Accessor   indicesAccessor   = model.accessors[primitive.indices];
            tinygltf::BufferView indicesBufferView = model.bufferViews[indicesAccessor.bufferView];
            tinygltf::Buffer     indicesBuffer     = model.buffers[indicesBufferView.buffer];

            unsigned int* indices = new unsigned int[indicesAccessor.count];
            auto start = std::begin(indicesBuffer.data) + indicesAccessor.byteOffset + indicesBufferView.byteOffset;
            std::copy_n(start, indicesAccessor.count, indices);

            IndexBuffer* indexBuffer = new IndexBuffer(indices, indicesAccessor.count);
            
            _meshes.push_back(new Mesh(vertexBuffer, indexBuffer, vertexBufferLayout));
        }
    }

    const tinygltf::Mesh&       mesh             = model.meshes[0];
    const tinygltf::Accessor&   positionAccessor = model.accessors[mesh.primitives[0].attributes.at("POSITION")];
    const tinygltf::BufferView& positionView     = model.bufferViews[positionAccessor.bufferView];
    const tinygltf::Buffer&     positionBuffer   = model.buffers[positionView.buffer];
    const void*                 positionData     = &positionBuffer.data[positionView.byteOffset + positionAccessor.byteOffset];
}

void Model::ImportObjModel(const std::string& filePath)
{
    Stream stream(filePath);

    std::vector<VertexPositionUVNormal> vertexBuffer;
    std::vector<unsigned int>           indexBuffer;
    std::vector<glm::vec3>              positionList;
    std::vector<glm::vec2>              uvList;
    std::vector<glm::vec3>              normalList;
    std::vector<glm::vec4>              colorList;

    std::string line;

    unsigned int positionIndexOffset = 0;
    unsigned int uvIndexOffset       = 0;
    unsigned int normalIndexOffset   = 0;
    unsigned int colorIndexOffset    = 0;
    while (std::getline(stream.GetCStream(), line))
    {
        if (line.length() == 0) { continue; }

        switch (line[0])
        {
            case 'o': // New object
                if (!vertexBuffer.empty())
                {
                    positionIndexOffset += positionList.size();
                    uvIndexOffset += uvList.size();
                    normalIndexOffset += normalList.size();
                    colorIndexOffset += colorList.size();
                    AddMesh(vertexBuffer, indexBuffer, positionList, uvList, normalList, colorList);
                }
                break;

            case 'v': // Vertex attributes
                {
                    // Skip if line length is 1
                    if (line.length() == 1) { continue; }

                    // Vec2 attributes
                    if (line[1] == 't') // vec2 (uvs)
                    {
                        glm::vec2 vec2           = glm::vec2(0.0);
                        float*    pVec2Coords[2] = {&vec2.x, &vec2.y};
                        splitString<float>(line, 3, ' ', pVec2Coords, 2);

                        //Debug::Log::Message(std::to_string(vec2.x) + "," + std::to_string(vec2.y));

                        uvList.push_back(vec2);
                        continue;
                    }

                    // Vec3 attributes
                    glm::vec3 vec3           = glm::vec3(0.0f);
                    float*    pVec3Coords[3] = {&vec3.x, &vec3.y, &vec3.z};
                    if (line[1] == ' ') // Positions
                    {
                        splitString<float>(line, 2, ' ', pVec3Coords, 3);
                        positionList.push_back(vec3);
                    }
                    else if (line[1] == 'n') // Normals
                    {
                        splitString<float>(line, 3, ' ', pVec3Coords, 3);
                        normalList.push_back(vec3);
                    }

                    // Debug::Log::Message(std::to_string(vec3.x) + "," + std::to_string(vec3.y) + "," + std::to_string(vec3.z));

                    break;
                }
            case 'f': // Faces
                //Debug::Log::Message("before split");
                std::vector<std::string> vertices = splitString(line, ' ', 2);
            //Debug::Log::Message("after split");

                for (const std::string& vertex : vertices)
                {
                    indexBuffer.push_back(indexBuffer.size());
                    unsigned int positionIndex = 0;
                    unsigned int uvIndex       = 0;
                    unsigned int normalIndex   = 0;

                    unsigned int* pVertexAttributes[] = {&positionIndex, &uvIndex, &normalIndex};


                    //Debug::Log::Message(vertex);
                    splitString(vertex, 0, '/', pVertexAttributes, 3);

                    positionIndex -= positionIndexOffset;
                    uvIndex -= uvIndexOffset;
                    normalIndex -= normalIndexOffset;

                    //Debug::Log::Message(std::to_string(positionIndex) + "," + std::to_string(uvIndex) + "," + std::to_string(normalIndex));

                    vertexBuffer.emplace_back(positionList[positionIndex - 1], uvList[uvIndex - 1], normalList[normalIndex - 1]);
                }

                break;
        }
    }
    stream.Close();

    // Add last mesh
    AddMesh(vertexBuffer, indexBuffer, positionList, uvList, normalList, colorList);
}
