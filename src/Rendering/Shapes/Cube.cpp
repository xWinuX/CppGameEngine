#include "Cube.h"
#include <glad/glad.h>

VertexBufferAttribute Cube::_vertexBufferAttributes[2] = {
    VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr),
    VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)))
};

VertexBufferLayout Cube::_vertexBufferLayout = VertexBufferLayout(_vertexBufferAttributes, sizeof(_vertexBufferAttributes) / sizeof(VertexBufferAttribute));

Cube::Cube() :
    _pCubeVertices(new VertexPositionUV[8]{
                       // Front
                       {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}}, // 0 Front Top Left
                       {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},  // 1 Front Top Right
                       {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},  // 2 Front Bottom Left
                       {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},   // 3 Front Bottom Right

                       // Back
                       {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}}, // 0 Back Top Left
                       {{1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},  // 1 Back Top Right
                       {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}},  // 2 Back Bottom Left
                       {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f}},   // 3 Back Bottom Right
                   }),
    _numCubeVertices(8),
    _pCubeIndices(new unsigned int[36]{
                      // Front Face
                      0, 1, 2, // First Triangle
                      1, 3, 2, // Second Triangle

                      // Right Face
                      1, 5, 3, // First Triangle
                      5, 7, 3, // Second Triangle

                      // Left Face
                      0, 6, 4, // First Triangle
                      6, 0, 2, // Second Triangle

                      // Top Face
                      1, 0, 4, // First Triangle
                      1, 4, 5, // Second Triangle

                      // Bottom Face
                      2, 3, 7, // First Triangle
                      6, 2, 7, // Second Triangle

                      // Back Face
                      7, 5, 4, // First Triangle
                      4, 6, 7  // Second Triangle
                  }),
    _numCubeIndices(36)
{
    _pMesh = new Mesh(
                      new VertexBuffer(reinterpret_cast<unsigned char*>(_pCubeVertices), sizeof(VertexPositionUV), _numCubeVertices),
                      new IndexBuffer(_pCubeIndices, _numCubeIndices),
                      _vertexBufferLayout
                     );
}

Cube::~Cube() { delete _pMesh; }

Mesh* Cube::GetMesh() const { return _pMesh; }
