#pragma once
#include <glad/glad.h>

class IndexBuffer
{
    private:
        GLuint       _indexBufferID = 0;
        unsigned int*      _pIndices;
        unsigned int _numIndices;
    public:
        IndexBuffer(unsigned int* pIndices, unsigned int numIndices);
        ~IndexBuffer();
        unsigned int GetNumIndices() const;
        void         Bind() const;
        static void  Unbind();
};
