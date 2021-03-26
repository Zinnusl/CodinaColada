#pragma once 

#include "../GameObject.h"

#include <cstdint>

class PathTile : public GameObject
{
public:
	PathTile() = delete;
	PathTile(Vector2 position);

	void OnDraw(float subframe) override;
};