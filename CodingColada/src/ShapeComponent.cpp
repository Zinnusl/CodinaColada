#include "ShapeComponent.h"

#include "Engine.h"


ShapeComponent::ShapeComponent(std::unique_ptr<IShape> shape)
	: shape_(std::move(shape))
{
}

void ShapeComponent::OnUpdate(IEngine& engine, float deltaTime)
{
}

void ShapeComponent::OnRemove(IEngine& engine)
{
	
}

void ShapeComponent::OnDraw(IEngine& engine, float subframe)
{
	shape_->Draw(engine, *gameobject_, subframe);
}

GameObject& ShapeComponent::GetGameobject()
{
	return *gameobject_;
}

void ShapeComponent::OnAdded(IEngine& engine, GameObject& gameobject)
{
	gameobject_ = &gameobject;
}