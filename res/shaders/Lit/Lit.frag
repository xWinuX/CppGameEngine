#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "Uniforms.frag"

#include "IO.frag"
#include "../Common/IO.frag"


void main()
{
    fragColor = vec4(0.0);
    #include "Passes/Normals.frag"
    #include "Passes/DirectionalLight.frag"
    #include "Passes/PointLight.frag"
    #include "Passes/Shadow.frag"
    #include "Passes/AmbientLight.frag"
    #include "Passes/Texture.frag"
    #include "Passes/ColorTint.frag"
}