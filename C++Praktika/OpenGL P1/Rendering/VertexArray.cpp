#include "VertexArray.h"

#include <glad/glad.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_vertexArrayID);
    glBindVertexArray(_vertexArrayID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
}


