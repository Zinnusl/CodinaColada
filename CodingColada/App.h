#pragma once

#include <iostream>
#include "IEngine.h"

class App
{
protected:
	std::ostream& logger_;
	std::unique_ptr<IEngine> engine_;
	
public:

	explicit App(std::ostream& logger, std::unique_ptr<IEngine> engine);

	void run();
};