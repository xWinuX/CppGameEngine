#version 400 core

in vec2 vTexCoords;
in float vDepth;

out vec4 fragColor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    fragColor = texture2D(u_Texture, vTexCoords) * (1-abs(vDepth/50.0));
}
