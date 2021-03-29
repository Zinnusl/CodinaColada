#pragma once

#include <iostream>

#include "../../engine/Engine.h"

class ServerApp
{
protected:
	std::ostream& logger_;
	std::unique_ptr<Engine> engine_;
	
public:
	ServerApp(std::ostream& logger, std::unique_ptr<Engine> engine);

	void run();
};