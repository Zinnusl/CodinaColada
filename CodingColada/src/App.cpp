#include "App.h"

#include <thread>
#include <chrono>

#include "IRenderer.h"
#include "GameObject.h"

class ChessPiece : public GameObject
{
public:
	void OnUpdate(float deltaTime)
	{
		//printf("ChessPiece OnUpdate with deltaTime %f\n", deltaTime);
	}
	void AddComponent(std::unique_ptr <IComponent> component)
	{
		printf("ChessPiece AddComponent\n");
	}
	void RemoveComponent(std::unique_ptr <IComponent> component)
	{
		printf("ChessPiece RemoveComponent\n");
	}
};


App::App(std::ostream& logger, std::unique_ptr<Engine> engine)
	: logger_(logger), engine_(std::move(engine))
{	
}

void App::run()
{
	logger_ << "Ich bin eine App? Dachte da an so ein Schachspiel.\n"; // <-- mich auskommentieren um den test zu testen(falls man sowas tut?)

	//Chess has 32 pieces
	for (int i = 0; i < 32; i++)
	{
		engine_->AddGameObject(std::make_unique<ChessPiece>());
	}

	engine_->GetRenderer().CreateWindow(640, 480);

	//TODO do I really need to use a raw pointer?
	std::thread engineThread(&Engine::StartGame, &*engine_);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	engine_->StopGame();
	engineThread.join();

	//engine_->MachNenViereckOderSo(); ? Oder doch eine Viereck Klasse?
}