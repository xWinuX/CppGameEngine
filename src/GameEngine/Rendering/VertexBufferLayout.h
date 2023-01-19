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
                void Bind(unsigned int offset) const;
                void Unbind() const;
                unsigned int GetNumVertexBufferAttributes() const;
        };
    }
}
