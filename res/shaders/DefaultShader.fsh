#version 400 core

in vec2 v_TexCoords;
in vec3 v_Normal;
in float v_LightIntensity;

out vec4 fragColor;

uniform vec4 u_ColorTint;
uniform sampler2D u_Texture;

void main()
{
    fragColor = texture2D(u_Texture, v_TexCoords) * u_ColorTint * v_LightIntensity;
}
