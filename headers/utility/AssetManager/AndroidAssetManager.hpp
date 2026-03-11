/*
** EPITECH PROJECT, 2026
** utility
** File description:
** AndroidAssetManager
*/

#pragma once

#ifdef __ANDROID__

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "utility/AssetManager/AAssetManager.hpp"

namespace utility
{
    class AndroidAssetManager : public AAssetManager
    {
    public:
        explicit AndroidAssetManager(AAssetManager *assetManager);
        ~AndroidAssetManager() override = default;

        bool loadDirectory(const std::string &directory) override;

        std::shared_ptr<utility::FileAsset> add(const std::string &path) override;

        void remove(const std::string &path, bool save = true) override;

        bool save(const std::string &path, const std::string &newPath = "") override;

    private:
        AAssetManager *_assetManager;
    };
} // namespace utility

#endif // __ANDROID__