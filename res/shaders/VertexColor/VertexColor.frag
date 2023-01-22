#include "../Common/Version.glsl"

uniform sampler2D u_Texture;

in vec4 v_Color;
in vec2 v_TextureCoords;

#include "../Common/IO.frag"

void main() 
{
    fragColor = texture(u_Texture, v_TextureCoords) * v_Color;
}
