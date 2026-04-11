/*
** ETIB PROJECT, 2026
** utility
** File description:
** font
*/

#include <utility/graphic/text/font.hpp>

namespace utility::graphic {

Font::Font(const std::vector<FileAsset> &fontAssets) {
  // Initialize FreeType library
  if (FT_Init_FreeType(&_ftLibrary)) {
    throw std::runtime_error("Could not initialize FreeType library.");
  }

  for (const auto &fontAsset : fontAssets) {
    FT_Face face;
    if (FT_New_Memory_Face(
            _ftLibrary,
            reinterpret_cast<const FT_Byte *>(fontAsset.content().c_str()),
            fontAsset.content().size(), 0, &face)) {
      throw std::runtime_error("Could not load font " + fontAsset.path() +
                               ": " +
                               FT_Error_String(FT_Err_Cannot_Open_Resource));
    }
    _faces[fontAsset.path()] = face;
  }
}

Font::~Font() {
  if (!isLoaded()) {
    return;
  }
  for (const auto &[_, face] : _faces) {
    FT_Done_Face(face);
  }
  if (_ftLibrary) {
    FT_Done_FreeType(_ftLibrary);
  }
}

////////////////////
// Public Methods //
////////////////////

std::vector<Glyph> Font::processCodePoints(uint32_t fontSize,
                                           const codePointString &codePoints) {
  std::vector<Glyph> glyphs;

  for (const auto &codePoint : codePoints) {
    std::string faceName = _getFaceNameForGlyph(codePoint);

    if (faceName.empty()) {
      continue;
    }

    auto fontSizedIt = _sizes.find(fontSize);
    std::shared_ptr<FontSized> fontSized;

    if (fontSizedIt == _sizes.end()) {
      fontSized = std::make_shared<FontSized>(fontSize, _faces.at(faceName));
      _sizes[fontSize] = {faceName, fontSized};
      if (onNewTextureCreated) {
        onNewTextureCreated(faceName + "_" + std::to_string(fontSize),
                            fontSized->getAtlas());
      } else {
        throw std::runtime_error(
            "Font size already processed but not found in sizes map: " +
            std::to_string(fontSize));
      }
    } else {
      fontSized = fontSizedIt->second.second;
    }
    glyphs.push_back(fontSized->generateGlyph(codePoint));
  }
  return glyphs;
}

std::vector<std::string> Font::getFontPaths(void) const {
  std::vector<std::string> fontPaths;
  for (const auto &[fontPath, _] : _faces) {
    fontPaths.push_back(fontPath);
  }
  return fontPaths;
}

bool Font::isLoaded(void) const {
  if (_faces.empty())
    return false;
  for (const auto &[_, face] : _faces) {
    if (!face || face->num_glyphs == 0) {
      return false;
    }
  }
  return true;
}

bool Font::hasGlyph(char32_t codepoint) const {
  if (!isLoaded()) {
    return false;
  }
  for (const auto &[_, face] : _faces) {
    if (FT_Get_Char_Index(face, codepoint) != 0) {
      return true;
    }
  }
  return false;
}

///////////////////////
// Protected Methods //
///////////////////////

std::string Font::_getFaceNameForGlyph(uint32_t codePoint) const {
  if (_faces.empty()) {
    return "";
  }

  for (const auto &[faceName, face] : _faces) {
    FT_UInt glyphIndex = FT_Get_Char_Index(face, codePoint);
    if (glyphIndex != 0) {
      return faceName;
    }
  }
  return "";
}

} // namespace utility::graphic