#pragma once 

#include "../GameObject.h"

#include <cstdint>

class HoverTile : public GameObject
{
	Vector2 size_;
public:
	HoverTile() = delete;
	HoverTile(Vector2 size);

	void OnUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;
};