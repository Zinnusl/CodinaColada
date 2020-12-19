#pragma once

#include <iostream>

#include "Engine.h"

class GameManager : public GameObject
{
public:
	GameManager();
	void OnUpdate(float deltaTime) override;
};

class App
{
protected:
	//std::ostream& logger_;
	std::unique_ptr<Engine> engine_;
	
public:
	App(std::unique_ptr<Engine> engine);
	//App(std::ostream& logger, Engine& engine);

	void run();
};