#include "Game.h"
#include <math.h>
#include <stdio.h>

Game::Game() {}
Game::~Game(){}

bool Game::Init()
{
	//Initialize SDL with all subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//Create our window: title, x, y, w, h, flags
	Window = SDL_CreateWindow("Input SDL: up-down +/- speed, left-right x0.1/x10 speed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}
	//Create a 2D rendering context for a window: window, device index, flags
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return false;
	}

	//Init variables
	cx = WINDOW_WIDTH >> 1,
	cy = WINDOW_HEIGHT >> 1;
	alpha = 0.0f;

	return true;
}
void Game::Release()
{
	//Clean up all SDL initialized subsystems
	SDL_Quit();
}
bool Game::Input()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	return false;
	}
	
	int state = SDL_GetMouseState(&mouse.x, &mouse.y);
	rx = mouse.x - cx;
	ry = -(mouse.y - cy);
	mouse.left = state & SDL_BUTTON(SDL_BUTTON_LEFT);
	mouse.middle = state & SDL_BUTTON(SDL_BUTTON_MIDDLE);
	mouse.right = state & SDL_BUTTON(SDL_BUTTON_RIGHT);

	return true;
}
bool Game::Update()
{
	//Read Input
	if (!Input())	return true;

	//Process Input
	alpha = atan2(ry, rx);

	return false;
}
void Game::Draw()
{
	char title[128];
	float degrees = alpha / (M_PI / 180.0);
	if (degrees < 0)	degrees += 360.0f;

	sprintf_s(title, "Mouse(x,y)=(%d,%d), Radar(x,y)=(%d,%d), alpha=%.2f, LMR=%d%d%d", mouse.x, mouse.y, rx, ry, degrees, mouse.left, mouse.middle, mouse.right);
	SDL_SetWindowTitle(Window, title);

	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	//Clear rendering target
	SDL_RenderClear(Renderer);

	//Draw radar
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(Renderer, cx, cy, cx + cy * cos(alpha), cy - cy * sin(alpha));

	//Update screen
	SDL_RenderPresent(Renderer);

	SDL_Delay(10);	// 1000/10 = 100 fps max
}