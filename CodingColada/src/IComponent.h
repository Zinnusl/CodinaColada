#pragma once

class Engine;
class IComponent
{
public:
	virtual void OnUpdate(Engine& engine, float deltaTime) = 0;
	virtual void OnAdded(Engine& engine) = 0;
	virtual void OnRemove(Engine& engine) = 0;
};