#include "Mesh.h"

Mesh::Mesh(float* positions, unsigned int* indices, const unsigned int positionsCount, const unsigned int indicesCount)
{
    _pPositions     = positions;
    _pIndices       = indices;
    _positionsCount = positionsCount;
    _indicesCount   = indicesCount;
}

unsigned Mesh::GetPositionsCount() const { return _positionsCount; }
unsigned Mesh::GetIndicesCount() const { return _indicesCount; }
