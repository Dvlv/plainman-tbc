#include "headers/texture-cache.h"
#include "raylib.h"
#include <array>
#include <string>

TextureCache::TextureCache() {}

Texture2D TextureCache::getTexture(int index) { return textures.at(index); }

int TextureCache::storeTexture(std::string filepath) {
    if (this->textureCount >= MAX_TEXTURES) {
        printf("TOO MANY TEXTURES!!!!\n\n");
        return -1;
    }

    Texture2D texture = LoadTexture(filepath.c_str());

    this->textures[this->textureCount] = texture;
    return this->textureCount++;
}

TextureCache::~TextureCache() {
    printf("tearing down texture store\n");
    for (int i = 0; i < this->textureCount; i++) {
        UnloadTexture(this->textures.at(i));
    }
    printf("texstore destroyed\n");
}
