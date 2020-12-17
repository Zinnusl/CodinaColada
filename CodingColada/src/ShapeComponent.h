#pragma once

#include "IComponent.h"
#include "IShape.h"

class ShapeComponent : public IComponent
{
protected:
	IShape shape_;

public:
	void OnUpdate(float deltaTime) override;
	void OnAdded() override;
	void OnRemove() override;

	void SetShape(IShape shape);

};