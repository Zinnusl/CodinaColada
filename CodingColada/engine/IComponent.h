#pragma once

#include <memory>

class IEngine;
class GameObject;

class IComponent
{
public:
	virtual GameObject& GetGameobject() = 0;
<<<<<<< HEAD:CodingColada/engine/IComponent.h
	virtual void OnAdded(Engine& engine, GameObject& gameobject) = 0;
	virtual void OnRemove(Engine& engine) = 0;
	virtual void OnUpdate(Engine& engine, float deltaTime) = 0;
	virtual void OnDraw(Engine& engine, float subframe, float deltaTime) = 0;
=======
	virtual void OnAdded(IEngine& engine, GameObject& gameobject) = 0;
	virtual void OnRemove(IEngine& engine) = 0;
	virtual void OnUpdate(IEngine& engine, float deltaTime) = 0;
	virtual void OnDraw(IEngine& engine, float subframe) = 0;
>>>>>>> origin:CodingColada/src/IComponent.h
};