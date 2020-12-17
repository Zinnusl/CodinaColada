#pragma once

#include <iostream>
#include "IEngine.h"

class App
{
protected:
	std::ostream& logger_;
	std::unique_ptr<IEngine> engine_;
	
public:

	App(std::ostream& logger, std::unique_ptr<IEngine> engine);

	void run();
};