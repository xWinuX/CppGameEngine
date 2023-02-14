﻿#pragma once
#include <map>

namespace GameEngine
{
    class AssetDatabase
    {
        public:
            template <typename T, typename TKey>
            static T Get(TKey key)
            {
                auto it = _assetMap<TKey, T>.find(key);
                if (it != _assetMap<TKey, T>.end()) { return it->second; }
                return nullptr;
            }

            template <typename TKey, typename T>
            static std::map<TKey, T>& GetAll() { return _assetMap<TKey, T>; }

            template <typename T, typename TKey>
            static T Add(TKey id, T asset)
            {
                _assetMap<TKey, T>[id] = asset;
                return asset;
            }

        private:
            template <typename TKey, typename T>
            static std::map<TKey, T> _assetMap;
    };

    template <typename TKey, typename T>
    std::map<TKey, T> AssetDatabase::_assetMap = std::map<TKey, T>();
}
