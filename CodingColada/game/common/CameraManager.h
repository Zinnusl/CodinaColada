#pragma once

#include "../../engine/GameObject.h"

class CameraManager : public GameObject
{
public:
	CameraManager();

	Vector2 WorldToScreen(Vector2 worldPosition);


	void OnDraw(float subframe, float deltaTime) override;
	void OnDebugTreeNode() override;
};