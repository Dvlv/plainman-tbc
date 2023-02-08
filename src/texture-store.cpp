#include "headers/texture-store.h"
#include "raylib.h"
#include <array>
#include <string>

#define MAX_TEXTURES 40

TextureStore::TextureStore() { this->textureCount = 0; }

Texture2D TextureStore::getTexture(int index) { return textures.at(index); }

int TextureStore::storeTexture(std::string filepath) {
  if (this->textureCount >= MAX_TEXTURES) {
    printf("TOO MANY TEXTURES!!!!\n\n");
    return -1;
  }

  Texture2D texture = LoadTexture(filepath.c_str());

  this->textures[this->textureCount] = texture;
  this->textureCount++;

  return this->textureCount - 1;
}

TextureStore::~TextureStore() {
  printf("tearing down texture store\n");
  for (int i = 0; i < this->textureCount; i++) {
    UnloadTexture(this->textures.at(i));
  }
  printf("texstore destroyed\n");
}
