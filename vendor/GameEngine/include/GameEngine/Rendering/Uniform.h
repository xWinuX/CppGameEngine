#pragma once

#include "../Debug/Log.h"
#include "glad/glad.h"
#include <glm/mat4x4.hpp>

#include "CubeMap.h"
#include "imgui.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "glm/gtc/type_ptr.hpp"

#include "../../../src/Asset.h"

#define LOCATION_CHECK if (_location < 0) { return; }

#define SAMPLER_SPECIFICATION(type) \
template <> \
class Uniform<type> \
{ \
    private: \
        const std::string   _name; \
        const GLint         _location = -1; \
        const type          _defaultValue; \
        const type          _value; \
        int                 _previousSlot = 0; \
\
        std::string GetNameWithID(const std::string& identifier) const { return _name + "##" + identifier; } \
\
    public: \
        Uniform(): \
            _defaultValue(), \
            _value() { } \
\
        Uniform(const std::string uniformName, const GLint location, const type defaultValue): \
            _name(uniformName), \
            _location(location), \
            _defaultValue(defaultValue), \
            _value(defaultValue) { } \
\
        void Apply(int slot = -1) \
        { \
            LOCATION_CHECK \
            if (slot == -1) { slot = _previousSlot; } \
            _value->Bind(slot); \
            glUniform1i(_location, slot); \
            _previousSlot = slot; \
        } \
\
        void Set(const type value) { _value = value; } \
\
        void Reset() { _value = _defaultValue; } \
\
        void Draw(const std::string& identifier) { Debug::Log::Message("This should never appear"); } \
\
        std::string GetName() const { return _name; } \
        type    GetDefaultValue() const { return const_cast<type>(_defaultValue); } \
};

namespace GameEngine
{
    namespace Rendering
    {
        template <typename T>
        class Uniform
        {
            private:
                const std::string _name;
                const GLint       _location = -1;
                const T           _defaultValue;
                T                 _value;

                static size_t _id;

                std::string GetNameWithID(const std::string& identifier) const { return _name + "##" + identifier; }

            public:
                Uniform():
                    _defaultValue(),
                    _value() { }

                Uniform(const std::string uniformName, const GLint location, T defaultValue):
                    _name(uniformName),
                    _location(location),
                    _defaultValue(defaultValue),
                    _value(defaultValue) { }

                void Apply() { Debug::Log::Message("This should never appear"); }

                void Set(T value) { _value = value; }

                void Reset() { _value = _defaultValue; }

                void Draw(const std::string& identifier) { Debug::Log::Message("This should never appear"); }

                std::string GetName() const { return _name; }

                T GetDefaultValue() { return _defaultValue; }

                T* GetValuePtr() { return &_value; }
        };

        template <typename T>
        size_t Uniform<T>::_id = 0;

        template <>
        class Uniform<Texture2D*>
        {
            private:
                const std::string _name;
                const GLint       _location = -1;
                const Texture2D*  _defaultValue;
                const Texture2D*  _value;
                const char*       _selectedTextureName = nullptr;
                int               _previousSlot        = 0;

                std::string GetNameWithID(const std::string& identifier) const { return _name + "##" + identifier; }

            public:
                Uniform():
                    _defaultValue(), _value() { }

                Uniform(const std::string uniformName, const GLint location, const Texture2D* defaultValue):
                    _name(uniformName), _location(location), _defaultValue(defaultValue), _value(defaultValue)
                {
                    if (defaultValue != nullptr) { _selectedTextureName = defaultValue->GetName().c_str(); }
                }

                void Apply(int slot = -1)
                {
                    LOCATION_CHECK
                    if (slot == -1) { slot = _previousSlot; }
                    _value->Bind(slot);
                    glUniform1i(_location, slot);
                    _previousSlot = slot;
                }

                void Set(const Texture2D* value)
                {
                    _value = value;
                    if (_value != nullptr) { _selectedTextureName = _value->GetName().c_str(); }
                }

