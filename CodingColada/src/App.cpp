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
	ChessPiece(IEngine& engine)
		: GameObject(engine)
	{

	}

	void OnUpdate(IEngine& engine, float deltaTime) override
	{
		//printf("ChessPiece OnUpdate with deltaTime %f\n", deltaTime);
	}
};


GameManager::GameManager(IEngine& engine)
	: GameObject(engine)
{

}

void GameManager::OnUpdate(IEngine& engine, float deltaTime)
{
	int GLFW_KEY_ESCAPE = 256;
	if (engine.GetInput().GetKey(GLFW_KEY_ESCAPE))
	{
		engine.StopGame();
	}
}


App::App(std::ostream& logger, IEngine& engine, boost::di::extension::ifactory<GameManager>& f_gm)
	: logger_(logger), engine_(engine), f_gm_(f_gm)
{
}

void App::run()
{
	logger_ << "Ich bin eine App? Dachte da an so ein Schachspiel.\n"; // <-- mich auskommentieren um den test zu testen(falls man sowas tut?)

	logger_ << "Ist das weirklich hier? 1\n";
	auto gameManager = f_gm_.create();
	logger_ << "Ist das weirklich hier? 2\n";

	gameManager->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<RectangleShape>(Vector2(0), Vector2(100))));
	engine_.AddGameObject(std::move(gameManager));

	//Chess has 32 pieces
	for (int i = 0; i < 32; i++)
	{
		engine_.AddGameObject(std::make_unique<ChessPiece>(engine_));
	}
	
	engine_.StartGame();
}