int vertexIndex = gl_VertexID % 4;
v_Position = calculateWorldSpacePosition(a_Transform, positions[vertexIndex]*vec3(a_SizeAndOrigin.x, a_SizeAndOrigin.y, 0.0));

gl_Position = calculateNDCPosition(u_ViewProjection, v_Position);

v_TexCoords = a_TextureCoords[vertexIndex];
v_Color = a_Colors[vertexIndex];