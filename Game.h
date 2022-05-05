#pragma once

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	480
#define MAX_KEYS		256

class Game
{
public:
	Game();
	~Game();

	bool Init();
	void Release();
	
	bool Input();
	bool Update();
	void Draw();

private:
	SDL_Window *Window;
	SDL_Renderer *Renderer;

	float alpha;	//angle computed as atan2
	int cx, cy;		//center of the screen
	int rx, ry;		//target point regarding radar coordinate system

	struct
	{
		int x, y;
		bool left, right, middle;
	} mouse;
};
