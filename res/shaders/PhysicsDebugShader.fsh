#version 400 core
in vec3 v_Color;

out vec4 fragColor;

void main()
{
    fragColor = vec4(v_Color.rbg, 1.0);
}
