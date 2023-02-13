vec4 skyboxColor = mix(vec4(0.0), texture(u_SkyboxCubeMap, reflect(-viewDirection, normal)), u_Smoothness);
// Fake slight skybox reflection with non metallic materials
fragColor += skyboxColor * 0.05f;
// Skybox contributes to final color based on metallic value
fragColor *= mix(albedo, skyboxColor, u_Metallicness);