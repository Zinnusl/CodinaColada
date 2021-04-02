#pragma once

#include "IComponent.h"

/*
* Disclaimer: Collisions are buggy
*/
class NetworkComponent : public IComponent
{
protected:
	int32_t networkId_;

public:
	NetworkComponent() = delete;
	NetworkComponent(const NetworkComponent&) = delete;
	NetworkComponent(int32_t networkId);

	void OnServerMessage();

	// Inherited via IComponent
	virtual void OnAdded(Engine& engine, GameObject& gameobject) override;
	virtual void OnRemove(Engine& engine) override;
	virtual void OnUpdate(Engine& engine, float deltaTime) override;
	virtual void OnDraw(Engine& engine, float subframe, float deltaTime) override;
};