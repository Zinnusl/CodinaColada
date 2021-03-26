#pragma once 

#include "../GameObject.h"



#include <cstdint>

class Grid;
class HoverTile : public GameObject
{
	Grid& grid_;

public:
	HoverTile() = delete;
	HoverTile(Grid& grid);

	void OnPhysicsUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;
	void OnDraw(float subframe) override;
};