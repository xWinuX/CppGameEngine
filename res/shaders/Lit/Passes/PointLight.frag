for (int i = 0; i < u_NumPointLights; i++)
{
    fragColor += calculatePointLightColor(
    v_Position, 
    u_ViewPosition,
    vec3(u_PointLightPositions[i]), 
    u_PointLightColors[i], 
    u_PointLightRanges[i], 
    u_PointLightIntensities[i],
    u_Shininess,
    u_NormalMap, 
    v_TexCoords, 
    v_TBN
    );
}