#pragma once

#include <functional>

class IInput
{
public:
	typedef std::function<void(void)> handlerCallbackType;
	virtual ~IInput() {};
	virtual void GetKeyDown(int key) = 0;
	virtual void GetKey(int key) = 0;
	virtual void AddHandler(int key, handlerCallbackType callback) = 0;
};