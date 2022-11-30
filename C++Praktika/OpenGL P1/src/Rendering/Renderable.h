#pragma once
#include "VertexArrayObject.h"
#include "../Components/Transform.h"

class Renderable
{
    public:
        virtual VertexArrayObject* GetVertexArrayObject() = 0;
        virtual Material*          GetMaterial() = 0;
        virtual Transform*         GetTransform() = 0;
};
