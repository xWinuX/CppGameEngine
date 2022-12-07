#version 400 core

in float vDepth;

out vec4 fragColor;

uniform vec4 u_Color;

void main()
{
    fragColor = (1-abs(vDepth/30.0)) * vec4(0.5, 0.5, 0.0, 1.0);
}
