#pragma once
#include <string>
#include <vector>

#include "Mesh.h"
#include "../Core/GameObject.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Model
        {
            private:
                std::vector<Mesh*> _meshes;

            public:
                explicit Model(const std::string& filePath);
                ~Model();

                Mesh* GetMesh(unsigned int index) const;
        };
    }
}
