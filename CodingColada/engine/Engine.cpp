#include "Engine.h"

#include "IRenderer.h"
#include "IInput.h"
#include "RigidbodyComponent.h"

#include "imgui.h"

#include <chrono>
#include <iostream>
#include <string> 


Engine::Engine(std::shared_ptr<IRenderer> renderer, std::unique_ptr<IInput> input, std::unique_ptr<IAudio> audio)
	: renderer_(std::move(renderer)), input_(std::move(input)), audio_(std::move(audio))
{
	GameObject::engine_ = this;
}

void Engine::StartGame()
{
	for (auto& go : gameobjects_)
	{
		go.second->OnStart();
	}

	auto currentFrame = std::chrono::steady_clock::now();
	auto lastFrame = std::chrono::steady_clock::now();

	//subframes are interpolated between physic ticks
	float subframe = 0;

	//physics
	int32_t ticksPerSecond = 64;
	int32_t microSecondsPerTick = 0;
	int32_t timeSinceLastPhysicsTick = 0;

	bool pauseGame = false;

	while (!stopGame)
	{
		microSecondsPerTick = 1000000 / ticksPerSecond;

		//Handle input
		//needs to be outside to allow to pause game
		input_->ProcessInput();
		audio_->Update();
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
					gameobject.second->OnPhysicsUpdate(timeSinceLastPhysicsTick);
					//gameobject.second->OnUpdate(microSecondsPerTick);
				}
				timeSinceLastPhysicsTick = 0;
			}

			if (subframe > 1)
			{
				subframe = subframe - 1.f;
			}
		}

		//Draw 
		renderer_->BeginFrame();
		for (const auto& gameobject : gameobjects_)
		{
			//gameobject.second->OnDraw(0);
			gameobject.second->OnDraw(subframe, deltaTime);
			//gameobject.second->OnDraw(1);
		}
		{
			ImGui::Begin("CodinaColada - Engine - Debug");
			ImGui::Text("%.1f FPS (subframe %f)", ImGui::GetIO().Framerate, subframe);
			ImGui::SameLine();
			ImGui::Checkbox("Pause", &pauseGame);
			ImGui::Separator();
			ImGui::SliderInt("Physic tps", &ticksPerSecond, 1, 128);

			if (ImGui::TreeNode("GameObjects"))
			{
				for (auto& it : gameobjects_)
				{
					GameObject* gameobject = it.second.get();
					if (ImGui::TreeNode(std::to_string(it.first).c_str()))
					{
						gameobject->OnDebugTreeNode();
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
			ImGui::End();
		}
		renderer_->EndFrame();
		for (auto& deletionId : gameObjectsMarkedForDeletion)
		{
			gameobjects_.erase(deletionId);
		}
		gameObjectsMarkedForDeletion.clear();
		lastFrame = currentFrame;
	}
}

void Engine::StopGame()
{
	stopGame = true;
}

bool Engine::IsStopped()
{
	return stopGame;
}

void Engine::AddGameObject(std::shared_ptr<GameObject> gameobject)
{
	
	gameobjects_.insert(std::make_pair<>(gameobject->GetId(), std::move(gameobject)));
}

void Engine::RemoveGameObject(std::shared_ptr<GameObject> gameobject)
{
	gameObjectsMarkedForDeletion.push_back(gameobject->GetId());
}

void Engine::RemoveGameObject(GameObject& gameobject)
{
	gameObjectsMarkedForDeletion.push_back(gameobject.GetId());
}


IRenderer& Engine::GetRenderer() const
{
	return *renderer_;
}

IInput& Engine::GetInput() const
{
	return *input_;
}

IAudio& Engine::GetAudio() const
{
	return *audio_;
}
