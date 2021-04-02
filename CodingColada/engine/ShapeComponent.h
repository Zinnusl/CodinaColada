#pragma once

#include "IComponent.h"
#include "IShape.h"

#include <memory>

class ShapeComponent : public IComponent
{
protected:
	//TODO this really shouldnt be a raw pointer
	GameObject* gameobject_;
	std::shared_ptr<IShape> shape_;
	
public:
	ShapeComponent(std::unique_ptr<IShape> shape);

	std::shared_ptr<IShape> GetShape();

	void OnUpdate(Engine& engine, float deltaTime) override;
	void OnAdded(Engine& engine, GameObject& gameobject) override;
	void OnRemove(Engine& engine) override;
	void OnDraw(Engine& engine, float subframe, float deltaTime) override;
	GameObject& GetGameobject() override;
};