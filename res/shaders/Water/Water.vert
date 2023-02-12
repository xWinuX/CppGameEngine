#include "../Common/Version.glsl"
#include "../Common/Layout.glsl"
#include "../Common/Functions.vert"
#include "../Common/Uniforms.glsl"

#include "../Lit/IO.vert"
out float v_WaveHeight;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() 
{
    vec3 vertexPosition = a_Position;
    
    float dist = distance(a_Position, vec3(0));
    v_WaveHeight = (sin((u_Time + (dist*0.3))*1.0) * 0.3) + rand(vec2(a_Position.x, a_Position.z)) * 0.1;
    vertexPosition += vec3(0.0, v_WaveHeight, 0.0);
    
    v_Position = calculateWorldSpacePosition(u_Transform, vertexPosition);
    gl_Position = calculateNDCPosition(u_ViewProjection, v_Position);
    v_TBN = calculateTBN(u_Transform, a_Normals, a_Tangents);
    v_TexCoords = a_TextureCoords;
}
