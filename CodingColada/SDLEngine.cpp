#include "SDLEngine.h"

#include "SDL2/SDL.h"

SDLEngine::SDLEngine()
	: window_(nullptr), renderer_(nullptr)
{
	SDL_Init(SDL_INIT_VIDEO);
}

SDLEngine::~SDLEngine()
{
	if (window_)
	{
		SDL_DestroyWindow(window_);
		window_ = nullptr;
		renderer_ = nullptr; // TODO: SDL_DestroyRenderer oder so?
	}
		
	SDL_Quit();
}

void SDLEngine::CreateWindow(const int size_x, const int size_y)
{
	window_ = SDL_CreateWindow(
		"ColadaLoca",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		size_x,
		size_y,
		0
	);

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer_);
	SDL_RenderPresent(renderer_);

	SDL_Delay(2000);
}
