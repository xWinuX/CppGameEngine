#include "Uniform.h"
#include <glm/mat4x4.hpp>

#define VALUE _isSet ? _value : _defaultValue

template <>
void Uniform<glm::vec4>::Apply() const
{
    const auto value = VALUE;
    glUniform4f(_location, value.x, value.y, value.z, value.w);
}

template <>
void Uniform<glm::mat4>::Apply() const
{
    glUniformMatrix4fv(_location, 1, GL_FALSE, &VALUE[0][0]);
}

template <>
void Uniform<int>::Apply() const
{
    glUniform1i(_location, VALUE);
}


