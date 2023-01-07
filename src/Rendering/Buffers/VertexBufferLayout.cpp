#include "VertexBufferLayout.h"

using namespace GameEngine::Rendering;

VertexBufferLayout::VertexBufferLayout(VertexBufferAttribute* pVertexBufferAttributes, const unsigned int numVertexBufferAttributes)
{
    _pVertexBufferAttributes   = pVertexBufferAttributes;
    _numVertexBufferAttributes = numVertexBufferAttributes;
}

VertexBufferLayout::~VertexBufferLayout() { delete[] _pVertexBufferAttributes; }

void VertexBufferLayout::Bind() const { for (unsigned int i = 0; i < _numVertexBufferAttributes; i++) { _pVertexBufferAttributes[i].Bind(i); } }

void VertexBufferLayout::Unbind() const { for (unsigned int i = 0; i < _numVertexBufferAttributes; i++) { _pVertexBufferAttributes[i].Unbind(i); } }
