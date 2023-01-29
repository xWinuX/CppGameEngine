#pragma once
#include <map>

class AssetDatabase
{
    private:
        template <typename TKey, typename T>
        static std::map<TKey, T> _assetMap;

    public:
        template <typename T, typename TKey>
        static T Get(TKey key)
        {
            auto it = _assetMap<TKey, T>.find(key);
            if (it != _assetMap<TKey, T>.end()) { return it->second; }
            return nullptr;
        }

        template <typename T, typename TKey>
        static T Add(TKey id, T asset)
        {
            _assetMap<TKey, T>[id] = asset;
            return asset;
        }
};

template <typename TKey, typename T>
std::map<TKey, T> AssetDatabase::_assetMap = std::map<TKey, T>();