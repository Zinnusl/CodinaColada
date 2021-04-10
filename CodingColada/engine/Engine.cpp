#include "Engine.h"

#include "IRenderer.h"
#include "IInput.h"
#include "RigidbodyComponent.h"

#include "imgui.h"

#include <chrono>
#include <iostream>
#include <string> 

<<<<<<< HEAD:CodingColada/engine/Engine.cpp

Engine::Engine(std::shared_ptr<IRenderer> renderer, std::unique_ptr<IInput> input, std::unique_ptr<IAudio> audio)
	: renderer_(std::move(renderer)), input_(std::move(input)), audio_(std::move(audio))
=======
Engine::Engine(IRenderer& renderer, IInput& input)
	: renderer_(renderer), input_(input)
>>>>>>> origin:CodingColada/src/Engine.cpp
{
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
<<<<<<< HEAD:CodingColada/engine/Engine.cpp
		microSecondsPerTick = 1000000 / ticksPerSecond;

		//Handle input
		//needs to be outside to allow to pause game
		input_->ProcessInput();
		audio_->Update();
=======
		// Needs to be outside to allow to pause game
		input_.ProcessInput();

>>>>>>> origin:CodingColada/src/Engine.cpp
		currentFrame = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentFrame - lastFrame).count();

		if (!pauseGame)
		{
			timeSinceLastPhysicsTick += (int32_t)deltaTime;

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
<<<<<<< HEAD:CodingColada/engine/Engine.cpp
					gameobject.second->OnPhysicsUpdate(timeSinceLastPhysicsTick);
=======
					gameobject.second->OnUpdate((float)timeSinceLastPhysicsTick);
>>>>>>> origin:CodingColada/src/Engine.cpp
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
		renderer_.BeginFrame();
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
<<<<<<< HEAD:CodingColada/engine/Engine.cpp
		renderer_->EndFrame();
		for (auto& deletionId : gameObjectsMarkedForDeletion)
		{
			gameobjects_.erase(deletionId);
		}
		gameObjectsMarkedForDeletion.clear();
=======
		renderer_.EndFrame();

>>>>>>> origin:CodingColada/src/Engine.cpp
		lastFrame = currentFrame;
	}
}

void Engine::StopGame()
{
	stopGame = true;
}

bool Engine::IsStopped()
{
<<<<<<< HEAD:CodingColada/engine/Engine.cpp
	return stopGame;
=======
	static int32_t gameObjectId = 1;
	gameobjects_.insert(std::make_pair<>(gameObjectId++, std::move(gameobject)));
>>>>>>> origin:CodingColada/src/Engine.cpp
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
	return renderer_;
}

IInput& Engine::GetInput() const
{
<<<<<<< HEAD:CodingColada/engine/Engine.cpp
	return *input_;
}

IAudio& Engine::GetAudio() const
{
	return *audio_;
}
=======
	return input_;
}
>>>>>>> origin:CodingColada/src/Engine.cpp
