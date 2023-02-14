#define MAX_POINT_LIGHTS 16
#define MAX_SHADOW_CASCADES 16
#define MAX_DIRECTIONAL_LIGHTS 3

layout(std140, binding = 2) uniform Lights 
{
    vec4 u_ShadowLightDirection;

    vec4 u_PointLightPositions[MAX_POINT_LIGHTS];
    vec4 u_PointLightColors[MAX_POINT_LIGHTS];
    float u_PointLightIntensities[MAX_POINT_LIGHTS];
    float u_PointLightRanges[MAX_POINT_LIGHTS];

    vec4 u_DirectionalLightDirections[MAX_DIRECTIONAL_LIGHTS];
    vec4 u_DirectionalLightColors[MAX_DIRECTIONAL_LIGHTS];
    float u_DirectionalLightIntensities[MAX_DIRECTIONAL_LIGHTS];

    float u_FrustumPlaneDistances[MAX_SHADOW_CASCADES];
    mat4 u_LightSpaceMatrices[MAX_SHADOW_CASCADES];

    float u_AmbientLightIntensity;
    float u_ShadowBias;

    int u_NumPointLights;
    int u_NumDirectionalLights;
    int u_NumShadowCascades;
};