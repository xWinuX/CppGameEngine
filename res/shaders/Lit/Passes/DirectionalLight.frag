// Directional Lights
for (int i = 0; i < u_NumDirectionalLights; i++)
{
    fragColor += calculateDirectionalLightColor(
        albedo,
        v_FragWorldPosition,
        viewDirection,
        vec3(u_DirectionalLightDirections[i]),
        u_DirectionalLightColors[i],
        u_DirectionalLightIntensities[i],
        u_Smoothness,
        u_Metallicness,
        normal
    );
}

