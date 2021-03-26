#pragma once

#include <functional>

#include "Vector2.h"

class Engine;
class GameObject;
class IShape
{
public:
	typedef std::function<void(void)> handlerCallbackType;
	virtual ~IShape() {};
	virtual void OnClick(Vector2 clickPosition) = 0;
	virtual void RegisterClickHandler(handlerCallbackType callback) = 0;
	virtual void Draw(Engine& engine, GameObject& gameobject, float subframe) = 0;
};