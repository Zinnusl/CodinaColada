#pragma once

#include "../../engine/GameObject.h"

class CameraManager : public GameObject
{
public:
	CameraManager();


	void OnDraw(float subframe, float deltaTime) override;
	void OnDebugTreeNode() override;
};