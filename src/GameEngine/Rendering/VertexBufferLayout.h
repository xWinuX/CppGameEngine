#pragma once

#include "VertexBufferAttribute.h"

namespace GameEngine
{
    namespace Rendering
    {
        class VertexBufferLayout
        {
            private:
                VertexBufferAttribute*             _pVertexBufferAttributes;
                unsigned int                       _numVertexBufferAttributes;
            public:
                VertexBufferLayout(VertexBufferAttribute* pVertexBufferAttributes, unsigned int numVertexBufferAttributes);
                ~VertexBufferLayout();
                void Bind() const;
                void Unbind() const;
        };
    }
}
