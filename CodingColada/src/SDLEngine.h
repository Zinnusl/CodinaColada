//#pragma once
//
//#include "IEngine.h"
//
//struct SDL_Window;
//struct SDL_Renderer;
//
//class SDLEngine : public IEngine
//{
//protected:
//	SDL_Window* window_;
//	SDL_Renderer* renderer_;
//
//public:
//	explicit SDLEngine();
//	~SDLEngine();
//
//	void CreateWindow(const int size_x, const int size_y);
//	IRenderer GetRenderer() const;
//};