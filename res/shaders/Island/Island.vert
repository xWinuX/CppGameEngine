#include "../Common/Version.glsl"
#include "../Common/Layout.glsl"
layout (location = 4) in vec4 a_Color;
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.vert"

#include "../Lit/IO.vert"

out vec4 v_Color;

void main() 
{
#include "../Lit/Main.vert"
    v_Color = a_Color;
}
