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

	void OnUpdate(IEngine& engine, float deltaTime) override;
	void OnAdded(IEngine& engine, GameObject& gameobject) override;
	void OnRemove(IEngine& engine) override;
	void OnDraw(IEngine& engine, float subframe) override;
	GameObject& GetGameobject() override;
};