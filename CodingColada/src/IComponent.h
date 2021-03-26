#pragma once

#include <memory>

class IEngine;
class GameObject;

class IComponent
{
public:
	virtual GameObject& GetGameobject() = 0;
	virtual void OnAdded(IEngine& engine, GameObject& gameobject) = 0;
	virtual void OnRemove(IEngine& engine) = 0;
	virtual void OnUpdate(IEngine& engine, float deltaTime) = 0;
	virtual void OnDraw(IEngine& engine, float subframe) = 0;
};