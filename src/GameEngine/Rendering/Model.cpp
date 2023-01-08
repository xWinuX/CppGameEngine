#include "Model.h"
#include <random>
#include <vector>

#include "../Debug/Log.h"
#include "../IO/Importer/GLTF.h"
#include "../IO/Importer/OBJ.h"

using namespace GameEngine::Rendering;

Model::Model(const std::string& filePath)
{
    const std::string extension = filePath.substr(filePath.find_last_of('.') + 1);

    if (extension == "obj") { _meshes = GameEngine::IO::Importer::OBJ::ImportModel(filePath); }
    else if (extension == "gltf") { _meshes = GameEngine::IO::Importer::GLTF::ImportModel(filePath); }
    else { Debug::Log::Error("Model file extension " + extension + " is not supported"); }
}

Model::~Model() { for (const Mesh* mesh : _meshes) { delete mesh; } }

Mesh* Model::GetMesh(const unsigned index) const { return index < _meshes.size() ? _meshes[index] : nullptr; }
