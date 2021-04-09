#pragma once

#include "../../engine/GameObject.h"

class SpriteComponent;
class AnimatedSpriteComponent;
class Level : public GameObject
{
	SpriteComponent* splashScreen_;
	AnimatedSpriteComponent* loadingAnimation_;
public:
	GameManager();
	void OnDraw(float subframe, float deltaTime) override;

	void OnDebugTreeNode() override;
	void OnStart() override;
};