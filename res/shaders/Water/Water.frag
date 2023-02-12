#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "../Lit/Uniforms.frag"

#include "../Common/IO.frag"
#include "../Lit/IO.frag"
in float v_WaveHeight;

void main()
{
    fragColor = vec4(0.0);

    #include "../Lit/Passes/Normals.frag"
    #include "../Lit/Passes/DirectionalLight.frag"
    #include "../Lit/Passes/PointLight.frag"
    #include "../Lit/Passes/Shadow.frag"
    #include "../Lit/Passes/AmbientLight.frag"

    fragColor = vec4(0.0, v_WaveHeight, 1.0, 1.0) * vec4(fragColor.rgb, 0.7);
}
