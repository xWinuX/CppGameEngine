vec4 calculatePointLightColor(
    vec3 fragPosition,
    vec3 viewPosition,
    vec3 lightPosition,
    vec4 color,
    float range,
    float intensity,
    float shininess,
    sampler2D normalMap,
    vec2 uvs,
    mat3 tbn
)
{
    vec4 diffuseSum = vec4(0);

    float frontFacingSign = gl_FrontFacing ? 1 : -1;

    tbn[2][0] *= frontFacingSign;
    tbn[2][1] *= frontFacingSign;
    tbn[2][2] *= frontFacingSign;

    // Normal
    vec3 normal = vec3(texture(normalMap, uvs));
    normal = normal * 2.0 - 1.0;
    normal = normalize(tbn * normal);

    // Diffuse
    float distance = length(lightPosition - fragPosition);
    vec3 lightVector = normalize(lightPosition - fragPosition);
    float diffuse = max(dot(normal, lightVector), 0.1);
    diffuse = diffuse * clamp(1.0 - distance*distance/(range*range), 0.0, 1.0);
    diffuseSum += color * intensity * diffuse;

    // Specular
    vec4 specularSum = vec4(0);
    vec3 viewVector = normalize(viewPosition-fragPosition);
    vec3 halfwayVector = normalize(lightVector + viewVector);
    float specular = pow(max(dot(normal, halfwayVector), 0.0), shininess*1000);
    specularSum += color * intensity * specular * diffuse;

    return diffuseSum + specularSum;
}