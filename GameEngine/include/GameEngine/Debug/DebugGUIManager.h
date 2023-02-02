#pragma once

class DebugGUIManager
{
    private:
        static bool _isHidden;
    public:
        static void Initialize();
        static void BeginNewFrame();
        static void Draw();
        static bool IsHidden();
        static void SetHidden(bool hidden);
        static void ToggleHidden();
};
