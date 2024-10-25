#pragma once

#include "Window.h"
#include "ResourceManager.h"

#include <SDL/SDL_image.h>

const int TOTAL_WINDOWS = 3;
const std::string DEFAULT_WINDOWS_NAME = "Test Window";

class Application 
{
public:
	//Initialize SDL2 and other system-wide libraries
	unsigned int init();

	//One loop of the app (Donst contain while true loop)
	bool loop(SDL_Event& e);

	//Closes all windows and system-wide libraries
	void close();

	//Start app (Contains while true loop)
	unsigned int run();

private:
	Window mWindows[TOTAL_WINDOWS];
	ResourceManager mResources;
};

