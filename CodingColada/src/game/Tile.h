#pragma once 

#include "../GameObject.h"

class Tile : public GameObject
{
public:
	Tile() = delete;
	Tile(Vector2 position);

	void OnUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;
};