#include "OpenGLInput.h"

#include "../Vector2.h"

#include <GLFW/glfw3.h>


int8_t OpenGLInput::keys_[1027];
double OpenGLInput::scrollWheel_ = 0;

void OpenGLInput::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys_[key] = 3;
		}
		else if (action == GLFW_RELEASE)
		{
			keys_[key] = 0;
		}
	}
}


void OpenGLInput::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	/*
	int left = 0;
	int right = 1;
	int middle = 2;
	*/
	int normalKeys = 1024;

	if (action == GLFW_PRESS)
	{
		keys_[normalKeys + button] = 3;
	}
	else if (action == GLFW_RELEASE)
	{
		keys_[normalKeys + button] = 0;
	}
}

void OpenGLInput::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scrollWheel_ = yoffset;
}

void OpenGLInput::RegisterWindow(void* window)
{
	window_ = (GLFWwindow*)window;
	glfwSetKeyCallback((GLFWwindow*)window, key_callback);
	glfwSetMouseButtonCallback((GLFWwindow*)window, mouse_button_callback);
	glfwSetScrollCallback((GLFWwindow*)window_, scroll_callback);
}

void OpenGLInput::ProcessInput()
{
	for (int i = 0; i < 1027; i++)
	{
		keys_[i] &= 1;
	}
	scrollWheel_ = 0;
	glfwPollEvents();
}

bool OpenGLInput::GetKeyDown(int key)
{
	return keys_[key] & 2;
}

bool OpenGLInput::GetKey(int key)
{
	return keys_[key] & 3;
}

void OpenGLInput::AddHandler(int key, handlerCallbackType callback)
{
	keyHandlers_.push_back(callback);
}


//Returns the mouse position in screen coordinates
Vector2 OpenGLInput::GetMousePosition()
{
	double xpos, ypos;
	glfwGetCursorPos(window_, &xpos, &ypos);
<<<<<<< HEAD:CodingColada/engine/opengl/OpenGLInput.cpp

	int width;
	int height;
	glfwGetWindowSize(window_, &width, &height);

	//TODO it seems to mouse position is not capped to the window but relative to it.. therefore pos it can be negative
	return Vector2(xpos, height-ypos);
=======
	return Vector2((float)xpos, (float)ypos);
>>>>>>> origin:CodingColada/engine/OpenGLRenderer/OpenGLInput.cpp
}

bool OpenGLInput::GetMouseDown(int key)
{
	return keys_[1024 + key] & 2;
}

bool OpenGLInput::GetMouse(int key)
{
	return keys_[1024 + key] & 3;
}

int OpenGLInput::GetScrollWheel()
{
	return scrollWheel_;
}