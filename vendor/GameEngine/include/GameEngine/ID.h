#pragma once
#include <string>


namespace GameEngine
{
    class ID
    {
        private:
            static size_t _id;
            size_t        _localID;

        protected:
            size_t      GetID() const;
            std::string GetImGuiIDString(const std::string& str) const;

        public:
            ID();
    };
}
