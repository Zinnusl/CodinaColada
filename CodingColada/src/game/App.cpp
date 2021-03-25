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
#include "Paddle.h"
#include "GameManager.h"
#include "Grid.h"

App::App(std::ostream& logger, std::unique_ptr<Engine> engine)
	: logger_(logger), engine_(std::move(engine))
{
}

void App::run()
{
	const Vector2 windowSize = { 2560, 1440 };
	void* window = engine_->GetRenderer().CreateWindow(windowSize.GetX(), windowSize.GetY());
	engine_->GetInput().RegisterWindow(window);

	auto gameManager = std::make_unique<GameManager>();
	auto grid = std::make_unique<Grid>(64, 64, 8, 16);
	grid->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(windowSize, Color(0, 0, 1, 0.1), &OpenGLRenderer::shaders_["grid"])));

	Vector2 paddleSize = { 20, 200 };
	auto paddle1 = std::make_unique<Paddle>(Vector2(40, 400));
	paddle1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(0, 0, 1, 1))));
	paddle1->AddComponent(std::make_unique<RigidbodyComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(0, 1, 0, 0.2))));

	auto paddle2 = std::make_unique<Paddle>(Vector2(windowSize.GetX() - 60, 400));
	paddle2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(1, 0, 0, 1))));
	paddle2->AddComponent(std::make_unique<RigidbodyComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(0, 1, 0, 0.2))));

	auto ball = std::make_unique<Ball>(Vector2(800, 450));
	//ball->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(20), Color(0, 1, 0, 1))));
	ball->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(OpenGLRenderer::shaders_["sprite"], OpenGLRenderer::textures_["watermelon"])));
	ball->AddComponent(std::make_unique<RigidbodyComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(64), Color(0, 1, 0, 0.2))));

	engine_->AddGameObject(std::move(gameManager));
	engine_->AddGameObject(std::move(grid));
	engine_->AddGameObject(std::move(paddle1));
	engine_->AddGameObject(std::move(paddle2));
	engine_->AddGameObject(std::move(ball));

	engine_->StartGame();
}