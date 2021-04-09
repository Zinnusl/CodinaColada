#pragma once

#include "../../engine/GameObject.h"

#include <memory>

class SpriteComponent;
class AnimatedSpriteComponent;
class Grid;
class Player;
class GameManager : public GameObject
{
	std::shared_ptr<Grid> grid_;
	std::vector<std::shared_ptr<Player>> players_;
	int32_t round_;
	int32_t customBlocksThisRound;
	int8_t  levelLayout[16 * 16];


	SpriteComponent* splashScreen_;
	AnimatedSpriteComponent* loadingAnimation_;
public:
	GameManager();
	void OnDraw(float subframe, float deltaTime) override;

	void OnDebugTreeNode() override;
	void OnStart() override;
};