#include "GameEngine/ID.h"

using namespace GameEngine;

size_t ID::_id = 0;

ID::ID():
    _localID(_id++) {}

size_t      ID::GetID() const { return _localID; }
std::string ID::GetImGuiIDString(const std::string& str) const { return str + "##" + std::to_string(_localID); }
