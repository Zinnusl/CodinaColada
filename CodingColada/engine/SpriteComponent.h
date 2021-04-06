#pragma once

#include "IComponent.h"
#include "ISprite.h"

class SpriteComponent :public IComponent
{
protected:
	//TODO this really shouldnt be a raw pointer
	GameObject* gameobject_;

	std::shared_ptr<ISprite> sprite_;
public:
	SpriteComponent(std::unique_ptr<ISprite> sprite);

	std::shared_ptr<ISprite> GetSprite();

	void OnUpdate(Engine& engine, float deltaTime) override;
	void OnAdded(Engine& engine, GameObject& gameobject) override;
	void OnRemove(Engine& engine) override;
	void OnDraw(Engine& engine, float subframe, float deltaTime) override;

	GameObject& GetGameobject() override;
};