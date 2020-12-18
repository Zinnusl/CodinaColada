#pragma once

#include "GameObject.h"

GameObject::GameObject(Engine& engine)
	: engine_(engine)
{
}

void GameObject::OnUpdate(Engine& engine, float deltaTime)
{
}

void GameObject::AddComponent(std::unique_ptr<IComponent> component)
{
	components_.push_back(std::move(component));
	//component->OnAdded()
}

void GameObject::RemoveComponent(std::unique_ptr<IComponent> component)
{
	auto position = std::find(components_.begin(), components_.end(), component);
	if (position != components_.end())
	{
		components_.erase(position);
	}
}