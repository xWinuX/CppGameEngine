#pragma once
#include "VertexArrayObject.h"
#include "../Core/Transform.h"

class Renderable
{
    public:
        virtual ~Renderable() = default;

        virtual VertexArrayObject* GetVertexArrayObject() { return nullptr; }
        virtual Material*          GetMaterial() { return nullptr; }
        virtual const Transform*   GetTransform() { return nullptr; }
};
