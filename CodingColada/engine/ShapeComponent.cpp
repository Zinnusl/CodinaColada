#include "ShapeComponent.h"

#include "Engine.h"


ShapeComponent::ShapeComponent(std::unique_ptr<IShape> shape)
	: shape_(std::move(shape))
{
}

std::shared_ptr<IShape> ShapeComponent::GetShape()
{
	return shape_;
}

void ShapeComponent::OnUpdate(Engine& engine, float deltaTime)
{
}

void ShapeComponent::OnRemove(Engine& engine)
{
	
}

void ShapeComponent::OnDraw(Engine& engine, float subframe, float deltaTime)
{
	shape_->Draw(engine, *gameobject_, subframe, deltaTime);
}

GameObject& ShapeComponent::GetGameobject()
{
	return *gameobject_;
}

void ShapeComponent::OnAdded(Engine& engine, GameObject& gameobject)
{
	gameobject_ = &gameobject;
}