#pragma once
#include <string>
#include <vector>

#include "Mesh.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Model
        {
            private:
                std::vector<Mesh*> _meshes;

            public:
                explicit Model(const std::string& filePath, bool createCollider = false);
                ~Model();

                Mesh* GetMesh(unsigned int index) const;
        };
    }
}
