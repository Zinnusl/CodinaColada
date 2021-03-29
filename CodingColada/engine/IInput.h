#pragma once

#include <functional>

class Vector2;
class IInput
{
public:
	typedef std::function<void(void)> handlerCallbackType;
	virtual ~IInput() {};

	//Fabis input system
	virtual void RegisterWindow(void* window) = 0;
	virtual void ProcessInput() = 0;
	virtual bool GetKeyDown(int key) = 0;
	virtual bool GetKey(int key) = 0;
	virtual bool GetMouseDown(int key) = 0;
	virtual bool GetMouse(int key) = 0;
	virtual Vector2 GetMousePosition() = 0;

	//Andi input system
	virtual void AddHandler(int key, handlerCallbackType callback) = 0;
};