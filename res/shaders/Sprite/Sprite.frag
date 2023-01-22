#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "Uniforms.frag"

#include "../Common/IO.frag"
#include "IO.frag"

void main()
{
    vec4 textureColor = texture2D(u_Texture, v_TexCoords);
    if (textureColor.a < 0.5) { discard; }

    fragColor = textureColor * v_Color;
}