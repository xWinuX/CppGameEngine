#version 400 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Colors;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Color;

void main()
{
    gl_Position = u_ViewProjection  * vec4(a_Position, 1.0);
    v_Color = a_Colors;    
}
