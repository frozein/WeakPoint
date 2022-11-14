#include <iostream>
#include "SDL.h"
#include "simulation.hpp"

int main(int argc, char **argv)
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	//init main subsystems, window, and renderer:
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0)
	{
		window = SDL_CreateWindow("ScarletGameJam", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);

		if (window)
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer)
			{
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
				SDL_RenderSetLogicalSize(renderer, 3840, 2160);
			}
			else
			{
				std::cout << "SDL ERROR, UNABLE TO INITIALIZE RENDERER - " << SDL_GetError() << std::endl;
				SDL_DestroyWindow(window);
				return -1;
			}
		}
		else
		{
			std::cout << "SDL ERROR, UNABLE TO CREATE WINDOW - " << SDL_GetError() << std::endl;
			return -1;
		}
	}
	else
	{
		std::cout << "SDL ERROR, UNABLE TO INTIALIZE SUBSYSTEMS - " << SDL_GetError() << std::endl;
		return -1;
	}

	float camX = 0.0f, camY = 0.0f;
	sim::World testWorld = sim::World(renderer, "test.png"); //TODO: fix

	bool running = true;
	while(running)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
			{
				running = false;
				break;
			}
			}
		}

		SDL_RenderClear(renderer);

		testWorld.render(renderer, 0, 0, 25);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}