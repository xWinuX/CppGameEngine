#include "Cube.h"
#include <glad/glad.h>

VertexBufferAttribute Cube::_vertexBufferAttributes[1] = {
    VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr)
};

VertexBufferLayout Cube::_vertexBufferLayout = VertexBufferLayout(_vertexBufferAttributes, sizeof(_vertexBufferAttributes)/sizeof(VertexBufferAttribute));

Cube::Cube() :
    _vertexBuffer(_cubeVertices, sizeof(_cubeVertices) / sizeof(VertexPos)),
    _indexBuffer(_cubeIndices, sizeof(_cubeIndices) / sizeof(GLubyte)),
    _mesh({&_vertexBuffer, &_indexBuffer, &_vertexBufferLayout})
{  }

Mesh& Cube::GetMesh() { return _mesh; }
