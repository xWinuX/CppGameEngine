﻿#include "VertexBufferLayout.h"

using namespace GameEngine::Rendering;

VertexBufferLayout::VertexBufferLayout(VertexBufferAttribute* pVertexBufferAttributes, const size_t numVertexBufferAttributes)
{
    _pVertexBufferAttributes   = pVertexBufferAttributes;
    _numVertexBufferAttributes = numVertexBufferAttributes;
}

VertexBufferLayout::~VertexBufferLayout() { delete[] _pVertexBufferAttributes; }

void VertexBufferLayout::Bind(const unsigned int offset) const { for (unsigned int i = 0; i < _numVertexBufferAttributes; i++) { _pVertexBufferAttributes[i].Bind(i + offset); } }

void   VertexBufferLayout::Unbind() const { for (unsigned int i = 0; i < _numVertexBufferAttributes; i++) { _pVertexBufferAttributes[i].Unbind(i); } }
size_t VertexBufferLayout::GetNumVertexBufferAttributes() const { return _numVertexBufferAttributes; }
