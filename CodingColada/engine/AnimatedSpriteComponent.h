#pragma once

#include "IComponent.h"
#include "ISprite.h"

#include <vector>

//Todo support spritesheets for performance
class AnimatedSpriteComponent : public IComponent
{
	int8_t animationIndex_;
	float msPerFrame_;
	float msSinceLastSpriteChange;
protected:
	//TODO this really shouldnt be a raw pointer
	GameObject* gameobject_;
	
	std::vector<std::shared_ptr<ISprite>> sprites_;

public:
	AnimatedSpriteComponent(std::vector<std::shared_ptr<ISprite>> sprites, float msPerFrame);

	void OnAdded(Engine& engine, GameObject& gameobject) override;
	void OnRemove(Engine& engine) override;
	void OnDraw(Engine& engine, float subframe, float deltaTime) override;

	GameObject& GetGameobject() override;

	// Inherited via IComponent
	virtual void OnUpdate(Engine& engine, float deltaTime) override;
};