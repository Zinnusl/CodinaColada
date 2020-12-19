#pragma once

#include "IComponent.h"
#include "IShape.h"

#include <memory>

class ShapeComponent : public IComponent
{
protected:
	std::unique_ptr<IShape> shape_;
	//std::unique_ptr<IShape> tmpShape_;
	
public:
	ShapeComponent(std::unique_ptr<IShape> shape);

	void OnUpdate(Engine& engine, float deltaTime) override;
	void OnAdded(Engine& engine) override;
	void OnRemove(Engine& engine) override;
};