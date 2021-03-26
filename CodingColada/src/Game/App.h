#pragma once

#include <iostream>

#include "boost/di/extension/injections/factory.hpp"

#include "../IEngine.h"
#include "../GameObject.h"

class App
{
protected:
	std::ostream& logger_;
	IEngine& engine_;
	
public:
	App(std::ostream& logger, IEngine& engine);

	void run();
};