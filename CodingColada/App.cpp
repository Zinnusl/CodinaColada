#include "App.h"

App::App(std::ostream& logger)
	: logger_(logger)
{	
}

void App::run()
{
	logger_ << "Ich bin eine App?\n";
}