#include "App.h"

#include <thread>
#include <chrono>

#include "../IRenderer.h"
#include "../GameObject.h"
#include "../RectangleShape.h"
#include "../ShapeComponent.h"
#include "../IRenderer.h"
#include "../GameObject.h"
#include "../ShapeComponent.h"
#include "../SpriteComponent.h"
#include "../RigidbodyComponent.h"
#include "../OpenGLRenderer/OpenGLRectangleShape.h"
#include "../OpenGLRenderer/OpenGLRenderer.h"
#include "../OpenGLRenderer/OpenGLSprite.h"
#include "../OpenGLRenderer/Color.h"
#include "imgui.h"
#include "Ball.h"
#include "Paddle.h"
#include "boost/di.hpp"
#include "boost/di/extension/injections/factory.hpp"
#include "boost/di/extension/injections/shared_factory.hpp"

namespace di = boost::di;

class GameManager : public GameObject
{
public:
	GameManager(IEngine& engine) : GameObject(engine)
	{
	}
	void OnUpdate(float deltaTime) override
	{
		int GLFW_KEY_ESCAPE = 256;
		if (engine_.GetInput().GetKeyDown(GLFW_KEY_ESCAPE))
		{
			if (components_.size() > 0)
			{
				RemoveComponent(*components_[0]);
			}
			else
			{
				engine_.StopGame();
			}
		}
	}
};


App::App(std::ostream& logger, IEngine& engine, Paddle::ifactory_t& paddle_factory, Ball::ifactory_t& ball_factory)
	: logger_(logger), engine_(engine), ball_factory_(ball_factory), paddle_factory_(paddle_factory)
{
}

void App::run()
{
	const Vector2 windowSize = { 1600, 900 };
	engine_.GetRenderer().CreateWindow((int)windowSize.GetX(), (int)windowSize.GetY(), engine_.GetInput());
	//logger_ << "Ich bin eine App? Dachte da an so ein Schachspiel.\n"; // <-- mich auskommentieren um den test zu testen(falls man sowas tut?)

	//auto gameManager = std::make_unique<GameManager>(engine_);
	auto gameManager = std::make_unique<GameManager>(engine_);

	/*
	auto shape = std::make_unique<OpenGLRectangleShape>(Vector2(200, 300), Vector2(200, 70), Color(1, 0, 0, 1));
	auto shapeComponent = std::make_unique<ShapeComponent>(std::move(shape));
	gameManager->AddComponent(std::move(shapeComponent));
	*/

	//Vector2(windowSize.GetX() - paddleSize.GetX() * 2 - paddleSize.GetX(), windowSize.GetY() / 2 - paddleSize.GetY() / 2)

	Vector2 paddleSize = { 20, 200 };
	//auto paddle1 = std::make_unique<Paddle>(Vector2(40, 400));
	auto paddle1 = paddle_factory_.create(Vector2(40, 400));
	paddle1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color{ 0, 0, 1, 1 })));
	paddle1->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	//auto paddle2 = std::make_unique<Paddle>(Vector2(1540, 400));
	auto paddle2 = paddle_factory_.create(Vector2(1540, 400));
	paddle2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color{ 1, 0, 0, 1 })));
	paddle2->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	//auto ball = std::make_unique<Ball>(Vector2(800, 450));
	auto ball = ball_factory_.create(Vector2(800, 450), Vector2(0.0004f));
	//ball->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(20), Color(0, 1, 0, 1))));
	ball->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(dynamic_cast<OpenGLRenderer&>(engine_.GetRenderer()).GetShader("sprite"), dynamic_cast<OpenGLRenderer&>(engine_.GetRenderer()).GetTexture("watermelon"))));
	ball->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(20)));

	engine_.AddGameObject(std::move(gameManager));
	engine_.AddGameObject(std::move(paddle1));
	engine_.AddGameObject(std::move(paddle2));
	engine_.AddGameObject(std::move(ball));

	engine_.StartGame();
}