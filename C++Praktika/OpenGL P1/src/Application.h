#pragma once

#include "Core/Window.h"

class Application
{
    private:
        static Window _window;
    public:
        Application();
        void    Run() const;
        static Window& GetWindow() { return _window; }
};
