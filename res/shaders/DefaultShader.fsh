#version 400 core

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_Position;

out vec4 fragColor;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Transform;

uniform vec4 u_ColorTint;
uniform sampler2D u_Texture;
uniform sampler2D u_NormalMap;
uniform float u_NormalMapIntensity;

uniform int u_NumPointLights;
uniform vec3 u_PointLightPositions[16];
uniform vec4 u_PointLightColors[16];
uniform float u_PointLightIntensities[16];
uniform float u_PointLightRanges[16];

void main()
{
    vec4 diffuseSum = vec4(0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < u_NumPointLights; i++)
    {
        vec3 normalMapValue = vec3(texture(u_NormalMap, v_TexCoords)) * u_NormalMapIntensity;
        vec3 normal = normalize(v_Normal + (normalMapValue * u_NormalMapIntensity));
        
        float distance = length(u_PointLightPositions[i] - v_Position);
        vec3 lightVector = normalize(u_PointLightPositions[i] - v_Position);
        float diffuse = max(dot(normal, lightVector), 0.1);

        diffuse = diffuse * clamp(1.0 - distance*distance/(u_PointLightRanges[i]*u_PointLightRanges[i]), 0.0, 1.0);
        diffuseSum += u_PointLightColors[i] * u_PointLightIntensities[i] * diffuse;
    }
    
    fragColor = texture2D(u_Texture, v_TexCoords) * u_ColorTint * diffuseSum;
}
