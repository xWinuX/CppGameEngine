#include "../Common/Version.glsl"
#include "../Common/Layout.glsl"
#include "../Common/Functions.vert"
#include "../Common/Uniforms.glsl"

#include "../Lit/IO.vert"

uniform vec3 u_WaveOrigin;
uniform float u_WaveSpeed;
uniform float u_WaveAmplitude;
uniform float u_WaveFrequency;

out float v_WaveHeight;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() 
{
    vec3 vertexPosition = a_Position;
    
    float dist = distance(a_Position, u_WaveOrigin);
    v_WaveHeight = (sin((u_Time + (dist*u_WaveFrequency))*u_WaveSpeed) * u_WaveAmplitude) + rand(vec2(a_Position.x, a_Position.z)) * 0.1;
    vertexPosition += vec3(0.0, v_WaveHeight, 0.0);
    
    v_FragWorldPosition = calculateWorldSpacePosition(u_Transform, vertexPosition);
    gl_Position = calculateNDCPosition(u_ViewProjection, v_FragWorldPosition);
    v_TBN = calculateTBN(u_Transform, a_Normals, a_Tangents);
    v_TexCoords = a_TextureCoords;
}
