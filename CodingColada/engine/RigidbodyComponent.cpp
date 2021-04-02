#include "RigidbodyComponent.h"

#include "GameObject.h"


RigidbodyComponent::RigidbodyComponent(Vector2 size)
    : size_(size)
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

GameObject& RigidbodyComponent::GetGameobject()
{
	return *gameobject_;
}

bool RigidbodyComponent::CheckCollision(RigidbodyComponent& other)
{
    // collision x-axis?
    bool collisionX = gameobject_->GetPosition().GetX() + size_.GetX() >= other.gameobject_->GetPosition().GetX() &&
        other.gameobject_->GetPosition().GetX() + other.size_.GetX() >= gameobject_->GetPosition().GetX();
    // collision y-axis?
    bool collisionY = gameobject_->GetPosition().GetY() + size_.GetY() >= other.gameobject_->GetPosition().GetY() &&
        other.gameobject_->GetPosition().GetY() + other.size_.GetY() >= gameobject_->GetPosition().GetY();
    // collision only if on both axes
    return collisionX && collisionY;
}

void RigidbodyComponent::OnDraw(Engine& engine, float subframe, float deltaTime)
{
}