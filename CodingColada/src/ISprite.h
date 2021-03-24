#pragma once

#include "IComponent.h"

class Engine;
class GameObject;
class ISprite
{
public:
	/*
	typedef std::function<void(void)> handlerCallbackType;
	virtual ~ITexture() {};
	virtual void OnClick(Vector2 clickPosition) = 0;
	virtual void RegisterClickHandler(handlerCallbackType callback) = 0;
	virtual void Draw(Engine& engine, GameObject& gameobject, float subframe) = 0;
	*/

	virtual void Draw(Engine& engine, GameObject& gameobject, float subframe) = 0;
};