#include "Engine.h"

#include "IRenderer.h"
#include "IInput.h"
#include "RigidbodyComponent.h"

#include "imgui.h"

#include <chrono>
#include <iostream>
#include <string> 



Engine::Engine(std::unique_ptr<IRenderer> renderer, std::unique_ptr<IInput> input)
	: renderer_(std::move(renderer)), input_(std::move(input))
{
	GameObject::engine_ = this;
}

void Engine::StartGame()
{
	auto currentFrame = std::chrono::steady_clock::now();
	auto lastFrame = std::chrono::steady_clock::now();

	float subframe = 0;
	//physics
	const int32_t ticksPerSecond = 64;
	const int32_t microSecondsPerTick = 1000000 / ticksPerSecond;
	int32_t timeSinceLastPhysicsTick = 0;

	bool pauseGame = false;

	while (!stopGame)
	{
		//Handle input
		//needs to be outside to allow to pause game
		input_->ProcessInput();
		currentFrame = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentFrame - lastFrame).count();

		if (!pauseGame)
		{
			timeSinceLastPhysicsTick += deltaTime;

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
			subframe = timeSinceLastPhysicsTick / (float)microSecondsPerTick;

			//printf("Subframe %f\n", subframe);
			//Check if its time to run physics
			if (timeSinceLastPhysicsTick >= microSecondsPerTick)
			{
				//run physics simulation
				for (const auto& gameobject : gameobjects_)
				{
					gameobject.second->OnUpdate(timeSinceLastPhysicsTick);
					//gameobject.second->OnUpdate(microSecondsPerTick);
				}
				timeSinceLastPhysicsTick = 0;
			}

			//TODO ghetto fix. Or is it?
			if (subframe > 1)
			{
				subframe = subframe - 1.f;
			}
		}
		//printf("subframe %f\n", subframe);
		//Draw 
		renderer_->BeginFrame();
		for (const auto& gameobject : gameobjects_)
		{
			//gameobject.second->OnDraw(0);
			gameobject.second->OnDraw(subframe);
			//gameobject.second->OnDraw(1);
		}
		{
			ImGui::Begin("CodinaColada - Engine - Debug");                          // Create a window called "Hello, world!" and append into it.
			ImGui::Checkbox("Pause", &pauseGame);
			if (ImGui::TreeNode("GameObjects"))
			{
				for (auto& it : gameobjects_)
				{
					GameObject* gameobject = it.second.get();
					if (ImGui::TreeNode(std::to_string(it.first).c_str()))
					{
						ImGui::Text("x: %f, y: %f", gameobject->GetPosition().GetX(), gameobject->GetPosition().GetY());
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
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