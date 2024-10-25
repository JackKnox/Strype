#pragma once

#include <SDL/SDL.h>
#include <string>
#include <unordered_map>

class ResourceManager
{
public:
	void init(SDL_Renderer* renderer);

	SDL_Texture* getTexture(std::string& path);

	void shutdown();
private:
	SDL_Renderer* mRenderer;

	std::unordered_map<std::string, SDL_Texture*> mTextures{};
};

