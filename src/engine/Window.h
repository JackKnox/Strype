#pragma once

#include <SDL/SDL.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Window
{
public:
	//Intializes internals
	Window();

	//Creates window
	bool init(std::string name);

	//Handles window events
	void handleEvent(SDL_Event& e);

	//Focuses on window
	void focus();

	//Shows windows contents
	void render();

	//Runs window step
	void loop();

	//Deallocates internals
	void free();

	//Window dimensions
	int getWidth();
	int getHeight();

	//Window focii
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();

private:
	//Window data
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	int mWindowID;

	//Window dimensions
	int mWidth;
	int mHeight;

	//Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
	bool mShown;
};