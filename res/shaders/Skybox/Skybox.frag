#include "../Common/Version.glsl"

#include "../Common/IO.frag"

in vec3 v_TexCoords;

uniform samplerCube u_CubeMap;

void main() 
{
    fragColor = texture(u_CubeMap, v_TexCoords) * 1.2;    
}
