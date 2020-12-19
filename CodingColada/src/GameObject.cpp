#pragma once

#include "GameObject.h"

#include "Engine.h"

Engine* GameObject::engine_;

GameObject::GameObject()
{
}

void GameObject::OnUpdate(float deltaTime)
{
}

void GameObject::AddComponent(std::unique_ptr<IComponent> component)
{
	//calling event before pushing so unique_ptr isnt empty
	component->OnAdded(*engine_);
	components_.push_back(std::move(component));
}

void GameObject::RemoveComponent(std::unique_ptr<IComponent> component)
{
	auto position = std::find(components_.begin(), components_.end(), component);
	if (position != components_.end())
	{
		components_.erase(position);
	}
}