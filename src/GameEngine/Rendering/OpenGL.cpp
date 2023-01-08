#include "OpenGL.h"

using namespace GameEngine::Rendering;

const std::map<GLenum, OpenGL::TypeEnumLookupEntry> OpenGL::TypeEnumLookup = {
    {GL_BYTE, {sizeof(GLbyte)}},
    {GL_UNSIGNED_BYTE, {sizeof(GLubyte)}},
    {GL_SHORT, {sizeof(GLshort)}},
    {GL_UNSIGNED_SHORT, {sizeof(GLushort)}},
    {GL_INT, {sizeof(GLint)}},
    {GL_UNSIGNED_INT, {sizeof(GLuint)}},
    {GL_FLOAT, {sizeof(GLfloat)}}
};