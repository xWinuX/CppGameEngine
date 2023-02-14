#pragma once
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Primitive.h"
#include "glm/vec3.hpp"
#include "glm/gtc/constants.hpp"
#include "reactphysics3d/collision/TriangleMesh.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Mesh
        {
            public:
                explicit Mesh(const std::string& name, const glm::vec3 translation = glm::zero<glm::vec3>());
                Mesh(
                    const std::string&  name,
                    VertexBuffer*       vertexBuffer,
                    IndexBuffer*        indexBuffer,
                    VertexBufferLayout* vertexBufferLayout,
                    glm::vec3           translation = glm::zero<glm::vec3>()
                );
                ~Mesh();

                const std::vector<Primitive*>& GetPrimitives();
                reactphysics3d::TriangleMesh*  GetColliderMesh() const;

                const std::string& GetName();
                glm::vec3          GetTranslation() const;

                void AddPrimitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout);
                void SetColliderMesh(reactphysics3d::TriangleMesh* triangleMesh);

            private:
                std::string                   _name;
                glm::vec3                     _translation;
                std::vector<Primitive*>       _primitives;
                reactphysics3d::TriangleMesh* _colliderMesh{};
        };
    }
}
