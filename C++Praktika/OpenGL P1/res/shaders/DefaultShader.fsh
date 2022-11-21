#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
    color = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, 1.0) * u_Color;
}