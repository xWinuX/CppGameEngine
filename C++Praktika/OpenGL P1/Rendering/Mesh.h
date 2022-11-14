#pragma once

struct Mesh
{
    private:
        float* _positions;
        unsigned int* _indices;
    public:
        Mesh(float positions[], unsigned int indices[]);
};
