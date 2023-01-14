mat3 calculateTBN(mat4 transform, vec3 normals, vec4 tangents)
{
    vec3 bitTangent = cross(normals, tangents.xyz) * tangents.w;

    vec3 T = normalize(vec3(transform * vec4(tangents.xyz, 0.0)));
    vec3 B = normalize(vec3(transform * vec4(bitTangent.xyz, 0.0)));
    vec3 N = normalize(vec3(transform * vec4(normals.xyz, 0.0)));

    return mat3(T, B, N);
}

vec4 calculatePointLightColor(vec3 fragPosition, vec3 position, vec4 color, float range, float intensity, sampler2D normalMap, float normalMapIntensity, vec2 uvs, mat3 tbn)
{
    vec4 diffuseSum = vec4(0);

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

vec4 calculateNDCPosition(mat4 viewProjection, mat4 transform, vec3 position)
{
    return viewProjection * transform * vec4(position, 1.0);
}

vec4 calculateNDCPosition(mat4 viewProjection, vec3 worldPosition)
{
    return viewProjection * vec4(worldPosition, 1.0);
}

vec3 calculateWorldSpacePosition(mat4 transform, vec3 position)
{
    return vec3(transform * vec4(position, 1.0));
}