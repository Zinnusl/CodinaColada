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

	//fps display
	int32_t fpsTimer = 0;
	int32_t fps = 0;
	int32_t fpsDisplay = 0;

	//physics
	const int32_t ticksPerSecond = 8;
	const int32_t microSecondsPerTick = 1000000 / ticksPerSecond;
	int32_t timeSinceLastPhysicsTick = 0;

	while (!stopGame)
	{
		auto currentFrame = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentFrame - lastFrame).count();

		fpsTimer += deltaTime;
		timeSinceLastPhysicsTick += deltaTime;
		fps++;

		//Check if 1 second has passed
		if (fpsTimer >= 1000000)
		{
			fpsTimer = 0;
			fpsDisplay = fps;
			fps = 0;
			printf("fps: %d\n", fpsDisplay);
		}

		//Handle input
		input_->ProcessInput();

		//Check for collisions. This should be part of physics simulation. It is also very buggy and O(n^2)
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

		//Since the physics simulation is not tied to the framerate, we need to interpolate between the old and the new positions.
		//The t value for interpolation is the subframe.
		float subframe = timeSinceLastPhysicsTick / (float)microSecondsPerTick;

		//Check if its time to run physics
		if (timeSinceLastPhysicsTick >= microSecondsPerTick)
		{
			//run physics simulation
			for (const auto& gameobject : gameobjects_)
			{
				gameobject.second->OnUpdate(timeSinceLastPhysicsTick / 400.f);
			}
			timeSinceLastPhysicsTick = 0;
		}

		//Draw 
		renderer_->BeginFrame();
		for (const auto& gameobject : gameobjects_)
		{
			gameobject.second->OnDraw(0);
			gameobject.second->OnDraw(subframe);
			gameobject.second->OnDraw(1);
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