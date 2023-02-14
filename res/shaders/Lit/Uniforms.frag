uniform vec4 u_ColorTint;
uniform samplerCube u_SkyboxCubeMap;

uniform sampler2D u_NormalMap;
uniform float u_NormalMapIntensity;

uniform float u_ShadowBias;
uniform float u_Smoothness;
uniform float u_Metallicness;
uniform float u_SkyboxReflectionIntensity;

#include "LightData.glsl"

layout (binding = 15) uniform sampler2DArray u_CascadedShadowMap;