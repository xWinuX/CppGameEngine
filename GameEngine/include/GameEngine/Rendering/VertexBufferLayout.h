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
                size_t                       _numVertexBufferAttributes;
            public:
                VertexBufferLayout(VertexBufferAttribute* pVertexBufferAttributes, const size_t numVertexBufferAttributes);
                ~VertexBufferLayout();
                void Bind(unsigned int offset) const;
                void Unbind() const;
                size_t GetNumVertexBufferAttributes() const;
        };
    }
}
