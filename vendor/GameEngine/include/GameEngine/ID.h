#pragma once
#include <string>


namespace GameEngine
{
    class ID
    {
        public:
            ID();

        protected:
            size_t      GetID() const;
            std::string GetImGuiIDString(const std::string& str) const;

        private:
            static size_t _id;
            size_t        _localID;
    };
}
