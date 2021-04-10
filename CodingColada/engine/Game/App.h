#pragma once

#include <iostream>

#include "boost/di/extension/injections/factory.hpp"

#include "../IEngine.h"
#include "../GameObject.h"
#include "Ball.h"
#include "Paddle.h"

namespace di = boost::di;

class App
{
protected:
	std::ostream& logger_;
	IEngine& engine_;
	Ball::ifactory_t& ball_factory_;
	Paddle::ifactory_t& paddle_factory_;
	
public:
	App(std::ostream& logger, IEngine& engine, Paddle::ifactory_t& paddle_factory, Ball::ifactory_t& ball_factory);

	void run();
};