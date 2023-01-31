#include "../Common/Version.glsl"

in vec2 v_UVs;

uniform sampler2D u_Texture;

uniform float u_Brightness;
uniform float u_Contrast;
uniform bool u_Grayscale;

uniform bool u_UseHSV;
uniform float u_Hue;
uniform float u_Saturation;
uniform float u_Value;

const vec2 screenSize = vec2(800, 800);

vec4 bloom(sampler2D tex, vec2 uv, float threshold, float intensity) {
    vec4 color = texture2D(tex, uv);
    vec4 blooms = vec4(0);
    vec2 offs = vec2(1/800);// increase the size of the offset
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
    blooms /= 12.0;// divide by the number of samples
    if (length(blooms.rgb) > threshold) {
        color += (blooms - color) * intensity;
    }
    return color;
}

vec3 setBrightness(vec3 color)
{
    return clamp(color + u_Brightness, vec3(0.0), vec3(1.0));
}

vec3 setContrast(vec3 color)
{
    float f = (u_Contrast + 1.0) / (1.01 - u_Contrast);
    return f * (color - 0.5) + 0.5;
}



vec3 rgbToHsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsvToRgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    vec3 color = texture(u_Texture, v_UVs).rgb;

    if (u_Grayscale)
    {
        color = vec3((color.r + color.g + color.b)/3);
    }
    
    if (u_UseHSV)
    {
        vec3 hsv = rgbToHsv(color);
        color = hsvToRgb(vec3(hsv.r*u_Hue, hsv.g*u_Saturation, hsv.b*u_Value));
    }
    else
    {
        color = setBrightness(color);
        color = setContrast(color);
    }

    gl_FragColor = vec4(color, 1.0);
}
