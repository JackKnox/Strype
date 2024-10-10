#pragma once

#include <SDL/SDL.h>
#include "Texture.h"

class Window
{
public:
	Window();

	~Window();

	bool init();

	bool loadMedia();

	void loop();

	bool destroy();

	int getWidth();
	int getHeight();

private:
	SDL_Window* mWindow = NULL;
	SDL_Renderer* mRenderer = NULL;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	Texture mArrowTexture;

	int mWidth;
	int mHeight;
};