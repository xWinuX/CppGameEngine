#include "../Common/Version.glsl"
#include "../Common/Uniforms.glsl"
#include "../Common/Functions.frag"

#include "Uniforms.frag"

#include "IO.frag"
#include "../Common/IO.frag"

void main()
{
    fragColor = vec4(0.0); 
    
//#include "Passes/AmbientLight.frag"
#include "Passes/PointLight.frag"
//#include "Passes/Texture.frag"
//#include "Passes/ColorTint.frag"
    
}