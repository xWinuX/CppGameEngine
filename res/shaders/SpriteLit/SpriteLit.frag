#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "../Lit/Uniforms.frag"

#include "../Common/IO.frag"
#include "../Sprite/IO.frag"

in mat3 v_TBN;

void main()
{
    vec4 textureColor = texture2D(u_Texture, v_TexCoords);
    if (textureColor.a < 0.5) { discard; }

    fragColor = vec4(0.0);
    #include "../Lit/Passes/Normals.frag"
    #include "../Lit/Passes/DirectionalLight.frag"
    #include "../Lit/Passes/PointLight.frag"
    #include "../Lit/Passes/Shadow.frag"
    #include "../Lit/Passes/AmbientLight.frag"
    fragColor *= textureColor;
    fragColor *= v_Color;
}