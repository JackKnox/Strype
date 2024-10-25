#include "Application.h"

unsigned int Application::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		return 1;
	}

	//Initialize SDL_image
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		SDL_Quit();
		printf("SDL_image Error: %s\n", IMG_GetError());
		return 2;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		SDL_Quit();
		IMG_Quit();
		printf("SDL Error: Texture filtering cannot be set to linear");
		return 3;
	}

	//Initialize the windows
	for (int i = 0; i < TOTAL_WINDOWS; ++i)
	{
		unsigned int error = mWindows[i].init(DEFAULT_WINDOWS_NAME);
		if (error > 0)
		{
			SDL_Quit();
			IMG_Quit();
			printf("System Error: %i", error);
			return 4;
		}
	}
	
	mResources.init(mWindows[0].getRenderer());
	
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
		for (int i = 0; i < TOTAL_WINDOWS; ++i)
		{
			mWindows[i].handleEvent(e);
		}
	}

	//Update all windows
	for (int i = 0; i < TOTAL_WINDOWS; ++i)
	{
		mWindows[i].render();
		SDL_RenderPresent(mWindows[i].getRenderer());
	}

	//Check all windows
	bool allWindowsClosed = true;
	for (int i = 0; i < TOTAL_WINDOWS; ++i)
	{
		if (mWindows[i].isShown())
		{
			allWindowsClosed = false;
			break;
		}
	}

	//Application closed all windows
	if (allWindowsClosed)
	{
		return true;
	}

	return false;
}

void Application::close()
{
	//Destroy windows
	for (int i = 0; i < TOTAL_WINDOWS; ++i)
	{
		mWindows[i].free();
	}

	mResources.shutdown();

	//Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
}

unsigned int Application::run()
{
	//Start up SDL
	unsigned int error = init();
	if (init() > 0)
	{
		printf("System Error: %i\n", error);
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
