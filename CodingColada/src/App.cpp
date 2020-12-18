#include "App.h"

#include <thread>
#include <chrono>

#include "IRenderer.h"
#include "GameObject.h"
#include "RectangleShape.h"
#include "ShapeComponent.h"

class ChessPiece : public GameObject
{
public:
	void OnUpdate(Engine& engine, float deltaTime) override
	{
		//printf("ChessPiece OnUpdate with deltaTime %f\n", deltaTime);
	} 
};


class GameManager : public GameObject
{
public:
	void OnUpdate(Engine& engine, float deltaTime) override
	{
		int GLFW_KEY_ESCAPE = 256;
		if (engine.GetInput().GetKey(GLFW_KEY_ESCAPE))
		{
			engine.StopGame();
		}
	}
};


App::App(std::ostream& logger, std::unique_ptr<Engine> engine)
	: logger_(logger), engine_(std::move(engine))
{	
}

void App::run()
{
	logger_ << "Ich bin eine App? Dachte da an so ein Schachspiel.\n"; // <-- mich auskommentieren um den test zu testen(falls man sowas tut?)

	auto gameManager = std::make_unique<GameManager>();

	gameManager->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<RectangleShape>(Vector2(0), Vector2(100))));
	
	engine_->AddGameObject(std::move(gameManager));

	//Chess has 32 pieces
	for (int i = 0; i < 32; i++)
	{
		engine_->AddGameObject(std::make_unique<ChessPiece>());
	}

	void* window = engine_->GetRenderer().CreateWindow(640, 480);
	engine_->GetInput().RegisterWindow(window);

	engine_->StartGame();
}