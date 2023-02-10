﻿uniform vec4 u_ColorTint;
uniform samplerCube u_SkyboxCubeMap;

uniform sampler2D u_Texture;
uniform sampler2D u_NormalMap;
uniform float u_NormalMapIntensity;

uniform float u_Shininess;

#define MAX_POINT_LIGHTS 16
#define MAX_DIRECTIONAL_LIGHTS 3
#define MAX_SHADOW_CASTERS 3

layout(std140, binding = 2) uniform Lights {
    vec4 u_AmbientLightColor;

    vec4 u_PointLightPositions[MAX_POINT_LIGHTS];
    vec4 u_PointLightColors[MAX_POINT_LIGHTS];
    float u_PointLightIntensities[MAX_POINT_LIGHTS];
    float u_PointLightRanges[MAX_POINT_LIGHTS];

    vec4 u_DirectionalLightDirections[MAX_DIRECTIONAL_LIGHTS];
    vec4 u_DirectionalLightColors[MAX_DIRECTIONAL_LIGHTS];
    float u_DirectionalLightIntensities[MAX_DIRECTIONAL_LIGHTS];
    
    mat4 u_LightSpaceMatrices[MAX_SHADOW_CASTERS];

    float u_AmbientLightIntensity;
    int u_NumPointLights;
    int u_NumDirectionalLights;
    int u_NumShadowCasters;
};

uniform sampler2D u_ShadowMap;