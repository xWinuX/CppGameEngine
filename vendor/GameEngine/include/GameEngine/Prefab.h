#pragma once
#include "GameObject.h"


namespace GameEngine
{
    class Prefab
    {
        public:
            explicit    Prefab(const std::string& name);
            GameObject* Instantiate();
            GameObject* Instantiate(glm::vec3 position);

        protected:
            virtual void PrepareGameObject(GameObject* gameObject);

        private:
            std::string _name;
    };
}
