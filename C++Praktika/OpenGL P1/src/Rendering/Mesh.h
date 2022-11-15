#pragma once

struct Mesh
{
    private:
        float*        _pPositions;
        unsigned int _positionsCount;
        unsigned int* _pIndices;
        unsigned int _indicesCount;
    public:
        Mesh(float* positions, unsigned int* indices, unsigned int positionsCount, unsigned int indicesCount);
        unsigned int GetPositionsCount() const;
        unsigned int GetIndicesCount() const;
};
