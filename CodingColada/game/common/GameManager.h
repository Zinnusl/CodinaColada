#pragma once

#include "../../engine/GameObject.h"

class GameManager : public GameObject
{
public:
	GameManager();
	void OnDraw(float subframe, float deltaTime) override;

	void OnDebugTreeNode() override;
	void OnStart() override;
};