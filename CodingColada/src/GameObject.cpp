#pragma once

#include "GameObject.h"

#include "Engine.h"

Engine* GameObject::engine_;

GameObject::GameObject()
{
}

GameObject::GameObject(Vector2 position)
	: previousPosition_(position), currentPosition_(position)
{
	
}

void GameObject::OnPhysicsUpdate(float deltaTime)
{
	previousPosition_ = currentPosition_;
	for (auto& component : components_)
	{
		component->OnUpdate(*engine_, deltaTime);
	}
}

void GameObject::OnDraw(float subframe)
{
	for (auto& component : components_)
	{
		component->OnDraw(*engine_, subframe);
	}
}

void GameObject::OnCollision(RigidbodyComponent& other)
{
}

void GameObject::OnDebugTreeNode()
{
}

Vector2 GameObject::GetPreviousPosition()
{
	return previousPosition_;
}

Vector2 GameObject::GetPosition()
{
	return currentPosition_;
}

Vector2 GameObject::GetDrawPosition(float t)
{
	return Vector2::lerp(previousPosition_, currentPosition_, t);
}

void GameObject::SetPosition(Vector2 position)
{
	currentPosition_ = position;
}

void GameObject::AddComponent(std::unique_ptr<IComponent> component)
{
	//calling event OnAdded before pushing so unique_ptr component isnt empty
	component->OnAdded(*engine_, *this);
	components_.push_back(std::move(component));
}

void GameObject::RemoveComponent(IComponent& component)
{
	auto position = std::find_if(components_.begin(), components_.end(), [&](const std::unique_ptr<IComponent>& entry) { return entry.get() == &component; });
	if (position != components_.end())
	{
		component.OnRemove(*engine_);
		components_.erase(position);
	}
}
