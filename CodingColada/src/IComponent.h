#pragma once

class IComponent
{
public:
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnAdded() = 0;
	virtual void OnRemove() = 0;
};