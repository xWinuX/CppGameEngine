#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct VertexPos
{
    public:
        explicit VertexPos(const glm::vec3 position): Position(position) {}
        glm::vec3 Position;
};

struct VertexTex
{
    public:
        explicit VertexTex(const glm::vec2 texCoords): TexCoords(texCoords) {}
        glm::vec2 TexCoords;
};


struct VertexCol
{
    public:
        explicit VertexCol(const glm::vec4 color): Color(color) {}
        glm::vec4 Color;
};

struct VertexPosTex : VertexPos, VertexTex
{
    public:
        VertexPosTex(const glm::vec3 position, const glm::vec2 texCoords): VertexPos(position), VertexTex(texCoords) {}
};

struct VertexPosCol : VertexPos, VertexCol
{
};

struct VertexPosColTex : VertexPos, VertexCol, VertexTex
{
};
