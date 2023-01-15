#include "../Common/Version.glsl"
layout (location = 0) in int a_VertexIndex;
layout (location = 1) in float a_AspectRatio;
layout (location = 2) in vec2 a_TextureCoords;
layout (location = 3) in vec4 a_Color;
#include "../Common/Functions.glsl"
#include "../Common/Uniforms.glsl"

#include "../Lit/IO.vert"

vec4 positions[] = {
    vec4(0.0, 0.0, 0.0, 1.0),
    vec4(1.0, 0.0, 0.0, 1.0),
    vec4(0.0, 1.0, 0.0, 1.0),
    vec4(1.0, 1.0, 0.0, 1.0)
};

void main()
{
    v_Position = calculateWorldSpacePosition(u_Transform, positions[a_VertexIndex]);

    gl_Position = calculateNDCPosition(u_ViewProjection, v_Position);

    v_TBN = calculateTBN(u_Transform, vec3(0.0, 0.0, 1.0), vec4(0.0, 1.0, 0.0, 1.0));

    v_TexCoords = a_TextureCoords;
}
