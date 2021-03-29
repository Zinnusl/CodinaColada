// CodingColada.cpp : Defines the entry point for the application.
//

#include "ServerApp.h"
#include "../../engine/opengl/OpenGLRenderer.h"
#include "../../engine/opengl/OpenGLInput.h"


int main()
{
	std::unique_ptr<OpenGLRenderer> renderer = std::make_unique<OpenGLRenderer>();
	std::unique_ptr<OpenGLInput> input = std::make_unique<OpenGLInput>();

	std::unique_ptr<Engine> engine = std::make_unique<Engine>(std::move(renderer), std::move(input));
	auto app = std::make_unique<ServerApp>(std::cout, std::move(engine));
	app->run();

	return 0;
}