#pragma once

#include "raylib.h"
#include <array>
#include <string>

class TextureCache {
  public:
    TextureCache();

    // funcs
    Texture2D getTexture(int index);
    int storeTexture(std::string filepath);

    ~TextureCache();

  private:
    static int const MAX_TEXTURES{100};
    std::array<Texture2D, MAX_TEXTURES> textures{};
    int textureCount{0};
};
