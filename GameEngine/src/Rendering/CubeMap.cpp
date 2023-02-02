#include "GameEngine/Rendering/CubeMap.h"

#include "stb_image.h"
#include "GameEngine/Debug/DebugGUIManager.h"
#include "GameEngine/Debug/Log.h"

using namespace GameEngine::Rendering;

const std::vector<std::string> CubeMap::SuffixOrder = {
    "_R",
    "_L",
    "_U",
    "_D",
    "_F",
    "_B",
};

/**
 * \brief Constructor
 * \param filePathWithoutExtension Path to cube map texture without suffix and file extension
 * Use the following naming scheme:
 * right = _R
 * left = _L
 * up = _U
 * down = _D
 * front = _F
 * back = _B
 * \param extension File extension
 */
CubeMap::CubeMap(const std::string& filePathWithoutExtension, const std::string& extension)
{
    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    Debug::Log::Message("before image load");
    for (unsigned int i = 0; i < SuffixOrder.size(); i++)
    {
        int width, height, numChannels;
        std::string filePath = filePathWithoutExtension + SuffixOrder[i] + extension;
        Debug::Log::Message(filePath);
        stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &numChannels, 3);
        Debug::Log::Message(std::to_string(width));
        Debug::Log::Message(std::to_string(height));
        Debug::Log::Message(std::to_string(numChannels));
        stbi_set_flip_vertically_on_load(false);
        Debug::Log::Message("stbi load done");
        if (!data)
        {
                Debug::Log::Message("failed to load");
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        Debug::Log::Message("gl tex done");
        stbi_image_free(data);
    }
    Debug::Log::Message("After image load");
}

CubeMap::~CubeMap()
{
    glDeleteTextures(1, &_textureID);
}

void CubeMap::Bind(const unsigned slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
}

void CubeMap::Unbind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint CubeMap::GetTextureID() const { return _textureID; }
