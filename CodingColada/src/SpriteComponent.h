#pragma once

#include "IComponent.h"
#include "IShape.h"

class SpriteComponent :public IComponent
{
protected:
	//TODO this really shouldnt be a raw pointer
	GameObject* gameobject_;

	std::shared_ptr<IShape> sprite_;

public:
	SpriteComponent(std::unique_ptr<IShape> sprite);

	void OnUpdate(IEngine& engine, float deltaTime) override;
	void OnAdded(IEngine& engine, GameObject& gameobject) override;
	void OnRemove(IEngine& engine) override;
	void OnDraw(IEngine& engine, float subframe) override;
	GameObject& GetGameobject() override;
};