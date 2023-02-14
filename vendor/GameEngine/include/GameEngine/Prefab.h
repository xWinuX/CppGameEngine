#pragma once
#include "GameObject.h"


namespace GameEngine
{
    class Prefab
    {
        private:
            std::string _name;

        protected:
            virtual void PrepareGameObject(GameObject* gameObject);

        public:
            explicit    Prefab(const std::string& name);
            GameObject* Instantiate();
            GameObject* Instantiate(glm::vec3 position);
    };
}
