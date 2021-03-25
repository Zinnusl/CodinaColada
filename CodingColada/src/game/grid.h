#pragma once 

#include "../GameObject.h"

#include <cstdint>

class Grid : public GameObject
{
	bool leftClicked_ = false;
	int32_t rows_;
	int32_t columns_;

public:
	Grid() = delete;
	Grid(int32_t rows, int32_t columns);

	void OnUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;
};