#pragma once

#include <functional>

class IInput
{
	virtual void GetKeyDown(int key) = 0;
	virtual void GetKey(int key) = 0;
	virtual void AddHandler(int key, std::function callback) = 0;
};