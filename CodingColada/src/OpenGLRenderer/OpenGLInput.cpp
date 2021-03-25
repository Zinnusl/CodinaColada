#include "OpenGLInput.h"

#include <GLFW/glfw3.h>


int8_t OpenGLInput::keys_[1024];

void OpenGLInput::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

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

void OpenGLInput::RegisterWindow(void* window)
{
	glfwSetKeyCallback((GLFWwindow*)window, key_callback);
}

void OpenGLInput::ProcessInput()
{
	for (int i = 0; i < 1024; i++)
	{
		keys_[i] &= 1;
	}
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

