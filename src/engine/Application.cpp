#include "Application.h"

#include "Errors.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

unsigned int Application::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		return ERROR_INIT_SDL;
	}
	
	//Initialize SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		SDL_Quit();
		printf("SDL_image Error: %s\n", IMG_GetError());
		return ERROR_INIT_SDL_IMAGE;
	}

	//Initialize SDL_mixer
	int mixFlags = MIX_INIT_MP3 | MIX_INIT_OGG;
	if (!(Mix_Init(mixFlags) & mixFlags))
	{
		SDL_Quit();
		IMG_Quit();
		printf("SDL_mixer Error: %s\n", Mix_GetError());
		return ERROR_INIT_SDL_MIXER;
	}

	//Initialize SDL_ttf
	if (TTF_Init() < 0)
	{
		SDL_Quit();
		IMG_Quit();
		Mix_Quit();
		printf("SDL_mixer Error: %s\n", Mix_GetError());
		return ERROR_INIT_SDL_TTF;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		SDL_Quit();
		IMG_Quit();
		Mix_Quit();
		TTF_Quit();
		printf("SDL Error: Texture filtering cannot be set to linear");
		return ERROR_SDL_ANTIALISLING;
	}

	//Initialize the windows
	if (unsigned int error = mWindow.init("Test Window"); error > 0)
	{
		SDL_Quit();
		IMG_Quit();
		Mix_Quit();
		TTF_Quit();
		return error;
	}
	
	//Load all resources
	mResources.init(mWindow.getRenderer());
	
	return 0;
}

bool Application::loop(SDL_Event& e)
{
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			return true;
		}

		//Handle window events
		mWindow.handleEvent(e);
	}

	//Update all windows
	mWindow.render();
	SDL_RenderCopy(mWindow.getRenderer(), mResources.getTexture("lettuce.png"), nullptr, nullptr);
	SDL_RenderPresent(mWindow.getRenderer());
	
	//Application closed all windows
	if (!mWindow.isShown())
	{
		return true;
	}

	return false;
}

void Application::close()
{
	//Destroy windows
	mWindow.free();

	//Free all resources
	mResources.shutdown();

	//Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
}

unsigned int Application::run()
{
	//Start up SDL
	if (unsigned int error = init(); error > 0)
	{
		printf("System Error: %i\n", error);
		return error;
	}

	bool quit = false;
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		quit = this->loop(e);
	}

	//Closes window and SDL
	close();

	return 0;
}
