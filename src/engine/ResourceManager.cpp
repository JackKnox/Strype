#include "ResourceManager.h"

#include <SDL/SDL_image.h>
#include <filesystem>

void ResourceManager::init(SDL_Renderer* renderer)
{
    mRenderer = renderer;

    const std::filesystem::path path = std::filesystem::path("res");
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            SDL_Texture* texture = getTexture(filePath);

        }
    }
}

SDL_Texture* ResourceManager::getTexture(std::string& path)
{
    if (mTextures.find(path) != mTextures.end()) {
        return mTextures[path];
    }

    SDL_Texture* tex = IMG_LoadTexture(mRenderer, path.c_str());
    if (tex == NULL)
    {
        printf("SDL_image Error: %s\n", IMG_GetError());
    }

    mTextures[path] = tex;
    return tex;
}

void ResourceManager::shutdown()
{

}
