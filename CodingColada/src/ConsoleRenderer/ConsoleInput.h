#pragma once

#include <vector>

#include "../IInput.h"
#include "../Vector2.h"

class ConsoleInput : public IInput
{
protected:
	static int8_t keys_[1024];
	std::vector<handlerCallbackType> keyHandlers_;
public:
	explicit ConsoleInput() = default;
	~ConsoleInput() = default;


	void RegisterWindow(void* window) override
	{}	
	void ProcessInput() override
	{}
	bool GetKeyDown(int key) override
	{
		return false;
	}
	bool GetKey(int key) override
	{
		return false;	
	}




	bool GetMouseDown(int key)
	{
		return false;
	}
	bool GetMouse(int key)
	{
		return false;
	}
	Vector2 GetMousePosition()
	{
		return Vector2(0.f);
	}






	void AddHandler(int key, handlerCallbackType callback) override
	{}
};