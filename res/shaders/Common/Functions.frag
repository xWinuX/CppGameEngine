vec4 calculatePointLightColor(vec3 fragPosition, vec3 position, vec4 color, float range, float intensity, sampler2D normalMap, float normalMapIntensity, vec2 uvs, mat3 tbn)
{
    vec4 diffuseSum = vec4(0);
    
    tbn[2][0] *= gl_FrontFacing ? 1 : -1;
    tbn[2][1] *= gl_FrontFacing ? 1 : -1;
    tbn[2][2] *= gl_FrontFacing ? 1 : -1;
    
    vec3 normal = vec3(texture(normalMap, uvs));
    normal = normal * 2.0 - 1.0;
    normal = normal * normalMapIntensity;
    normal = normalize(tbn * normal);

    float distance = length(position - fragPosition);
    vec3 lightVector = normalize(position - fragPosition);
    float diffuse = max(dot(normal, lightVector), 0.1);

    diffuse = diffuse * clamp(1.0 - distance*distance/(range*range), 0.0, 1.0);
    diffuseSum += color * intensity * diffuse;

    return diffuseSum;
}