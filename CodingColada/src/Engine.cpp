#include "Engine.h"

#include "IRenderer.h"
#include "IInput.h"

#include <chrono>

Engine::Engine(IRenderer& renderer, IInput& input)
	: renderer_(renderer), input_(input)
{
}

void Engine::StartGame()
{
	auto lastFrame = std::chrono::steady_clock::now();

	GetRenderer().CreateWindow(1240, 1024, GetInput());
	
	while (!stopGame)
	{
		auto currentFrame = std::chrono::steady_clock::now();
		auto deltaTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>(currentFrame - lastFrame).count();
		
		//input
		input_.ProcessInput();

		//update (physics...)
		for (const auto& gameobject : gameobjects_)
		{
			//gameobject.second->OnUpdate(*this, deltaTime);
			gameobject.second->OnUpdate(*this, deltaTime);
		}

		//draw
		renderer_.Draw();
		lastFrame = currentFrame;
	}
}

void Engine::StopGame()
{
	stopGame = true;
}

void Engine::AddGameObject(std::unique_ptr<GameObject> gameobject)
{
	static int32_t gameObjectId = 1;
	gameobjects_.insert(std::make_pair<>(gameObjectId++, std::move(gameobject)));
}

IRenderer& Engine::GetRenderer() const
{
	return renderer_;
}

IInput& Engine::GetInput() const
{
	return input_;
}