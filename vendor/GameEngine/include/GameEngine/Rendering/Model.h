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
            public:
                explicit Model(const std::string& filePath, bool createCollider = false);
                ~Model();

                Mesh* GetMesh(unsigned int index) const;

            private:
                std::vector<Mesh*> _meshes;
        };
    }
}
