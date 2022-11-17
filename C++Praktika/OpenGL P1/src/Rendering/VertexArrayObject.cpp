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

int add(int a, int b) { return a + b; }

void VertexArrayObject::Initialize()
{
    // Prepare Arrays
    unsigned int numPositions = 0;
    _numIndices   = 0;

    for (const auto& mapIterator : _meshMap)
    {
        std::vector<const Mesh*> meshes = mapIterator.second;
        for (const Mesh* const& mesh : meshes)
        {
            numPositions += mesh->pMeshData->numPositions;
            _numIndices += mesh->pMeshData->numIndices;
        }
    }

    std::vector<float>   positions = std::vector<float>(numPositions);
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
            const float* meshDataPositions    = mesh->pMeshData->pPositions;
            const int    numMeshDataPositions = mesh->pMeshData->numPositions;
            std::copy_n(meshDataPositions, numMeshDataPositions, positionsIterator);
            positionsIterator += numMeshDataPositions;
            positionPosition += numMeshDataPositions;

            // Combine indices
            const GLubyte* meshDataIndices    = mesh->pMeshData->pIndices;
            const int      numMeshDataIndices = mesh->pMeshData->numIndices;
            std::transform(
                           meshDataIndices,
                           meshDataIndices + numMeshDataIndices,
                           indicesIterator,
                           [indicesPosition](GLubyte input) { return input + indicesPosition; }
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
    glBufferData(GL_ARRAY_BUFFER, numPositions * sizeof(float), positions.data(), GL_STATIC_DRAW);

    // Bind Vertex Attributes
    for (unsigned int i = 0; i < _numVertexAttributes; i++) { _pVertexAttributes[i].Bind(i); }

    // Generate Index Buffer
    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(GLubyte), indices.data(), GL_STATIC_DRAW);

    Bind();
}

void VertexArrayObject::Bind() const
{
    glBindVertexArray(_vertexArrayID);
}

void VertexArrayObject::Draw() const
{
    Bind();
    glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_BYTE, nullptr);
}

void VertexArrayObject::AddMesh(const Mesh* mesh) { _meshMap[mesh->pMaterial].push_back(mesh); }
