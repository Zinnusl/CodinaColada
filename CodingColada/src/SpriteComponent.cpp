#pragma once

#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(std::unique_ptr<ISprite> sprite)
	: sprite_(std::move(sprite))
{
}

void SpriteComponent::OnUpdate(IEngine& engine, float deltaTime)
{
}

void SpriteComponent::OnAdded(IEngine& engine, GameObject& gameobject)
{
	gameobject_ = &gameobject;
}

void SpriteComponent::OnRemove(IEngine& engine)
{
}

void SpriteComponent::OnDraw(IEngine& engine, float subframe)
{
	sprite_->Draw(engine, *gameobject_, subframe);
}

GameObject& SpriteComponent::GetGameobject()
{
	return *gameobject_;
}