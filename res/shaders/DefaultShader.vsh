#version 400 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normals;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Transform;
uniform int u_NumPointLights;
uniform vec3 u_PointLightPositions[16];
uniform vec4 u_PointLightColors[16];
uniform float u_PointLightIntensities[16];

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec4 v_LightColor;

void main()
{
    vec4 diffuseSum = vec4(0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < u_NumPointLights; i++)
    {
        vec3 modelViewVertex = vec3(u_Transform * vec4(pos, 1.0));
        vec3 modelViewNormal = vec3(u_Transform *  vec4(normals.xyz, 0.0));
        float distance = length(u_PointLightPositions[i] - modelViewVertex);
        vec3 lightVector = normalize(u_PointLightPositions[i] - modelViewVertex);
        float diffuse = max(dot(modelViewNormal, lightVector), 0.1);
        diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));
        diffuseSum += u_PointLightColors[i] * u_PointLightIntensities[i] * diffuse;
    }

    v_LightColor = diffuseSum;
    gl_Position = u_Projection * u_View * u_Transform * vec4(pos, 1.0);
    
    v_TexCoords = texCoords;
    v_Normal = normals;
}
