#pragma once
#include <map>
#include <vector>


class Material;
class Renderable;

class Renderer
{
    private:
        static std::map<Material*, std::vector<const Renderable*>> _renderables;
    public:
        static void Submit(Renderable* renderable);
        static void Draw();
};
