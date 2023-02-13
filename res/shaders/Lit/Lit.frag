#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "Uniforms.frag"

#include "IO.frag"
#include "../Common/IO.frag"


void main()
{
    fragColor = vec4(0.0);

    #include "Passes/PreCalcs.frag"
    #include "Passes/Albedo.frag"
    #include "Passes/DirectionalLight.frag"
    #include "Passes/Shadow.frag"
    #include "Passes/AmbientLight.frag"
    #include "Passes/PointLight.frag"
    #include "Passes/SkyboxReflection.frag"
}