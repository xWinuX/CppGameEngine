﻿#include "../Common/Version.glsl"

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_UVs;

out vec2 v_UVs;

void main() 
{
    gl_Position = vec4(a_Position.xy, 0.0, 1.0);
    v_UVs = a_UVs;
}
