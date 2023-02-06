#include "GameEngine/Rendering/Model.h"

#include <random>
#include <vector>

#include "GameEngine/IO/Importer/GLTF.h"
#include "GameEngine/IO/Importer/OBJ.h"

using namespace GameEngine::Rendering;
using namespace GameEngine::IO;

Model::Model(const std::string& filePath, const bool createCollider)
{
    const std::string extension = filePath.substr(filePath.find_last_of('.') + 1);

    if (extension == "obj") { _meshes = IO::Importer::OBJ::ImportModel(filePath); }
    else if (extension == "gltf") { _meshes = IO::Importer::GLTF::ImportModel(filePath, createCollider); }
    else { Debug::Log::Error("Model file extension " + extension + " is not supported"); }
}

Model::~Model() { for (const Mesh* mesh : _meshes) { delete mesh; } }

Mesh* Model::GetMesh(const unsigned index) const { return index < _meshes.size() ? _meshes[index] : nullptr; }
