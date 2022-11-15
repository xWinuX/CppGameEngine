#pragma once
#include "VertexAttribute.h"

class VertexArrayObject
{
    private:
        GLuint _vertexArrayID;
    public:
        VertexArrayObject();
        void Bind();
};

