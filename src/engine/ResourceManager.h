#pragma once

#include <unordered_map>
#include <SDL/SDL.h>

#include "Application.h"

class ResourceManager
{
public:
	ResourceManager(Application* app);

private:
	Application* currentApp;

	std::unordered_map<std::string, SDL_Texture*> mTextures{};
};

