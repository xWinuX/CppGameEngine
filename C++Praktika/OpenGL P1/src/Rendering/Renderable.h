#pragma once
#include "VertexArrayObject.h"
#include "../Components/Transform.h"

class Renderable
{
    public:
        virtual ~Renderable() = default;

        virtual VertexArrayObject* GetVertexArrayObject() { return nullptr; }
        virtual Material*          GetMaterial() { return nullptr; }
        virtual Transform*         GetTransform() { return nullptr; }
};
