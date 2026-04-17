#pragma once

#include <utility/asset_manager/file_asset.hpp>
#include <utility/asset_manager/asset_manager.hpp>

#include <utility/graphic/text/font.hpp>
#include <utility/graphic/text/text_material.hpp>
#include <utility/graphic/material.hpp>

namespace utility {
/**
 * @brief The RessourceManager class is responsible for managing and loading various resources such as fonts, materials,
 * and textures in a graphics application.
 *
 * The RessourceManager provides methods to load resources from file paths or from asset objects,
 * and it maintains internal maps to store loaded resources for efficient retrieval.
 * It supports loading fonts, materials, and textures, and it can handle different shader types for materials.
 */
class RessourceManager {
public:
    /**
     * @brief Enumeration for different shader types that can be associated with materials.
     *
     * This enum defines the types of shaders that can be used when loading materials.
     * It currently includes `TEXT_SHADER` for text rendering and `MESH_SHADER` for mesh rendering,
     * allowing for different visual effects based on the shader type used in the material.
     */
    enum class ShaderType {
        TEXT_SHADER,
        MESH_SHADER
    };

    /**
     * @brief Constructs a RessourceManager object.
     */
    RessourceManager() = default;

    /**
     * @brief Destructs the RessourceManager object.
     */
    ~RessourceManager() = default;

    /**
     * @brief Loads a font resource from a specified file path.
     *
     * @param path The file path to the font resource to be loaded.
     * @param assetManager A reference to the AssetManager instance used to load the font asset.
     *
     * @return A shared pointer to the loaded Font object.
     */
    std::shared_ptr<graphic::Font> loadFont(const std::string &path, AssetManager &assetManager);

    /**
     * @brief Loads a font resource from a specified asset.
     *
     * @param fontAsset A shared pointer to the FileAsset object containing the font data to be loaded.
     *
     * @return A shared pointer to the loaded Font object.
     */
    std::shared_ptr<graphic::Font> loadFontFromAsset(std::shared_ptr<utility::FileAsset> fontAsset);

    // TODO: add loadFontsFromDirectory method to load all fonts from a directory
    // But needs to be implemented in the AssetManager first to load all assets from a directory

    // TODO: add loadFontFamily method to load all fonts from a directory
    // But needs to be implemented in the AssetManager first to load all assets from a directory

    /**
     * @brief Loads a font family resource from a vector of font assets.
     *
     * @param fontAssets A vector of shared pointers to FileAsset objects containing the font data for the font family to be loaded.
     *
     * @return A shared pointer to the loaded Font object representing the font family.
     */
    std::shared_ptr<graphic::Font> loadFontFamilyFromAssets(const std::vector<std::shared_ptr<utility::FileAsset>> &fontAssets);

    /**
     * @brief Loads a material resource from a specified file path.
     *
     * @param path The file path to the material resource to be loaded.
     * @param shaderType The type of shader to be associated with the loaded material.
     * @param assetManager A reference to the AssetManager instance used to load the material asset.
     *
     * @return A shared pointer to the loaded Material object.
     */
    std::shared_ptr<graphic::Material> loadMaterial(const std::string &path, ShaderType shaderType, AssetManager &assetManager);

    /**
     * @brief Loads a material resource from a specified asset.
     *
     * @param shaderType The type of shader to be associated with the loaded material.
     * @param materialAsset A shared pointer to the FileAsset object containing the material data to be loaded.
     *
     * @return A shared pointer to the loaded Material object.
     */
    std::shared_ptr<graphic::Material> loadMaterialFromAsset(ShaderType shaderType, std::shared_ptr<utility::FileAsset> materialAsset);

    /**
     * @brief Loads a texture resource from a specified file path.
     *
     * @param path The file path to the texture resource to be loaded.
     * @param assetManager A reference to the AssetManager instance used to load the texture asset
     *
     * @return A shared pointer to the loaded Texture object.
     */
    std::shared_ptr<graphic::Texture> loadTexture(const std::string &path, AssetManager &assetManager);

    /**
     * @brief Loads a texture resource from a specified asset.
     *
     * @param textureAsset A shared pointer to the FileAsset object containing the texture data to be loaded.
     *
     * @return A shared pointer to the loaded Texture object.
     */
    std::shared_ptr<graphic::Texture> loadTextureFromAsset(std::shared_ptr<utility::FileAsset> textureAsset);

    // TODO: add loadTexturesFromDirectory method to load all textures from a directory
    // But needs to be implemented in the AssetManager first to load all assets from a directory

protected:
    /**
     * @brief Internal maps to store loaded fonts for efficient retrieval.
     */
    std::map<std::string, std::shared_ptr<graphic::Font>> _fonts;

    /**
     * @brief Internal map to store loaded materials for efficient retrieval.
     */
    std::map<std::string, std::shared_ptr<graphic::Material>> _materials;

    /**
     * @brief Internal map to store loaded textures for efficient retrieval.
     */
    std::map<std::string, std::shared_ptr<graphic::Texture>> _textures;
};
}
