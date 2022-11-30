#version 400 core

layout (location = 0) in vec3 pos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out float vDepth;

void main()
{
    gl_Position = u_ViewProjection * u_Model * vec4(pos, 1.0);
    vDepth = gl_Position.z; 
}
