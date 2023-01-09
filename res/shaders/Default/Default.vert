#include "../Common/Version.glsl"
#include "../Common/Functions.glsl"
#include "../Common/Layout.glsl"
#include "../Common/Uniforms.glsl"

#include "IO.vert"

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
    
    v_TBN = calculateTBN(u_Transform, a_Normals, a_Tangents);
    
    v_Position = vec3(u_Transform * vec4(a_Position, 1.0));
    
    v_TexCoords = a_TextureCoords;
}
