﻿#include "../Common/Version.glsl"

layout (location = 0) in mat4 a_Transform;
layout (location = 4) in vec4 a_PositionsAndUVs[4];

#include "../Common/Functions.vert"
#include "../Common/Uniforms.glsl"

#include "../Lit/LightData.glsl"

out vec2 v_TexCoords;

void main() 
{
    int vertexIndex = gl_VertexID % 4;
    
    gl_Position = u_LightSpaceMatrices[0] * a_Transform * vec4(vec3(a_PositionsAndUVs[vertexIndex].xy, 0.0), 1.0);

    v_TexCoords = a_PositionsAndUVs[vertexIndex].zw;
}
