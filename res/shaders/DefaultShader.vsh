#version 400 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normals;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Transform;
uniform int u_NumPointLights;
uniform vec3 u_PointLightPositions[8];

out vec2 v_TexCoords;
out vec3 v_Normal;
out float v_LightIntensity;

void main()
{
    float diffuseSum = 0;
    for (int i = 0; i < u_NumPointLights; i++)
    {
        vec3 modelViewVertex = vec3(u_Transform * vec4(pos, 1.0));
        vec3 modelViewNormal = vec3(u_Transform *  vec4(normals.xyz, 0.0));
        float distance = length(u_PointLightPositions[i] - modelViewVertex);
        vec3 lightVector = normalize(u_PointLightPositions[i] - modelViewVertex);
        float diffuse = max(dot(modelViewNormal, lightVector), 0.1);
        diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));
        diffuseSum += diffuse;
    }

    v_LightIntensity = diffuseSum;
    gl_Position = u_Projection * u_View * u_Transform * vec4(pos, 1.0);
    
    v_TexCoords = texCoords;
    v_Normal = normals;
}
