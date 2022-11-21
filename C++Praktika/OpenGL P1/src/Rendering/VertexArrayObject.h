#pragma once
#include <map>
#include <vector>

#include "Mesh.h"
#include "VertexAttribute.h"

class VertexArrayObject
{
    private:
        const VertexAttribute* _pVertexAttributes;
        unsigned int           _numVertexAttributes;
        GLuint                 _vertexArrayID = 0;

        std::map<const Material*, std::vector<const Mesh*>> _meshMap;
        std::map<const Material*, int>                      _indicesBatchMap;

        GLuint _vertexBufferID;
        GLuint _indexBufferID;
    
        int _numPositions = 0;
        int _numIndices   = 0;

        void Bind() const;
    public:
        explicit VertexArrayObject(const VertexAttribute* pVertexAttributes, unsigned int numVertexAttributes);
        void     PrepareMeshes();
        void     Draw() const;
        void     AddMesh(const Mesh* mesh);
        void     RemoveMesh(const Mesh* mesh);
        void     ClearMeshes();
};
