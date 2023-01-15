#include "../Common/Version.glsl"
#include "../Common/Layout.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.vert"

#include "IO.vert"

void main()
{
    v_Position = calculateWorldSpacePosition(u_Transform, a_Position);
    
    gl_Position = calculateNDCPosition(u_ViewProjection, v_Position);
    
    v_TBN = calculateTBN(u_Transform, a_Normals, a_Tangents);
    
    v_TexCoords = a_TextureCoords;
}
