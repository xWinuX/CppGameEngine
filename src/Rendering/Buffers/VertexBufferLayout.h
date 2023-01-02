#pragma once
#include "VertexBufferAttribute.h"

class VertexBufferLayout
{
    private:
        VertexBufferAttribute* _pVertexBufferAttributes;
        unsigned int _numVertexBufferAttributes;
    public:
        explicit VertexBufferLayout(VertexBufferAttribute* pVertexBufferAttributes, unsigned int numVertexBufferAttributes);
        ~VertexBufferLayout();
        void Bind() const;
};
