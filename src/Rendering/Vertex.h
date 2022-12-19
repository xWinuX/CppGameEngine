#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct VertexPosition
{
    public:
        explicit VertexPosition(const glm::vec3 position): Position(position)
        {
        }

        glm::vec3 Position;
};


struct VertexNormal
{
    public:
        explicit VertexNormal(const glm::vec3 normal): Normal(normal)
        {
        }

        glm::vec2 Normal;
};


struct VertexUV
{
    public:
        explicit VertexUV(const glm::vec2 texCoords): TexCoords(texCoords)
        {
        }

        glm::vec2 TexCoords;
};


struct VertexColor
{
    public:
        explicit VertexColor(const glm::vec4 color): Color(color)
        {
        }

        glm::vec4 Color;
};

struct VertexPositionUV : VertexPosition, VertexUV
{
    public:
        VertexPositionUV(const glm::vec3 position, const glm::vec2 texCoords): VertexPosition(position), VertexUV(texCoords)
        {
        }
};

struct VertexPositionUVNormal : VertexPosition, VertexUV, VertexNormal
{
    public:
        VertexPositionUVNormal(const glm::vec3 position, const glm::vec2 uv, const glm::vec3 normal): VertexPosition(position), VertexUV(uv), VertexNormal(normal)
        {
        }
};

struct VertexPositionColor : VertexPosition, VertexColor
{
};

struct VertexPositionColorUV : VertexPosition, VertexColor, VertexUV
{
};
