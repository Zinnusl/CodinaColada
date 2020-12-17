#pragma once

#include "GameObject.h"

void GameObject::OnUpdate(float deltaTime)
{
}

void GameObject::AddComponent(std::unique_ptr<IComponent> component)
{
}

void GameObject::RemoveComponent(std::unique_ptr<IComponent> component)
{
}