#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "../Lit/Uniforms.frag"
#include "../Sprite/Uniforms.frag"

#include "../Common/IO.frag"
#include "../Sprite/IO.frag"

in mat3 v_TBN;

void main()
{
    vec4 albedo = texture2D(u_Texture, v_TexCoords);
    if (albedo.a < 0.5) { discard; }
    
    fragColor = vec4(0.0);
    #include "../Lit/Passes/PreCalcs.frag"
    albedo *= v_Color;
    #include "../Lit/Passes/DirectionalLight.frag"
    #include "../Lit/Passes/Shadow.frag"
    #include "../Lit/Passes/AmbientLight.frag"
    #include "../Lit/Passes/PointLight.frag"
    #include "../Lit/Passes/SkyboxReflection.frag"
}