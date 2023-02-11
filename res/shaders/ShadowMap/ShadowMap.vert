#include "../Common/Version.glsl"

layout (location = 0) in vec3 a_Pos;

#include "../Common/Functions.vert"
#include "../Common/Uniforms.glsl"

#include "../Lit/LightData.glsl"

void main() 
{
    gl_Position = u_LightSpaceMatrix * u_Transform * vec4(a_Pos.xyz, 1.0);
}
