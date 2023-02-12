vec4 calculatePointLightColor(
vec3 fragPosition,
vec3 viewPosition,
vec3 lightPosition,
vec4 color,
float range,
float intensity,
float shininess,
vec3 normal
)
{
    vec4 diffuseSum = vec4(0);
    
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
vec3 normal
)
{
    vec4 diffuseSum = vec4(0);
    
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

    vec4 fragPosLightSpace = lightMatrices[layer] * vec4(fragPosition, 1.0);


    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    if (currentDepth  > 1.0)
    {
        return 0.0;
    }


    // calculate bias (based on depth map resolution and slope)

    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    if (layer == cascadeCount)
    {
        bias *= 1 / (farPlane * 0.5f);
    }
    else
    {
        bias *= 1 / (frustumPlaneDistances[layer] * 0.5f);
    }

    // PCF
   
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(shadowMap, 0));
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(
            shadowMap,
            vec3(projCoords.xy + vec2(x, y) * texelSize,
            layer)
            ).r;
            shadow += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    return shadow;
}