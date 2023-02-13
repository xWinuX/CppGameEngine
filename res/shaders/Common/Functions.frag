vec4 calculatePointLightColor(
    vec4 albedo,
    vec3 fragPosition,
    vec3 viewDirection,
    vec3 lightPosition,
    vec4 lightColor,
    float range,
    float intensity,
    float smoothness,
    float metallicness,
    vec3 normal
)
{
    vec4 diffuseSum = vec4(0);
    
    // Diffuse
    float distance = length(lightPosition - fragPosition);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diffuse = max(dot(normal, lightDirection), 0.0);
    float distanceFactor = clamp(1.0 - distance*distance/(range*range), 0.0, 1.0);
    diffuseSum += lightColor * intensity * diffuse * distanceFactor;

    // Specular
    vec3 halfwayVector = normalize(lightDirection + viewDirection);
    float specular = pow(max(dot(normal, halfwayVector), 0.0), 1 + (smoothness*1000));
    
    // Calculate how much the albedo contributes to the color of the specular highlight based on the metallicness level
    vec4 specularColor = lightColor * mix(vec4(1.0), albedo, metallicness);
    
    vec4 specularSum = specularColor * intensity * specular * distanceFactor;

    return (albedo * diffuseSum) + specularSum;
}

vec4 calculateDirectionalLightColor(
    vec4 albedo,
    vec3 fragPosition,
    vec3 viewDirection,
    vec3 lightDirection,
    vec4 lightColor,
    float intensity,
    float smoothness,
    float metallicness,
    vec3 normal
)
{
    vec4 diffuseSum = vec4(0);
    
    // Diffuse
    float diffuse = max(dot(normal, lightDirection), 0.0);
    diffuseSum += lightColor * intensity * diffuse;

    // Specular
    vec3 halfwayVector = normalize(lightDirection + viewDirection);
    float specular = pow(max(dot(normal, halfwayVector), 0.0), 1 + (smoothness*1000));

    // Calculate how much the albedo contributes to the color of the specular highlight based on the metallicness level
    vec4 specularColor = lightColor * mix(vec4(1.0), albedo, metallicness);

    vec4 specularSum = specularColor * intensity * specular;

    return (albedo * diffuseSum) + specularSum;
}


float shadowCalculation(
    vec3 fragPosition,
    mat4 viewMatrix,
    float frustumPlaneDistances[16],
    mat4 lightMatrices[16],
    vec3 lightDir,
    float farPlane,
    vec3 normal,
    int cascadeCount,
    sampler2DArray shadowMap
)
{
    vec4 fragPosViewSpace = viewMatrix * vec4(fragPosition, 1.0);
    float depthValue = abs(fragPosViewSpace.z);

    // Check which cascade should be used to shade this pixel
    int layer = -1;
    for (int i = 0; i < cascadeCount; ++i)
    {
        if (depthValue < frustumPlaneDistances[i])//TODO: Replace with var
        {
            layer = i;
            break;
        }
    }
    if (layer == -1) { layer = cascadeCount; }


    // Transform fragment to lightspace and apply the projection then transform to 0-1
    vec4 fragPosLightSpace = lightMatrices[layer] * vec4(fragPosition, 1.0);
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Get depth of current fragment, return no shadow if there is no depth
    float currentDepth = projCoords.z;
    if (currentDepth  > 1.0) { return 0.0; }
    
    // Calculate bias based on normal
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    if (layer == cascadeCount){ bias *= 1 / (farPlane * 0.5f); }
    else { bias *= 1 / (frustumPlaneDistances[layer] * 0.5f); }

    // Blur shadow
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(shadowMap, 0));
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float bluredDepth = texture(shadowMap, vec3(projCoords.xy + vec2(x, y) * texelSize, layer)).r;
            shadow += (currentDepth - bias) > bluredDepth ? 1.0 : 0.0;
        }
    }
    
    // Average out blurred shadow
    shadow /= 9.0;
    
    return shadow;
}