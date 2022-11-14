#pragma once

struct Mesh
{
    private:
        float* _vertices;
        unsigned int* _triangles;
    public:
        Mesh(float vertices[], unsigned int triangles[]);
};
