#include "ServerApp.h"

#include <thread>
#include <chrono>

#include "../../engine/IRenderer.h"
#include "../../engine/GameObject.h"
#include "../../engine/ShapeComponent.h"
#include "../../engine/SpriteComponent.h"
#include "../../engine/RigidbodyComponent.h"
#include "../../engine/opengl/OpenGLRectangleShape.h"
#include "../../engine/opengl/OpenGLRenderer.h"
#include "../../engine/opengl/OpenGLSprite.h"
#include "../../engine/Color.h"

#include "imgui.h"

#include "../common/Ball.h"
#include "../common/Paddle.h"
#include "../common/GameManager.h"
#include "../common/Grid.h"
#include "../common/HoverTile.h"

#include "CustomServer.h"

void StartServer()
{
	CustomServer server(1337);
	server.Start();
	while (!GameObject::engine_->IsStopped())
	{
		server.Update(-1, true);
	}
	//TODO issues with joining the thread etc
	server.Stop();
}

ServerApp::ServerApp(std::ostream& logger, std::unique_ptr<Engine> engine)
	: logger_(logger), engine_(std::move(engine))
{
}

void ServerApp::run()
{
	const Vector2 windowSize = { 2560, 1440 };
	void* window = engine_->GetRenderer().CreateWindow(windowSize.GetX(), windowSize.GetY(), windowSize.GetX(), windowSize.GetY(), false);
	engine_->GetInput().RegisterWindow(window);

	auto gameManager = std::make_unique<GameManager>();
	auto grid = std::make_unique<GameObject>(Vector2(0,0));
	grid->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(windowSize, Color(0, 0, 1, 0.1), &OpenGLRenderer::shaders_["grid"])));

	Vector2 paddleSize = { 20, 200 };
	auto paddle1 = std::make_unique<Paddle>(Vector2(40, 400));
	paddle1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(0, 0, 1, 1))));
	paddle1->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto paddle2 = std::make_unique<Paddle>(Vector2(windowSize.GetX() - 60, 400));
	paddle2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(1, 0, 0, 1))));
	paddle2->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto ball = std::make_unique<Ball>(Vector2(800, 450));
	//ball->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(20), Color(0, 1, 0, 1))));
	ball->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["sprite"], OpenGLRenderer::textures_["watermelon"])));
	ball->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));

	engine_->AddGameObject(std::move(gameManager));
	engine_->AddGameObject(std::move(grid));
	engine_->AddGameObject(std::move(paddle1));
	engine_->AddGameObject(std::move(paddle2));
	engine_->AddGameObject(std::move(ball));

	std::thread first(StartServer);
	engine_->StartGame();
	first.join();
}