#pragma once

#include <memory>

class Engine;
class GameObject;
class IComponent
{
public:
	virtual GameObject& GetGameobject() = 0;
	virtual void OnAdded(Engine& engine, GameObject& gameobject) = 0;
	virtual void OnRemove(Engine& engine) = 0;
	virtual void OnUpdate(Engine& engine, float deltaTime) = 0;
	virtual void OnDraw(Engine& engine, float subframe, float deltaTime) = 0;
};