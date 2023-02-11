uniform vec4 u_ColorTint;
uniform samplerCube u_SkyboxCubeMap;

uniform sampler2D u_Texture;
uniform sampler2D u_NormalMap;
uniform float u_NormalMapIntensity;

uniform float u_Shininess;

#include "LightData.glsl"

uniform sampler2D u_ShadowMap;