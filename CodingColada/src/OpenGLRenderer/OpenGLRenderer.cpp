#include "OpenGLRenderer.h"
#include "../IInput.h"

#include "GLFW/glfw3.h"

OpenGLRenderer::OpenGLRenderer()
	: window_(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

OpenGLRenderer::~OpenGLRenderer()
{
	if (window_) {
		glfwDestroyWindow(window_);
	}
	glfwTerminate();
}

void OpenGLRenderer::Draw()
{
	for (const auto& shape : shapes_)
	{
		shape->Draw();
	}
}

void OpenGLRenderer::AddShape(std::unique_ptr<IShape> shape)
{
	shapes_.push_back(std::move(shape));
}

void OpenGLRenderer::OnClick(Vector2 clickPosition)
{
}

void OpenGLRenderer::CreateWindow(int x, int y, IInput& input)
{
	glfwWindowHint(GLFW_RESIZABLE, true);
	input.RegisterWindow(glfwCreateWindow(x, y, "GLFWWindow", nullptr, nullptr));
}
