#pragma once

#include "raylib.h"
#include <array>
#include <string>

class TextureStore {
public:
  TextureStore();

  // vars
  std::array<Texture2D, 30> textures;
  int textureCount = 0;
  // funcs
  Texture2D getTexture(int index);
  int storeTexture(std::string filepath);

  ~TextureStore();
};
