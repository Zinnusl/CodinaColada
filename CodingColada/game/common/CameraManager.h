#pragma once

#include "../../engine/GameObject.h"

class CameraManager : public GameObject
{
public:
	CameraManager();
	void OnDraw(float deltaTime) override;

	void OnDebugTreeNode() override;
};