                void Reset() { Set(_defaultValue); }

                void Draw(const std::string& identifier)
                {
                    LOCATION_CHECK
                    if (_value != nullptr)
                    {
                        ImGui::Image(reinterpret_cast<void*>(_value->GetTextureID()), {50, 50}, {0, 1}, {1, 0});
                        ImGui::SameLine();
                    }
                    const std::map<Asset::Texture2D, Texture2D*> textures = AssetDatabase::GetAll<Asset::Texture2D, Texture2D*>();
                    if (ImGui::BeginCombo(GetNameWithID(identifier).c_str(), _selectedTextureName))
                    {
                        for (const std::pair<const Asset::Texture2D, Texture2D*> value : textures)
                        {
                            ImGui::Image(reinterpret_cast<void*>(value.second->GetTextureID()), {30, 30}, {0, 1}, {1, 0});
                            ImGui::SameLine();

                            const std::string& textureString = value.second->GetName();
                            const bool         isSelected    = _selectedTextureName == textureString.c_str();
                            if (ImGui::Selectable(textureString.c_str(), isSelected)) { Set(value.second); }
                            if (isSelected) { ImGui::SetItemDefaultFocus(); }
                        }
                        ImGui::EndCombo();
                    }
                }

                std::string GetName() const { return _name; }
                Texture2D*  GetDefaultValue() const { return const_cast<Texture2D*>(_defaultValue); }
        };

        SAMPLER_SPECIFICATION(Texture2DArray*)
        SAMPLER_SPECIFICATION(CubeMap*)

        template <>
        inline void Uniform<float>::Apply()
        {
            LOCATION_CHECK
            glUniform1f(_location, _value);
        }

        inline void Uniform<float>::Draw(const std::string& identifier)
        {
            LOCATION_CHECK
            ImGui::InputFloat(GetNameWithID(identifier).c_str(), &_value);
        }


        template <>
        inline void Uniform<std::vector<float>*>::Apply()
        {
            LOCATION_CHECK
            glUniform1fv(_location, static_cast<int>(_value->size()), _value->data());
        }

        template <>
        inline void Uniform<glm::vec4>::Apply()
        {
            LOCATION_CHECK
            glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
        }

        template <>
        inline void Uniform<glm::vec4>::Draw(const std::string& identifier)
        {
            LOCATION_CHECK
            ImGui::ColorPicker4(GetNameWithID(identifier).c_str(), glm::value_ptr(_value));
        }

        template <>
        inline void Uniform<std::vector<glm::vec4>*>::Apply()
        {
            LOCATION_CHECK
            if (_value == nullptr) { return; }

            glUniform4fv(_location, static_cast<int>(_value->size()), reinterpret_cast<GLfloat*>(_value->data()));
        }

        template <>
        inline void Uniform<glm::vec3>::Apply()
        {
            LOCATION_CHECK
            glUniform3f(_location, _value.x, _value.y, _value.z);
        }

        inline void Uniform<glm::vec3>::Draw(const std::string& identifier)
        {
            LOCATION_CHECK
            ImGui::InputFloat3(GetNameWithID(identifier).c_str(), glm::value_ptr(_value));
        }

        template <>
        inline void Uniform<std::vector<glm::vec3>*>::Apply()
        {
            LOCATION_CHECK
            if (_value == nullptr) { return; }

            glUniform3fv(_location, static_cast<int>(_value->size()), reinterpret_cast<GLfloat*>(_value->data()));
        }

        template <>
        inline void Uniform<glm::mat4>::Apply()
        {
            LOCATION_CHECK
            glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
        }

        template <>
        inline void Uniform<int>::Apply()
        {
            LOCATION_CHECK
            glUniform1i(_location, _value);
        }

        inline void Uniform<int>::Draw(const std::string& identifier)
        {
            LOCATION_CHECK
            ImGui::InputInt(GetNameWithID(identifier).c_str(), &_value);
        }
    }
}
