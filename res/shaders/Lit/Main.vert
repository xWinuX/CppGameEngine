v_Position = calculateWorldSpacePosition(u_Transform, a_Position);

gl_Position = calculateNDCPosition(u_ViewProjection, v_Position);

v_TBN = calculateTBN(u_Transform, a_Normals, a_Tangents);

v_TexCoords = a_TextureCoords;