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
};