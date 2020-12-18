#include "Engine.h"

#include "IRenderer.h"
#include "IInput.h"

#include <chrono>

Engine::Engine(std::unique_ptr<IRenderer> renderer, std::unique_ptr<IInput> input)
	: renderer_(std::move(renderer)), input_(std::move(input))
{

}

void Engine::StartGame()
{
	auto lastFrame = std::chrono::steady_clock::now();
	//TODO termination condition
	while (!stopGame)
	{
		auto currentFrame = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrame - lastFrame).count();
		
		//input
		input_->ProcessInput();

		//update (physics...)
		for (const auto& gameobject : gameobjects_)
		{
			gameobject.second->OnUpdate(deltaTime);
		}

		//draw
		renderer_->Draw();
		lastFrame = currentFrame;
	}
}

void Engine::StopGame()
{
	stopGame = true;
}

void Engine::AddGameObject(std::unique_ptr<GameObject> gameobject)
{
	//TODO how are ids generated?
	static int32_t gameObjectId = 1;
	gameobjects_.insert(std::make_pair<>(gameObjectId++, std::move(gameobject)));
}

IRenderer& Engine::GetRenderer() const
{
	return *renderer_;
}

IInput& Engine::GetInput() const
{
	return *input_;
}