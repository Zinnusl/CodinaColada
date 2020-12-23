#pragma once

#include "IShape.h"
#include "Vector2.h"

#include <memory>

class GameObject;
class IRenderer
{
public:
	virtual ~IRenderer() {};
	virtual void BeginFrame() = 0;
	virtual void Draw(GameObject& gameobject) = 0;
	virtual void EndFrame() = 0;
	virtual void OnClick(Vector2 clickPosition) = 0;

	//TODO. IInput needs a way to get the window so it can register for the input events
	virtual void* CreateWindow(int x, int y) = 0;
};