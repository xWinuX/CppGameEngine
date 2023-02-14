mat3 tbn = v_TBN;
float frontFacingSign = gl_FrontFacing ? 1 : -1;
tbn[2][0] *= frontFacingSign;
tbn[2][1] *= frontFacingSign;
tbn[2][2] *= frontFacingSign;

vec3 normal = vec3(texture(u_NormalMap, v_TexCoords));
vec3 rawNormal = vec3(tbn[2][0], tbn[2][1], tbn[2][2]);
normal = normal * 2.0 - 1.0;
normal = normalize(tbn * normal);

vec3 viewDirection = normalize(u_ViewPosition-v_FragWorldPosition);