#include "Engine.h"

#include "IRenderer.h"
#include "IInput.h"

Engine::Engine(std::unique_ptr<IRenderer> renderer, std::unique_ptr<IInput> input)
	: renderer_(std::move(renderer)), input_(std::move(input))
{

}

void Engine::StartGame()
{
	//TODO termination condition
	while (1)
	{
		//input
		//Input (pollt events?) und ruft die handler auf.
		//phsyics

		//draw
		renderer_->Draw();
	}
}

IRenderer& Engine::GetRenderer() const
{
	return *renderer_;
}

IInput& Engine::GetInput() const
{
	return *input_;
}
