#include "../Common/Version.glsl"
in vec3 v_Color;

#include "../Common/IO.frag"

void main()
{
    fragColor = vec4(v_Color.rbg, 1.0);
}
