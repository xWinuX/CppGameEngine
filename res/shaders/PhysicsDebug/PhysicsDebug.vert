#include "../Common/Version.glsl"

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Colors;

#include "../Common/Uniforms.glsl"

out vec3 v_Color;

void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
    v_Color = a_Colors;    
}
