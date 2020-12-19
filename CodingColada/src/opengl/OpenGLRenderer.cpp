#include "OpenGLRenderer.h"

#include "glad/glad.h"
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
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (const auto& shape : shapes_)
	{
		shape->Draw();
	}
	glfwSwapBuffers(window_);
}

void OpenGLRenderer::AddShape(std::unique_ptr<IShape> shape)
{
	shapes_.push_back(std::move(shape));
}

void OpenGLRenderer::OnClick(Vector2 clickPosition)
{

}

void* OpenGLRenderer::CreateWindow(int x, int y)
{
	glfwWindowHint(GLFW_RESIZABLE, true);
	
	int xPos, yPos, width, height;
	auto primaryMonitor = glfwGetPrimaryMonitor();
	glfwGetMonitorWorkarea(primaryMonitor, &xPos, &yPos , &width, &height);
	window_ = glfwCreateWindow(x, y, "GLFWWindow", nullptr, nullptr);
	//window_ = glfwCreateWindow(x, y, "GLFWWindow", nullptr, nullptr);
	glfwMakeContextCurrent(window_);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("FATAL ERROR: Failed to initialize GLAD\n");
	}
	
	glViewport(0, 0, x, y);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return window_;
}
