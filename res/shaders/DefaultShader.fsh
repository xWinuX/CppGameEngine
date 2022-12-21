#version 400 core

in vec2 vTexCoords;
in float vDepth;
in vec3 vNormal;

out vec4 fragColor;

uniform vec4 u_ColorTint;
uniform sampler2D u_Texture;

void main()
{
    fragColor = texture2D(u_Texture, vTexCoords) * u_ColorTint;
}
