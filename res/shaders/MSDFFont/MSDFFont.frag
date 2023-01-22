#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "../Sprite/Uniforms.frag"
//uniform vec2 u_UnitRange = vec2(2.0); // MSDF Pixel Range / Atlas Size

#include "../Common/IO.frag"
#include "../Sprite/IO.frag"


float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

float screenPxRange() {
    vec2 unitRange = vec2(2.0)/vec2(textureSize(u_Texture, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(v_TexCoords);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

void main()
{
    vec3 sampleColor = texture(u_Texture, v_TexCoords).rgb;
    float medianOfAllColorChannels = median(sampleColor.r, sampleColor.g, sampleColor.b);
    float screenPxDistance = screenPxRange()*(medianOfAllColorChannels - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
    if (opacity < 0.5) { discard; }
    fragColor = vec4(v_Color.rgb, opacity);
}