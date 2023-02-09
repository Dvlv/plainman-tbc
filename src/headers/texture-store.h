#pragma once

#include "raylib.h"
#include <array>
#include <string>

#define MAX_TEXTURES 100

class TextureStore {
public:
  TextureStore();

  // vars
  std::array<Texture2D, MAX_TEXTURES> textures;
  int textureCount = 0;
  // funcs
  Texture2D getTexture(int index);
  int storeTexture(std::string filepath);

  ~TextureStore();
};
