﻿#pragma once
#include "Renderable.h"

class Renderer
{
    private:
        //static std::map<Material*, std::vector<Renderable*>> _renderables;
    public:
        static void Submit(Renderable* renderable);
        static void Draw();
};
