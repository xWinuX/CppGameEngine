mat3 calculateTBN(mat4 transform, vec3 normals, vec4 tangents)
{
    vec3 bitTangent = cross(normals, tangents.xyz) * tangents.w;

    vec3 T = normalize(vec3(transform * vec4(tangents.xyz, 0.0)));
    vec3 B = normalize(vec3(transform * vec4(bitTangent.xyz, 0.0)));
    vec3 N = normalize(vec3(transform * vec4(normals.xyz, 0.0)));

    return mat3(T, B, N);
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