#pragma once

#include "IComponent.h"
#include "Color.h"

class Engine;
class GameObject;
class ISprite
{
public:
	virtual Color GetColor() = 0;
	virtual void SetColor(Color color) = 0;

	virtual void Draw(Engine& engine, GameObject& gameobject, float subframe) = 0;
};