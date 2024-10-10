#include "Window.h"
#include <string>
#include <SDL/SDL_image.h>
#include <iostream>

Window::Window()
{
	//Init SDL and other stuff...
	if (!init())
	{
		printf("Failed to initialize!\n");
	}

	//Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
	}
}

Window::~Window()
{
	//Free resources and close SDL 
	destroy();
}

bool Window::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		success = false;
	}

	//Initialize SDL_image	
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		std::cout << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
		success = false;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}

	//Create window
	mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mWindow == NULL)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	//Create vsynced renderer for window
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == NULL)
	{
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return success;
}

bool Window::loadMedia()
{
	//Loading success flag
	bool success = true;

	mArrowTexture.BindRenderer(mRenderer);
	success = mArrowTexture.loadFromFile("res/lettuce.png") & true;

	return success;
}

void Window::loop()
{
	//Main loop flag
	bool quit = false;
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(mRenderer);

		//Render arrow
		mArrowTexture.render((SCREEN_WIDTH - mArrowTexture.getWidth()) / 2, (SCREEN_HEIGHT - mArrowTexture.getHeight()) / 2, NULL, 0, NULL, SDL_FLIP_NONE);

		//Update screen
		SDL_RenderPresent(mRenderer);
	}
}

bool Window::destroy()
{
	//Free loaded images
	mArrowTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	return true;
}
