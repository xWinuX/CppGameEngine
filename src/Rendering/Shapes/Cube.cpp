#include "Cube.h"
#include <glad/glad.h>

VertexBufferAttribute Cube::_vertexBufferAttributes[2] = {
    VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr),
    VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)))
};

VertexBufferLayout Cube::_vertexBufferLayout = VertexBufferLayout(_vertexBufferAttributes, sizeof(_vertexBufferAttributes)/sizeof(VertexBufferAttribute));

Cube::Cube() :
    _vertexBuffer(reinterpret_cast<unsigned char*>(_cubeVertices), 5 * sizeof(float),  sizeof(_cubeVertices) / sizeof(VertexPositionUV)),
    _indexBuffer(_cubeIndices, sizeof(_cubeIndices) / sizeof(GLubyte)),
    _mesh({&_vertexBuffer, &_indexBuffer, &_vertexBufferLayout})
{  }

Mesh& Cube::GetMesh() { return _mesh; }
