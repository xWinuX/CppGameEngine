﻿#include "../Common/Version.glsl"

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TextureCoords;

#include "../Common/Uniforms.glsl"

out vec4 v_Color;
out vec2 v_TextureCoords;

void main() 
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
    
    v_Color = a_Color;
    v_TextureCoords = a_TextureCoords;
}