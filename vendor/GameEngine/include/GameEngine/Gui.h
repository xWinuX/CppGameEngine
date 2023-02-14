#pragma once

namespace GameEngine
{
    class Gui
    {
        public:
            static void Initialize();
            static void BeginNewFrame();
            static void Draw();
            static bool IsHidden();
            static void SetHidden(bool hidden);
            static void ToggleHidden();

        private:
            static bool _isHidden;
    };
}
