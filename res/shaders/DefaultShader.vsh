#version 400 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normals;
layout (location = 2) in vec4 a_Tangents;
layout (location = 3) in vec2 a_TextureCoords;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec2 v_TexCoords;
out vec3 v_Normal;
out mat3 v_TBN;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
     
    vec3 bitTangent = cross(a_Normals, a_Tangents.xyz) * a_Tangents.w;
    
    vec3 T = normalize(vec3(u_Transform * vec4(a_Tangents.xyz, 0.0)));
    vec3 B = normalize(vec3(u_Transform * vec4(bitTangent.xyz, 0.0)));
    vec3 N = normalize(vec3(u_Transform * vec4(a_Normals.xyz, 0.0)));
    
    v_TBN = mat3(T, B, N);
    
    v_Position = vec3(u_Transform * vec4(a_Position, 1.0));
    v_Normal = vec3(transpose(inverse(u_Transform)) * vec4(a_Normals, 1.0));
    v_TexCoords = a_TextureCoords;
}
