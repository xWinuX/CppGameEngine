#include "../Common/Version.glsl"
#include "../Common/Layout.glsl"
#include "../Common/Functions.glsl"
#include "../Common/Uniforms.glsl"

#include "../Default/Layout.glsl"

#include "../Default/IO.vert"
out float v_WaveHeight;

void main() 
{
    vec3 vertexPosition = a_Position;
    
    float dist = distance(a_Position, vec3(0));
    v_WaveHeight = clamp(sin((u_Time + dist)*3.0), -1.0, 1.0)*0.2;
    vertexPosition += vec3(0.0, v_WaveHeight, 0.0);    
    
    v_TBN = calculateTBN(u_Transform, a_Normals, a_Tangents);

    gl_Position = u_ViewProjection * u_Transform * vec4(vertexPosition, 1.0);
    
    v_Position = vec3(u_Transform * vec4(vertexPosition, 1.0));

    v_TexCoords = a_TextureCoords;
}
