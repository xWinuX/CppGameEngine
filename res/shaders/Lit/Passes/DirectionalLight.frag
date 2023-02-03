for (int i = 0; i < u_NumDirectionalLights; i++)
{
    fragColor += calculateDirectionalLightColor(
    v_Position,
    u_ViewPosition,
    u_DirectionalLightDirections[i],
    u_DirectionalLightColors[i],
    u_DirectionalLightIntensities[i],
    u_Shininess,
    u_NormalMap,
    v_TexCoords,
    v_TBN
    );
}