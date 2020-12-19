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
	std::ostream& logger_;
	std::unique_ptr<Engine> engine_;
	
public:
	App(std::ostream& logger, std::unique_ptr<Engine> engine);

	void run();
};