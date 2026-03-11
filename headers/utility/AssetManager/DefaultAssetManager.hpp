/*
** EPITECH PROJECT, 2026
** utility
** File description:
** DefaultAssetManager
*/

#pragma once

#include "utility/AssetManager/AAssetManager.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace utility
{
    class DefaultAssetManager : public AAssetManager {
        public:

            DefaultAssetManager() = default;

            bool loadDirectory(const std::string &directory) override;

            std::shared_ptr<utility::FileAsset> add(const std::string &path) override;

            void remove(const std::string &path, bool save = true) override;

            bool save(const std::string &path, const std::string &newPath = "") override;

    };
} // namespace utility