#pragma once
#include "GameObject.h"


namespace GameEngine
{
    class Prefab
    {
        protected:
            virtual void PrepareGameObject(GameObject* gameObject);
        public:
            GameObject* Instantiate();
    };
}
