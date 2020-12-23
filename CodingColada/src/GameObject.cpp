#pragma once

#include "GameObject.h"

#include "Engine.h"

Engine* GameObject::engine_;

GameObject::GameObject()
{
}

GameObject::GameObject(Vector2 position)
	: position_(position)
{
	
}

void GameObject::OnUpdate(float deltaTime)
{
	for (auto& component : components_)
	{
		component->OnUpdate(*engine_, deltaTime);
	}
}

void GameObject::OnDraw()
{
	for (auto& component : components_)
	{
		component->OnDraw(*engine_);
	}
}

void GameObject::OnCollision(RigidbodyComponent& other)
{
}

Vector2 GameObject::GetPosition()
{
	return position_;
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
