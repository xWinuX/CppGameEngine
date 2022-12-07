#version 400 core

layout (location = 0) in vec3 pos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out float vDepth;

void main()
{
    gl_Position = vec4(pos, 1.0);
    vDepth = gl_Position.z; 
}
