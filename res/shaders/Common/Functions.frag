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
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diffuse = max(dot(normal, lightDirection), 0.0);
    float distanceFactor = clamp(1.0 - distance*distance/(range*range), 0.0, 1.0);
    diffuseSum += color * intensity * diffuse * distanceFactor;

    // Specular
    float lambertian = max(dot(lightDirection, normal), 0.0);
    
    vec3 viewVector = normalize(viewPosition-fragPosition);
    vec3 halfwayVector = normalize(lightDirection + viewVector);
    float specular = pow(max(dot(normal, halfwayVector), 0.0), 1 + (shininess*1000));
    vec4 specularSum = color * intensity * specular * distanceFactor * lambertian;

    return diffuseSum + specularSum;
}

vec4 calculateDirectionalLightColor(
    vec3 fragPosition,
    vec3 viewPosition,
    vec3 lightDirection,
    vec4 color,
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
    float diffuse = max(dot(normal, lightDirection), 0.0);
    diffuseSum += color * intensity * diffuse;

    // Specular
    float lambertian = max(dot(lightDirection, normal), 0.0);

    vec3 viewVector = normalize(viewPosition-fragPosition);
    vec3 halfwayVector = normalize(lightDirection + viewVector);
    float specular = pow(max(dot(normal, halfwayVector), 0.0), 1 + (shininess*1000));
    vec4 specularSum = color * intensity * specular * lambertian;

    return diffuseSum + specularSum;
}