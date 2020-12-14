#include "App.h"

#include "SDL2/SDL.h"

App::App(std::ostream& logger)
	: logger_(logger)
{	
}

void App::run()
{
	logger_ << "Ich bin eine App?\n"; // <-- mich auskommentieren um den test zu testen(falls man sowas tut?)

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"ColadaLoca",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		0
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Delay(2000);

	SDL_DestroyWindow(window);
	SDL_Quit();
}