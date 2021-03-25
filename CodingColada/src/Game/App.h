#pragma once

#include <iostream>

#include "boost/di/extension/injections/factory.hpp"

#include "../IEngine.h"
#include "../GameObject.h"

class GameManager : public GameObject
{
public:
	GameManager(IEngine& engine);
	void OnUpdate(IEngine& engine, float deltaTime) override;
};

class App
{
protected:
	std::ostream& logger_;
	IEngine& engine_;
	boost::di::extension::ifactory<GameManager>& f_gm_;
	
public:

	App(std::ostream& logger, IEngine& engine, boost::di::extension::ifactory<GameManager>& f_gm);

	void run();
};