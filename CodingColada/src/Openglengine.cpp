#include "Openglengine.h"

#include <gl/glew.h>
#include "GLFW/glfw3.h"


Openglengine::Openglengine()
{
}

Openglengine::~Openglengine()
{
}

void Openglengine::CreateWindow(const int size_x, const int size_y)
{
	glfwInit();
	window_ = glfwCreateWindow(size_x, size_y, "FhsEngine", nullptr, nullptr);
}

IRenderer* Openglengine::GetRenderer() const
{
	return renderer_;
}
