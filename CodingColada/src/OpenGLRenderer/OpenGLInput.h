#pragma once

#include "../IInput.h"

#include <vector>

struct  GLFWwindow;
class OpenGLInput : public IInput
{
protected:
	static int8_t keys_[1024];
	std::vector<handlerCallbackType> keyHandlers_;
public:
	~OpenGLInput() = default;
	void RegisterWindow(void* window) override;
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void ProcessInput() override;
	bool GetKeyDown(int key) override;
	bool GetKey(int key) override;
	void AddHandler(int key, handlerCallbackType callback) override;
};