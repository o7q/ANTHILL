#pragma once

#include <memory>
#include <unordered_map>

template <typename KeyType, typename Type> class AssetStore
{
  public:
    AssetStore() = default;
    AssetStore(const AssetStore &other) = delete;
    AssetStore &operator=(const AssetStore &other) = delete;
    ~AssetStore() = default;

    void add(KeyType key, std::unique_ptr<Type> asset)
    {
        m_assets[key] = std::move(asset);
    }
    void remove(KeyType key) { m_assets.erase(key); }
    const Type *get(KeyType key) const
    {
        auto it = m_assets.find(key);
        return it != m_assets.end() ? it->second.get() : &m_fallback;
    }

  private:
    std::unordered_map<KeyType, std::unique_ptr<Type>> m_assets;
    Type m_fallback;
};
