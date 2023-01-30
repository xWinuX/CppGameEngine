#include "../Common/Version.glsl"

in vec2 v_UVs;

uniform sampler2D u_Texture;

const vec2 screenSize = vec2(800, 800);


vec4 bloom(sampler2D tex, vec2 uv, float threshold, float intensity) {
    vec4 color = texture2D(tex, uv);
    vec4 blooms = vec4(0);
    vec2 offs = vec2(1/800); // increase the size of the offset
    blooms += texture2D(tex, uv + offs * vec2(0, 1));
    blooms += texture2D(tex, uv + offs * vec2(1, 0));
    blooms += texture2D(tex, uv - offs * vec2(0, 1));
    blooms += texture2D(tex, uv - offs * vec2(1, 0));
    blooms += texture2D(tex, uv + offs * vec2(1, 1));
    blooms += texture2D(tex, uv - offs * vec2(1, -1));
    blooms += texture2D(tex, uv - offs * vec2(-1, 1));
    blooms += texture2D(tex, uv + offs * vec2(-1, -1));
    blooms += texture2D(tex, uv + offs * vec2(2, 0));
    blooms += texture2D(tex, uv - offs * vec2(-2, 0));
    blooms += texture2D(tex, uv + offs * vec2(0, 2));
    blooms += texture2D(tex, uv - offs * vec2(0, -2));
    blooms /= 12.0; // divide by the number of samples
    if (length(blooms.rgb) > threshold) {
        color += (blooms - color) * intensity;
    }
    return color;
}

void main()
{
    gl_FragColor = bloom(u_Texture, v_UVs, 0.8, 1.0);
}
