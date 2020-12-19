#include "ShapeComponent.h"

#include "Engine.h"


ShapeComponent::ShapeComponent(std::unique_ptr<IShape> shape)
	: shape_(std::move(shape))
{
}

void ShapeComponent::OnUpdate(Engine& engine, float deltaTime)
{
}

void ShapeComponent::OnAdded(Engine& engine)
{
	engine.GetRenderer().AddShape(std::move(shape_));
}

void ShapeComponent::OnRemove(Engine& engine)
{

}