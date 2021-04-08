#pragma once

#include "../../engine/GameObject.h"

class CameraManager : public GameObject
{
private:
	int panningSpeed_ = 200;
public:
	CameraManager();


	void OnDraw(float subframe, float deltaTime) override;
	void OnDebugTreeNode() override;
};