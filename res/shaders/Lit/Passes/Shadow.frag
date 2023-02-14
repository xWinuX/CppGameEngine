// Shadows
fragColor *= 1.0-shadowCalculation(
    v_FragWorldPosition,
    u_View,
    u_FrustumPlaneDistances,
    u_LightSpaceMatrices,
    vec3(u_ShadowLightDirection),
    u_FarPlane,
    u_ShadowBias,
    rawNormal,
    u_NumShadowCascades,
    u_CascadedShadowMap
);


