uniform float u_Time;
uniform mat4 u_Transform;

layout(std140, binding = 1) uniform Camera {
    //float u_FarPlane;
    mat4 u_ViewProjection;
    mat4 u_Projection;
    mat4 u_View;
    vec3 u_ViewPosition;
};
