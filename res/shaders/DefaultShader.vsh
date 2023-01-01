#version 400 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TextureCoords;
layout (location = 2) in vec3 a_Normals;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform mat4 u_TransposedInverseTransform;

out vec3 v_Position;
out vec2 v_TexCoords;
out vec3 v_Normal;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
     
    v_Position = vec3(u_Transform * vec4(a_Position, 1.0));
    v_Normal = vec3(u_TransposedInverseTransform * vec4(a_Normals, 1.0));
    v_TexCoords = a_TextureCoords;
}
