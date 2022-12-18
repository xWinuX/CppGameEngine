#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/vec2.hpp>

class Texture
{
    private:
        GLuint      _textureID;
        std::string _filePath;
        glm::ivec2  _size;
        int _bitsPerPixel;
    public:
        explicit Texture(std::string filePath);
        ~Texture();

        void Bind(unsigned int slot) const;
        void Unbind();

        const glm::ivec2& GetSize() const;
};
