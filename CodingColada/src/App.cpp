#include "App.h"

#include <thread>
#include <chrono>

#include "IRenderer.h"
#include "GameObject.h"
#include "ShapeComponent.h"
#include "opengl/OpenGLRectangleShape.h"


class ChessPiece : public GameObject
{
public:
	ChessPiece()
	{

	}

	void OnUpdate(float deltaTime) override
	{
		printf("ChessPiece OnUpdate with deltaTime %f\n", deltaTime);
	}
};

GameManager::GameManager()
{

}

void GameManager::OnUpdate(float deltaTime)
{
	int GLFW_KEY_ESCAPE = 256;
	if (engine_->GetInput().GetKey(GLFW_KEY_ESCAPE))
	{
		engine_->StopGame();
	}
}

App::App(std::ostream& logger, std::unique_ptr<Engine> engine)
	: logger_(logger), engine_(std::move(engine))
{
}

void App::run()
{
	//logger_ << "Ich bin eine App? Dachte da an so ein Schachspiel.\n"; // <-- mich auskommentieren um den test zu testen(falls man sowas tut?)

	//auto gameManager = std::make_unique<GameManager>(engine_);
	auto gameManager = std::make_unique<GameManager>();
 	
	auto shape = std::make_unique<OpenGLRectangleShape>(Vector2(0), Vector2(100));
	auto shapeComponent = std::make_unique<ShapeComponent>(std::move(shape));
	gameManager->AddComponent(std::move(shapeComponent));
	
	engine_->AddGameObject(std::move(gameManager));

	//Chess has 32 pieces
	for (int i = 0; i < 32; i++)
	{
		engine_->AddGameObject(std::make_unique<ChessPiece>());
	}

	engine_->StartGame();
}