#include "App.h"


App::App(std::ostream& logger, std::unique_ptr<IEngine> engine)
	: logger_(logger), engine_(std::move(engine))
{	
}

void App::run()
{
	logger_ << "Ich bin eine App? Dachte da an so ein Schachspiel.\n"; // <-- mich auskommentieren um den test zu testen(falls man sowas tut?)

	engine_->CreateWindow(640, 480);

	//engine_->MachNenViereckOderSo(); ? Oder doch eine Viereck Klasse?
}