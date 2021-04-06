#pragma once
#include "../IInput.h"

#include <vector>

struct  GLFWwindow;
class OpenGLInput : public IInput
{
protected:
	//1025 = leftmouse, 1026 = middlemouse, 1027 = rightmouse
	static int8_t keys_[1027];
	static double scrollWheel_;
	GLFWwindow* window_;
	std::vector<handlerCallbackType> keyHandlers_;
public:
	~OpenGLInput() = default;
	void RegisterWindow(void* window) override;
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void ProcessInput() override;
	bool GetKeyDown(int key) override;
	bool GetKey(int key) override;
	void AddHandler(int key, handlerCallbackType callback) override;

	// Inherited via IInput
	virtual Vector2 GetMousePosition() override;
	virtual bool GetMouseDown(int key) override;
	virtual bool GetMouse(int key) override;
	virtual int GetScrollWheel() override;
};