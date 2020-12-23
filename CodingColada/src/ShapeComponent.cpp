#include "ShapeComponent.h"

#include "Engine.h"


ShapeComponent::ShapeComponent(std::unique_ptr<IShape> shape)
	: shape_(std::move(shape))
{
}

void ShapeComponent::OnUpdate(Engine& engine, float deltaTime)
{
}

void ShapeComponent::OnRemove(Engine& engine)
{
	
}

void ShapeComponent::OnDraw(Engine& engine)
{
	shape_->Draw(engine, *gameobject_);
}

GameObject& ShapeComponent::GetGameobject()
{
	return *gameobject_;
}

void ShapeComponent::OnAdded(Engine& engine, GameObject& gameobject)
{
	gameobject_ = &gameobject;
}
