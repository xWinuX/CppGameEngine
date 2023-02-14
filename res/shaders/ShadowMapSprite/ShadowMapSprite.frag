#include "../Common/Version.glsl"

#include "../Sprite/Uniforms.frag"

in vec2 v_TexCoords;

void main() 
{
    vec4 textureColor = texture2D(u_Texture, v_TexCoords);
    if (textureColor.a < 0.5) { discard; }
}
