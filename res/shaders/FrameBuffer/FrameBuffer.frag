#include "../Common/Version.glsl"

in vec2 v_UVs;
uniform sampler2D u_Texture;

const vec2 screenSize = vec2(1920, 1080);
const vec3 bloomFactor = vec3(1.0, 1.0, 1.0);
const int blurSize = 3;

vec4 sampleColor(sampler2D tex, vec2 uv, vec2 offset)
{
    return texture(tex, uv + offset / screenSize);
}

#include "../Common/IO.frag"

void main()
{
    vec4 color = texture(u_Texture, v_UVs);
    float average = (color.r + color.g + color.b) / 3;
    
    vec4 bloom = vec4(0.0);
    for (int i = -blurSize; i <= blurSize; i++)
    {
        for (int j = -blurSize; j <= blurSize; j++)
        {
            vec2 offset = vec2(float(i), float(j))*3;
            bloom += sampleColor(u_Texture, v_UVs, offset);
        }
    }
    bloom /= (blurSize * 2 + 1) * (blurSize * 2 + 1);
    
    fragColor = vec4(color.rgb + bloom.rgb * average, color.a);
}