#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "../Lit/Uniforms.frag"

uniform sampler2D u_TextureRed;
uniform sampler2D u_TextureGreen;
uniform sampler2D u_TextureBlue;

uniform float u_TilingFactor;

#include "../Lit/IO.frag"
in vec4 v_Color;

#include "../Common/IO.frag"

void main()
{
    fragColor = vec4(0.0);

    #include "../Lit/Passes/DirectionalLight.frag"
    #include "../Lit/Passes/PointLight.frag"
    #include "../Lit/Passes/Shadow.frag"
    #include "../Lit/Passes/AmbientLight.frag"

    vec4 textureColor = vec4(0.0);
    vec4 normalizedColor = normalize(v_Color);
    textureColor += texture(u_TextureRed, v_Position.xz*u_TilingFactor) * v_Color.r;
    textureColor += texture(u_TextureGreen, v_Position.xz*u_TilingFactor) * v_Color.g;
    textureColor += texture(u_TextureBlue, v_Position.xz*u_TilingFactor) * v_Color.b;
    fragColor *= textureColor;
    #include "../Lit/Passes/ColorTint.frag"
}