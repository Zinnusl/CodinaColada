#include "ShapeComponent.h"

#include "Engine.h"


ShapeComponent::ShapeComponent(std::unique_ptr<IShape> shape)
	: shape_(std::move(shape))
{
}

<<<<<<< HEAD:CodingColada/engine/ShapeComponent.cpp
std::shared_ptr<IShape> ShapeComponent::GetShape()
{
	return shape_;
}

void ShapeComponent::OnUpdate(Engine& engine, float deltaTime)
=======
void ShapeComponent::OnUpdate(IEngine& engine, float deltaTime)
>>>>>>> origin:CodingColada/src/ShapeComponent.cpp
{
}

void ShapeComponent::OnRemove(IEngine& engine)
{
	
}

<<<<<<< HEAD:CodingColada/engine/ShapeComponent.cpp
void ShapeComponent::OnDraw(Engine& engine, float subframe, float deltaTime)
=======
void ShapeComponent::OnDraw(IEngine& engine, float subframe)
>>>>>>> origin:CodingColada/src/ShapeComponent.cpp
{
	shape_->Draw(engine, *gameobject_, subframe, deltaTime);
}

GameObject& ShapeComponent::GetGameobject()
{
	return *gameobject_;
}

void ShapeComponent::OnAdded(IEngine& engine, GameObject& gameobject)
{
	gameobject_ = &gameobject;
}