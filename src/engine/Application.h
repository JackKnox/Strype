#pragma once

#include "ResourceManager.h"
#include "Window.h"

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
	Window mWindow;
	ResourceManager mResources;
};

