int vertexIndex = gl_VertexID % 4;
v_FragWorldPosition = calculateWorldSpacePosition(a_Transform, vec3(a_PositionsAndUVs[vertexIndex].xy, 0.0));

gl_Position = calculateNDCPosition(u_ViewProjection, v_FragWorldPosition);

v_TexCoords = a_PositionsAndUVs[vertexIndex].zw;
v_Color = a_Colors[vertexIndex];