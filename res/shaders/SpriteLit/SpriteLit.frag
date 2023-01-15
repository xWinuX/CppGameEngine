#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "../Lit/Uniforms.frag"

#include "../Lit/IO.frag"

void main()
{
    vec4 textureColor = texture2D(u_Texture, v_TexCoords);
    if (textureColor.a == 0) { discard; }

    fragColor = vec4(0.0);
#include "../Lit/Passes/AmbientLight.frag"
#include "../Lit/Passes/PointLight.frag"
    fragColor *= textureColor;
#include "../Lit/Passes/ColorTint.frag"
}