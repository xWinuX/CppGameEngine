vec4 skyboxColor = mix(vec4(0.0), texture(u_SkyboxCubeMap, reflect(-viewDirection, normal)), u_Smoothness);
skyboxColor *= length(fragColor);
// Fake slight skybox reflection with non metallic materials
fragColor += mix(vec4(0.0),skyboxColor * 0.05f, u_Smoothness);
// Skybox contributes to final color based on metallic value
fragColor *= mix(vec4(1.0), mix(albedo, skyboxColor, u_Metallicness), u_Smoothness);
