#include "../Common/Version.glsl"

layout(triangles, invocations = 5) in;
layout(triangle_strip, max_vertices = 3) out;

#include "../Lit/LightData.glsl"

in vec2 v_TexCoordsGeometry[];
out vec2 v_TexCoords;

void main()
{
    for (int i = 0; i < 3; ++i)
    {
        gl_Position = u_LightSpaceMatrices[gl_InvocationID] * gl_in[i].gl_Position;
        gl_Layer = gl_InvocationID;
        v_TexCoords = v_TexCoordsGeometry[i];
        EmitVertex();
    }
    EndPrimitive();
}
