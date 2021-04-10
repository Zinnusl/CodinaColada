#pragma once

#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "Engine.h"

<<<<<<< HEAD:CodingColada/engine/GameObject.cpp
Engine* GameObject::engine_;
int64_t GameObject::nextGameObjectId_ = 0;

GameObject::GameObject()
	: id_(nextGameObjectId_++)
{
}

GameObject::GameObject(Vector2 position)
	: previousPosition_(position), currentPosition_(position), id_(nextGameObjectId_++)
=======
GameObject::GameObject(IEngine& engine)
	: engine_(engine)
{
}

GameObject::GameObject(IEngine& engine, Vector2 position)
	: engine_(engine), position_(position)
>>>>>>> origin:CodingColada/src/GameObject.cpp
{
}

void GameObject::OnStart()
{
}

//Called on every Physics tick. This allows to run expensive calculations frequently but not every frame.
void GameObject::OnPhysicsUpdate(float deltaTime)
{
	previousPosition_ = currentPosition_;
	for (auto& component : components_)
	{
		component->OnUpdate(engine_, deltaTime);
	}
}

void GameObject::OnDraw(float subframe, float deltaTime)
{
	for (auto& component : components_)
	{
<<<<<<< HEAD:CodingColada/engine/GameObject.cpp
		component->OnDraw(*engine_, subframe, deltaTime);
=======
		component->OnDraw(engine_, subframe);
>>>>>>> origin:CodingColada/src/GameObject.cpp
	}
}

void GameObject::OnCollision(RigidbodyComponent& other)
{
}

<<<<<<< HEAD:CodingColada/engine/GameObject.cpp
void GameObject::OnDebugTreeNode()
{
}

int64_t GameObject::GetId()
{
	return id_;
}

Vector2 GameObject::GetPreviousPosition()
{
	return previousPosition_;
}

=======
>>>>>>> origin:CodingColada/src/GameObject.cpp
Vector2 GameObject::GetPosition()
{
	return position_;
}

void GameObject::SetPosition(Vector2 position)
{
	currentPosition_ = position;
}

void GameObject::AddComponent(std::unique_ptr<IComponent> component)
{
	//calling event OnAdded before pushing so unique_ptr component isnt empty
	component->OnAdded(engine_, *this);
	components_.push_back(std::move(component));
}

void GameObject::RemoveComponent(IComponent& component)
{
	auto position = std::find_if(components_.begin(), components_.end(), [&](const std::unique_ptr<IComponent>& entry) { return entry.get() == &component; });
	if (position != components_.end())
	{
		component.OnRemove(engine_);
		components_.erase(position);
	}
}