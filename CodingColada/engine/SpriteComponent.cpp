#pragma once

#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(std::unique_ptr<IShape> sprite)
	: sprite_(std::move(sprite)), gameobject_(nullptr)
{
}

<<<<<<< HEAD:CodingColada/engine/SpriteComponent.cpp
std::shared_ptr<ISprite> SpriteComponent::GetSprite()
{
	return sprite_;
}

void SpriteComponent::OnUpdate(Engine& engine, float deltaTime)
=======
void SpriteComponent::OnUpdate(IEngine& engine, float deltaTime)
>>>>>>> origin:CodingColada/src/SpriteComponent.cpp
{
}

void SpriteComponent::OnAdded(IEngine& engine, GameObject& gameobject)
{
	gameobject_ = &gameobject;
}

void SpriteComponent::OnRemove(IEngine& engine)
{
}

<<<<<<< HEAD:CodingColada/engine/SpriteComponent.cpp
void SpriteComponent::OnDraw(Engine& engine, float subframe, float deltaTime)
=======
void SpriteComponent::OnDraw(IEngine& engine, float subframe)
>>>>>>> origin:CodingColada/src/SpriteComponent.cpp
{
	sprite_->Draw(engine, *gameobject_, subframe, deltaTime);
}

GameObject& SpriteComponent::GetGameobject()
{
	return *gameobject_;
}