#include "RigidbodyComponent.h"
#include "GameObject.h"


RigidbodyComponent::RigidbodyComponent(Vector2 size)
	: offset_(Vector2(0)), size_(size), gameobject_(nullptr)
{
}

void RigidbodyComponent::OnUpdate(IEngine& engine, float deltaTime)
{
 
}

void RigidbodyComponent::OnAdded(IEngine& engine, GameObject& gameobject)
{
    gameobject_ = &gameobject;
}

void RigidbodyComponent::OnRemove(IEngine& engine)
{
}

void RigidbodyComponent::OnDraw(IEngine& engine, float subframe)
{
}

GameObject& RigidbodyComponent::GetGameobject()
{
	return *gameobject_;
}

bool RigidbodyComponent::CollidesWith(RigidbodyComponent& other)
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
