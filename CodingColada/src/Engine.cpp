#include "Engine.h"

#include "IRenderer.h"
#include "IInput.h"
#include "RigidbodyComponent.h"
#include <chrono>

Engine::Engine(std::unique_ptr<IRenderer> renderer, std::unique_ptr<IInput> input)
	: renderer_(std::move(renderer)), input_(std::move(input))
{
	GameObject::engine_ = this;
}

void Engine::StartGame()
{
	auto lastFrame = std::chrono::steady_clock::now();

	while (!stopGame)
	{
		auto currentFrame = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrame - lastFrame).count();
		
		//input
		input_->ProcessInput();

		//update (physics...)
		for (const auto& gameobject : gameobjects_)
		{
			//gameobject.second->OnUpdate(*this, deltaTime);
			gameobject.second->OnUpdate(deltaTime);
		}

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
						printf("Collision\n");
					}
				}
			}
		}

		renderer_->BeginFrame();

		//draw gameobjects
		for (const auto& gameobject : gameobjects_)
		{
			//gameobject.second->OnUpdate(*this, deltaTime);
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