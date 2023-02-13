#include "GameEngine/Rendering/Primitive.h"

#include "GameEngine/Rendering/VertexArrayObject.h"

using namespace GameEngine::Rendering;

Primitive::Primitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout):
    _vertexBuffer(vertexBuffer),
    _indexBuffer(indexBuffer),
    _vertexBufferLayout(vertexBufferLayout),
    _vertexArrayObject(new VertexArrayObject(vertexBuffer, indexBuffer, vertexBufferLayout)) { }

Primitive::~Primitive()
{
    delete _vertexBuffer;
    delete _indexBuffer;
    delete _vertexBufferLayout;
    delete _vertexArrayObject;
}

VertexArrayObject*  Primitive::GetVertexArrayObject() const { return _vertexArrayObject; }
VertexBuffer*       Primitive::GetVertexBuffer() const { return _vertexBuffer; }
IndexBuffer*        Primitive::GetIndexBuffer() const { return _indexBuffer; }
VertexBufferLayout* Primitive::GetVertexBufferLayout() const { return _vertexBufferLayout; }
