uniform vec4 u_ColorTint;
uniform samplerCube u_SkyboxCubeMap;

uniform sampler2D u_Texture;
uniform sampler2D u_NormalMap;
uniform float u_NormalMapIntensity;

uniform float u_Shininess;

uniform vec4 u_AmbientLightColor;
uniform float u_AmbientLightIntensity;

#define MAX_POINT_LIGHTS 16
uniform int u_NumPointLights = 0;
uniform vec3 u_PointLightPositions[MAX_POINT_LIGHTS];
uniform vec4 u_PointLightColors[MAX_POINT_LIGHTS];
uniform float u_PointLightIntensities[MAX_POINT_LIGHTS];
uniform float u_PointLightRanges[MAX_POINT_LIGHTS];

#define MAX_DIRECTIONAL_LIGHTS 3
uniform int u_NumDirectionalLights = 0;
uniform vec3 u_DirectionalLightDirections[MAX_DIRECTIONAL_LIGHTS];
uniform vec4 u_DirectionalLightColors[MAX_DIRECTIONAL_LIGHTS];
uniform float u_DirectionalLightIntensities[MAX_DIRECTIONAL_LIGHTS];
