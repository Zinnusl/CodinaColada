#pragma once

#include "../GameObject.h"

class GameManager : public GameObject
{
public:
	GameManager();
	void OnUpdate(float deltaTime) override;

	void OnDebugTreeNode() override;
};