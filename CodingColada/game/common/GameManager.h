#pragma once

#include "../../engine/GameObject.h"

class GameManager : public GameObject
{
public:
	GameManager();
	void OnDraw(float deltaTime) override;

	void OnDebugTreeNode() override;
};