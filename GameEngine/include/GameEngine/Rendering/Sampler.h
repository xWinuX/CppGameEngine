#pragma once

namespace GameEngine
{
    namespace Rendering
    {
        class Sampler
        {
            public:
                virtual void Bind(const unsigned int slot = 0) const = 0;
                virtual void Unbind() = 0;
        };
    }
}
