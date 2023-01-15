#include "../Common/Version.glsl"
#include "../Common/Layout.glsl"
#include "../Common/Functions.vert"
#include "../Common/Uniforms.glsl"

#include "../Lit/IO.vert"
out float v_WaveHeight;

void main() 
{
    vec3 vertexPosition = a_Position;
    
    float dist = distance(a_Position, vec3(0));
    v_WaveHeight = clamp(sin((u_Time + dist)*3.0), -1.0, 1.0)*0.2;
    vertexPosition += vec3(0.0, v_WaveHeight, 0.0);
    
    v_Position = calculateWorldSpacePosition(u_Transform, vertexPosition);
    gl_Position = calculateNDCPosition(u_ViewProjection, v_Position);
    v_TBN = calculateTBN(u_Transform, a_Normals, a_Tangents);
    v_TexCoords = a_TextureCoords;
}
