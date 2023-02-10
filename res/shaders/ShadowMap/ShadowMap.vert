#include "../Common/Version.glsl"

layout (location = 0) in vec3 a_Pos;

#include "../Common/Functions.vert"
#include "../Common/Uniforms.glsl"

uniform mat4 u_LightSpace;

void main() 
{
    gl_Position = u_LightSpace * u_Transform * vec4(a_Pos.xyz, 1.0);
}
