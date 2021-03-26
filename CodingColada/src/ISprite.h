#pragma once

#include "IComponent.h"

class Engine;
class GameObject;
class ISprite
{
public:
	virtual void Draw(Engine& engine, GameObject& gameobject, float subframe) = 0;
};