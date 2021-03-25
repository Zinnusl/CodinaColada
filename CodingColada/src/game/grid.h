#pragma once 

#include "../GameObject.h"

#include <cstdint>

class Grid : public GameObject
{
	bool leftClicked_ = false;
	int32_t rows_;
	int32_t columns_;
	int32_t tileSize_;
	int32_t tileOffset_;

public:
	Grid() = delete;
	Grid(int32_t rows, int32_t columns, int32_t tileSize, int32_t tileOffset);

	void OnUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;
};