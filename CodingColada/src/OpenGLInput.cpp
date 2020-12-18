#include "OpenGLInput.h"

#include <GLFW/glfw3.h>

void OpenGLInput::ProcessInput()
{
	glfwPollEvents();
}

void OpenGLInput::GetKeyDown(int key)
{
}

void OpenGLInput::GetKey(int key)
{
}

void OpenGLInput::AddHandler(int key, handlerCallbackType callback)
{
	keyHandlers_.push_back(callback);
}