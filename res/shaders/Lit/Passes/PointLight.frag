for (int i = 0; i < u_NumPointLights; i++)
{
    fragColor += calculatePointLightColor(v_Position, u_PointLightPositions[i], u_PointLightColors[i], u_PointLightRanges[i], u_PointLightIntensities[i], u_NormalMap, u_NormalMapIntensity, v_TexCoords, v_TBN);
}