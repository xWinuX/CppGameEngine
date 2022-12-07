#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct VertexPos
{
    public:
        glm::vec3 Position;
};

struct VertexPosCol : VertexPos
{
    public:
        glm::vec4 Color;
};

struct VertexPosColTex : VertexPosCol
{
    public:
        glm::vec2 TexCoords;
};