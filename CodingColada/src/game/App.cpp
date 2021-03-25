#include "App.h"

#include <thread>
#include <chrono>

#include "../IRenderer.h"
#include "../GameObject.h"
#include "../ShapeComponent.h"
#include "../SpriteComponent.h"
#include "../RigidbodyComponent.h"
#include "../opengl/OpenGLRectangleShape.h"
#include "../opengl/OpenGLRenderer.h"
#include "../opengl/OpenGLSprite.h"
#include "../Color.h"
#include "imgui.h"

#include "Ball.h"
#include "GameManager.h"


class Paddle : public GameObject
{
	float speed = 0.001;
public:
	Paddle()
	{
	}
	
	Paddle(Vector2 position)
		: GameObject(position)
	{
	}
	
	void OnUpdate(float deltaTime) override
	{
		previousPosition_ = currentPosition_;

		#define 	GLFW_KEY_DOWN   264
		#define 	GLFW_KEY_UP   265
		const int maxMove = 700;
		if (engine_->GetInput().GetKey(GLFW_KEY_DOWN))
		{
			float yPos = currentPosition_.GetY();
			if (currentPosition_.GetY() > 0)
			{
				float newPos = currentPosition_.GetY() - speed * deltaTime;
				if (newPos < 0)
				{
					newPos = 0;
				}
				currentPosition_.SetY(newPos);
			}
		}
		if (engine_->GetInput().GetKey(GLFW_KEY_UP))
		{
			float yPos = currentPosition_.GetY();
			if (currentPosition_.GetY() < maxMove)
			{
				float newPos = currentPosition_.GetY() + speed * deltaTime;
				if (newPos > maxMove)
				{
					newPos = maxMove;
				}
				currentPosition_.SetY(newPos);
			}
		}
	}

	void OnDebugTreeNode() override
	{
		ImGui::Text("Paddle");
	}
};





App::App(std::ostream& logger, std::unique_ptr<Engine> engine)
	: logger_(logger), engine_(std::move(engine))
{
}

void App::run()
{
	const Vector2 windowSize = { 1600, 900 };
	void* window = engine_->GetRenderer().CreateWindow(windowSize.GetX(), windowSize.GetY());
	engine_->GetInput().RegisterWindow(window);

	auto gameManager = std::make_unique<GameManager>();

	Vector2 paddleSize = { 20, 200 };
	auto paddle1 = std::make_unique<Paddle>(Vector2(40, 400));
	paddle1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(0, 0, 1, 1))));
	paddle1->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto paddle2 = std::make_unique<Paddle>(Vector2(1540, 400));
	paddle2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(1, 0, 0, 1))));
	paddle2->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto ball = std::make_unique<Ball>(Vector2(800, 450));
	//ball->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(20), Color(0, 1, 0, 1))));
	ball->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(OpenGLRenderer::shaders_["sprite"], OpenGLRenderer::textures_["watermelon"])));
	ball->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(20)));

	engine_->AddGameObject(std::move(gameManager));
	engine_->AddGameObject(std::move(paddle1));
	engine_->AddGameObject(std::move(paddle2));
	engine_->AddGameObject(std::move(ball));

	engine_->StartGame();
}