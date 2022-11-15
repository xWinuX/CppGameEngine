#include "VertexAttributes.h"

VertexAttributes::VertexAttributes(const VertexAttribute* vertexAttributes, const unsigned int vertexAttributesSize)
{
    _pVertexAttributes = vertexAttributes;
    _vertexAttributesSize = vertexAttributesSize;
}

void VertexAttributes::Bind() const
{
    for (unsigned int i = 0; i < _vertexAttributesSize; i++)
    {
        _pVertexAttributes[i].Bind(i);
    }
}
