#include "VertexArrayObject.h"

#include <algorithm>
#include <glad/glad.h>

#include "Material.h"

VertexArrayObject::VertexArrayObject(const VertexAttribute* pVertexAttributes, const unsigned int numVertexAttributes)
{
    glGenVertexArrays(1, &_vertexArrayID);
    _pVertexAttributes   = pVertexAttributes;
    _numVertexAttributes = numVertexAttributes;
}

void VertexArrayObject::PrepareMeshes() const
{
    std::vector<float>   positions = std::vector<float>(_numPositions);
    std::vector<GLubyte> indices   = std::vector<GLubyte>(_numIndices);

    int  positionPosition  = 0;
    int  indicesPosition   = 0;
    auto positionsIterator = positions.begin();
    auto indicesIterator   = indices.begin();
    for (const auto& mapIterator : _meshMap)
    {
        std::vector<const Mesh*> meshes = mapIterator.second;
        for (const Mesh* const& mesh : meshes)
        {
            // Combine Positions
            const float* meshDataPositions    = mesh->PMeshData->PPositions;
            const int    numMeshDataPositions = mesh->PMeshData->NumPositions;
            std::copy_n(meshDataPositions, numMeshDataPositions, positionsIterator);
            positionsIterator += numMeshDataPositions;
            positionPosition += numMeshDataPositions;

            // Combine indices
            const GLubyte* meshDataIndices    = mesh->PMeshData->PIndices;
            const int      numMeshDataIndices = mesh->PMeshData->NumIndices;
            std::transform(
                           meshDataIndices,
                           meshDataIndices + numMeshDataIndices,
                           indicesIterator,
                           [indicesPosition](const GLubyte input) { return input + indicesPosition; }
                          );
            indicesPosition += numMeshDataIndices;
            indicesIterator += numMeshDataIndices;
        }
    }

    Bind();

    // Generate Vertex Buffer
    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, _numPositions * sizeof(float), positions.data(), GL_STATIC_DRAW);

    // Bind Vertex Attributes
    for (unsigned int i = 0; i < _numVertexAttributes; i++) { _pVertexAttributes[i].Bind(i); }

    // Generate Index Buffer
    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(GLubyte), indices.data(), GL_STATIC_DRAW);

    std::cout << "posSize: " << positions.size() << std::endl;
    for (const float position : positions) { std::cout << "pos: " << position << std::endl; }

    std::cout << "indSize: " << indices.size() << std::endl;
    for (const float index : indices) { std::cout << "ind: " << index << std::endl; }

    Bind();
}

void VertexArrayObject::Bind() const
{
    glBindVertexArray(_vertexArrayID);
}

void VertexArrayObject::Draw() const
{
    Bind();
    int           offset = 0;
    const Shader* shader = nullptr;
    for (const auto& indicesBatchMap : _indicesBatchMap)
    {
        // Choose if new shader should get activated
        const Shader* newShader = indicesBatchMap.first->GetShader();
        if (shader == nullptr || shader != newShader)
        {
            indicesBatchMap.first->UseShader();
            shader = newShader;
        }

        // Apply material unique uniforms
        indicesBatchMap.first->ApplyUniforms();

        // Actually draw the elements
        glDrawElements(GL_TRIANGLES, indicesBatchMap.second, GL_UNSIGNED_BYTE, (void*)offset);
        offset += indicesBatchMap.second;
    }
}

void VertexArrayObject::AddMesh(const Mesh* mesh)
{
    // TODO: Add smarter way to batch materials (make it so that if there are materials with the same shader they are in order so the shader only gets switched once)
    _meshMap[mesh->PMaterial].push_back(mesh);

    const int numIndices   = mesh->PMeshData->NumIndices;
    const int numPositions = mesh->PMeshData->NumPositions;

    _indicesBatchMap[mesh->PMaterial] += numIndices;
    _numPositions += numPositions;
    _numIndices += numIndices;
}
