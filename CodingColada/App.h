#pragma once

#include <iostream>

class App
{
protected:
	std::ostream& logger_;

public:

	explicit App(std::ostream& logger);


	void run();
};