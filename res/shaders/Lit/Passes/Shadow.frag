// Shadows
fragColor *= 1.0-shadowCalculation(
    v_Position,
    u_View,
    u_FrustumPlaneDistances,
    u_LightSpaceMatrices,
    vec3(u_ShadowLightDirection),
    u_FarPlane,
    normal,
    u_NumShadowCascades,
    u_CascadedShadowMap
);


