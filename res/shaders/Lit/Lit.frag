#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "Uniforms.frag"

#include "IO.frag"
#include "../Common/IO.frag"

void main()
{
    fragColor = vec4(0.0);

    fragColor += vec4(texture(u_SkyboxCubeMap, vec3(0.0)).rgb, 1.0) * u_AmbientLightIntensity;

    //#include "Passes/AmbientLight.frag"
#include "Passes/PointLight.frag"
#include "Passes/Texture.frag"
#include "Passes/ColorTint.frag"
}