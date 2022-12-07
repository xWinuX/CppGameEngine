#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(VertexBufferAttribute* pVertexBufferAttributes, unsigned numVertexBufferAttributes)
{
    _pVertexBufferAttributes = pVertexBufferAttributes;
    _numVertexBufferAttributes = numVertexBufferAttributes;
}

void VertexBufferLayout::Bind() const
{
    for (unsigned int i = 0; i < _numVertexBufferAttributes; i++)
    {
        _pVertexBufferAttributes[i].Bind(i);
    }
}
