#include "../Common/Version.glsl"

uniform sampler2D u_Texture;

in vec4 v_Color;
in vec2 v_TextureCoords;

void main() 
{
    gl_FragColor = texture(u_Texture, v_TextureCoords) * v_Color;
}
