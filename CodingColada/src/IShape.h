#pragma once

#include <functional>

class IShape
{
	virtual void OnClick(int x, int y) = 0;
	virtual void RegisterClickHandler(std::function<void> callback) = 0;
	virtual void Draw() = 0;
};