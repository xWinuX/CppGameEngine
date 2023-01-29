﻿#include "../Common/Version.glsl"

#include "../Sprite/Attributes.vert"

#include "../Common/Functions.vert"

#include "../Common/Uniforms.glsl"

#include "../Sprite/IO.vert"
out mat3 v_TBN;

void main()
{ 
#include "../Sprite/Main.vert"

    v_TBN = mat3(vec3(1.0, 0.0, 0.0),vec3(0.0, 1.0, 0.0),vec3(1.0, 0.0, 0.0));
}