uniform vec4 u_ColorTint;
uniform sampler2D u_Texture;
uniform sampler2D u_NormalMap;
uniform float u_NormalMapIntensity;

uniform vec4 u_AmbientLightColor;
uniform float u_AmbientLightIntensity;

uniform int u_NumPointLights;
uniform vec3 u_PointLightPositions[16];
uniform vec4 u_PointLightColors[16];
uniform float u_PointLightIntensities[16];
uniform float u_PointLightRanges[16];