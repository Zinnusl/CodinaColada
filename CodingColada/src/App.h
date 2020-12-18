#pragma once

#include <iostream>

#include "boost/di/extension/injections/factory.hpp"

#include "Engine.h"

class GameManager : public GameObject
{
public:
	GameManager(Engine& engine);
	void OnUpdate(Engine& engine, float deltaTime) override;
};

class App
{
protected:
	std::ostream& logger_;
	Engine& engine_;
	boost::di::extension::ifactory<GameManager>& f_gm_;
	
public:

	App(std::ostream& logger, Engine& engine, boost::di::extension::ifactory<GameManager>& f_gm);

	void run();
};