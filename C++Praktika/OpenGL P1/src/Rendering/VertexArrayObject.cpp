#include "VertexArrayObject.h"
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &_vertexArrayID);
}

void VertexArrayObject::Bind()
{
    glBindVertexArray(_vertexArrayID);
}

