#include "Engine.h"

#include "IRenderer.h"
#include "IInput.h"
#include "RigidbodyComponent.h"

#include <chrono>
#include <iostream>

Engine::Engine(std::unique_ptr<IRenderer> renderer, std::unique_ptr<IInput> input)
	: renderer_(std::move(renderer)), input_(std::move(input))
{
	GameObject::engine_ = this;
}

void Engine::StartGame()
{
	auto lastFrame = std::chrono::steady_clock::now();
	long long time = 0;
	int32_t fps = 0;
	int32_t fpsDisplay = 0;

	while (!stopGame)
	{
		auto currentFrame = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentFrame - lastFrame).count();
		time += deltaTime;
		fps++;

		if (time >= 1000000)
		{
			time = 0;
			fpsDisplay = fps;
			fps = 0;
			printf("fps: %d\n", fpsDisplay);
		}

		//input
		input_->ProcessInput();

		for (const auto& gameobject : gameobjects_)
		{
			RigidbodyComponent* rb = gameobject.second->GetFirstComponentOfType<RigidbodyComponent>();
			if (!rb)
			{
				continue;
			}
			for (const auto& gameobject : gameobjects_)
			{
				auto otherRb = gameobject.second->GetFirstComponentOfType<RigidbodyComponent>();
				if (!otherRb)
				{
					continue;
				}
				if (rb != otherRb)
				{
					bool isCollided = rb->CheckCollision(*otherRb);
					if (isCollided)
					{
						otherRb->GetGameobject().OnCollision(*rb);
					}
				}
			}
		}

		//update (physics...)
		for (const auto& gameobject : gameobjects_)
		{
			gameobject.second->OnUpdate(deltaTime);
		}

		renderer_->BeginFrame();
		for (const auto& gameobject : gameobjects_)
		{
			gameobject.second->OnDraw();
		}
		renderer_->EndFrame();

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