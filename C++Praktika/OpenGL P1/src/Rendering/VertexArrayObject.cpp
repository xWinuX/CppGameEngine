#include "VertexArrayObject.h"

#include <glad/glad.h>


/*
VertexArrayObject::VertexArrayObject(const VertexBufferAttribute* pVertexAttributes, const unsigned int numVertexAttributes)
{
    glGenVertexArrays(1, &_vertexArrayID);
    glGenBuffers(1, &_vertexBufferID);
    glGenBuffers(1, &_indexBufferID);
    _pVertexAttributes   = pVertexAttributes;
    _numVertexAttributes = numVertexAttributes;
}

void VertexArrayObject::PrepareMeshes()
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
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, _numPositions * sizeof(float), positions.data(), GL_STATIC_DRAW);

    // Bind Vertex Attributes
    for (unsigned int i = 0; i < _numVertexAttributes; i++) { _pVertexAttributes[i].Bind(i); }

    // Generate Index Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
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

void VertexArrayObject::RemoveMesh(const Mesh* mesh)
{
    std::vector<const Mesh*>* vec               = &_meshMap[mesh->PMaterial];
    const auto                foundMeshIterator = std::find(vec->begin(), vec->end(), mesh);
    if (foundMeshIterator != vec->end())
    {
        _indicesBatchMap[mesh->PMaterial] -= mesh->PMeshData->NumIndices;
        _numPositions -= mesh->PMeshData->NumPositions;
        _numIndices -= mesh->PMeshData->NumIndices;
        vec->erase(foundMeshIterator);
    }
}

void VertexArrayObject::ClearMeshes()
{
    for (auto& meshMap : _meshMap) { meshMap.second.clear(); }

    _meshMap.clear();
    _indicesBatchMap.clear();
    _numPositions = 0;
    _numIndices   = 0;
}*/

VertexArrayObject::VertexArrayObject(const VertexBufferLayout* pVertexBufferLayout)
{
    _pVertexBufferLayout = pVertexBufferLayout;
    glGenVertexArrays(1, &_vertexArrayObjectID);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &_vertexArrayObjectID);
}

void VertexArrayObject::AddVertexBuffer(VertexBuffer* pVertexBuffer)
{
    _vertexBuffers.push_back(pVertexBuffer);
}

void VertexArrayObject::SetIndexBuffer(IndexBuffer* pIndexBuffer)
{
    _pIndexBuffer = pIndexBuffer;
}

void VertexArrayObject::Bind() const
{
    glBindVertexArray(_vertexArrayObjectID);
}

void VertexArrayObject::Unbind()
{
    glBindVertexArray(0);
}
