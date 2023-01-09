#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.glsl"

#include "Uniforms.frag"

#include "IO.frag"

void main()
{
    vec4 diffuseSum = u_AmbientLightColor * u_AmbientLightIntensity;
    for (int i = 0; i < u_NumPointLights; i++)
    {
        diffuseSum += calculatePointLightColor(v_Position, u_PointLightPositions[i], u_PointLightColors[i], u_PointLightRanges[i], u_PointLightIntensities[i], u_NormalMap, u_NormalMapIntensity, v_TexCoords, v_TBN);
    }

    fragColor = texture2D(u_Texture, v_TexCoords) * u_ColorTint * diffuseSum;
}
