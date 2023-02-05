#include "../Common/Version.glsl"

layout (location = 0) in vec3 a_Pos;

#include "../Common/Uniforms.glsl"

out vec3 v_TexCoords;

void main() 
{
    vec4 pos = u_Projection * u_View * vec4(a_Pos, 1.0f);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    v_TexCoords = vec3(a_Pos.x, a_Pos.y, -a_Pos.z);
}
