#pragma once
#include <glad/glad.h>

class IndexBuffer
{
    private:
        GLuint         _indexBufferID = 0;
        unsigned char* _pIndices;
        unsigned int   _numIndices;
        GLenum         _indicesType;

    public:
        IndexBuffer(unsigned char* pIndices, unsigned int numIndices, GLenum indicesType);
        ~IndexBuffer();
        unsigned int GetNumIndices() const;
        GLenum       GetIndicesType() const;
        void         Bind() const;
        static void  Unbind();
};
