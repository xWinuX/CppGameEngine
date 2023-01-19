#include "../Common/Version.glsl"

// Once per Quad
layout (location = 0) in float a_AspectRatio;
layout (location = 1) in mat4 a_Transform;

// Every Vertex
layout (location = 5) in vec2 a_TextureCoords[4];
layout (location = 10) in vec4 a_Colors[4];

#include "../Common/Functions.vert"
#include "../Common/Uniforms.glsl"

#include "../Lit/IO.vert"
out vec4 v_Color;

const vec3 positions[4] = vec3[](
    vec3(0.0, 0.0, 0.1),
    vec3(1.0, 0.0, 0.1),
    vec3(0.0, -1.0, 0.1),
    vec3(1.0, -1.0, 0.1)
);

void main()
{
    int vertexIndex = gl_VertexID % 4;
    v_Position = calculateWorldSpacePosition(a_Transform, positions[vertexIndex]*vec3(a_AspectRatio, 1.0, gl_InstanceID));

    gl_Position = calculateNDCPosition(u_ViewProjection, v_Position);
    
    v_TBN = calculateTBN(u_Transform, vec3(0.0, 0.0, 1.0), vec4(0.0, 1.0, 0.0, 1.0));

    v_TexCoords = a_TextureCoords[vertexIndex];
    v_Color = a_Colors[vertexIndex];
}
