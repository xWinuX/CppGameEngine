#pragma once

#include "VertexAttribute.h"

class VertexAttributes
{
    private:
        const VertexAttribute* _pVertexAttributes;
        unsigned int _vertexAttributesSize;
    public:
 
        explicit VertexAttributes(const VertexAttribute* vertexAttributes, unsigned int vertexAttributesSize);
        void     Bind() const;
        
};
