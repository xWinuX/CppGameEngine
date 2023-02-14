// Point Lights
for (int i = 0; i < u_NumPointLights; i++)
{
    fragColor += calculatePointLightColor(
        albedo,
        v_FragWorldPosition,
        viewDirection,
        vec3(u_PointLightPositions[i]),
        u_PointLightColors[i],
        u_PointLightRanges[i],
        u_PointLightIntensities[i],
        u_Smoothness,
        u_Metallicness,
        normal
    );
}
