﻿#pragma once

class Behaviour
{
    public:
        virtual      ~Behaviour() = 0;
        virtual void Update() = 0;
        virtual void LateUpdate() = 0;
        virtual void Draw() = 0;
};