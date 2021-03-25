#include "RigidbodyComponent.h"
#include "GameObject.h"


RigidbodyComponent::RigidbodyComponent(std::unique_ptr<RectangleShape> shape)
    : shape_(std::move(shape))
{
}

void RigidbodyComponent::OnUpdate(Engine& engine, float deltaTime)
{
 
}

void RigidbodyComponent::OnAdded(Engine& engine, GameObject& gameobject)
{
    gameobject_ = &gameobject;
}

void RigidbodyComponent::OnRemove(Engine& engine)
{
}

void RigidbodyComponent::OnDraw(Engine& engine, float subframe)
{
    shape_->Draw(engine, *gameobject_, subframe);
}

GameObject& RigidbodyComponent::GetGameobject()
{
	return *gameobject_;
}

bool RigidbodyComponent::CheckCollision(RigidbodyComponent& other)
{
    // collision x-axis?
    bool collisionX = gameobject_->GetPosition().GetX() + shape_->GetSize().GetX() >= other.gameobject_->GetPosition().GetX() &&
        other.gameobject_->GetPosition().GetX() + other.shape_->GetSize().GetX() >= gameobject_->GetPosition().GetX();
    // collision y-axis?
    bool collisionY = gameobject_->GetPosition().GetY() + shape_->GetSize().GetY() >= other.gameobject_->GetPosition().GetY() &&
        other.gameobject_->GetPosition().GetY() + other.shape_->GetSize().GetY() >= gameobject_->GetPosition().GetY();
    // collision only if on both axes
    return collisionX && collisionY;
}