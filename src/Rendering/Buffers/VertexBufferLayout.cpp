#include "VertexBufferLayout.h"

#include <iostream>

VertexBufferLayout::VertexBufferLayout(VertexBufferAttribute* pVertexBufferAttributes, const unsigned int numVertexBufferAttributes)
{
    _pVertexBufferAttributes = pVertexBufferAttributes;
    _numVertexBufferAttributes = numVertexBufferAttributes;
}

void VertexBufferLayout::Bind() const
{
    for (unsigned int i = 0; i < _numVertexBufferAttributes; i++)
    {
       // std::cout << i << ":" << _pVertexBufferAttributes[i].GetSize() << std::endl;
        _pVertexBufferAttributes[i].Bind(i);
    }
}
