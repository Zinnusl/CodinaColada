#pragma once

#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(std::unique_ptr<ISprite> sprite)
	: sprite_(std::move(sprite))
{
}

std::shared_ptr<ISprite> SpriteComponent::GetSprite()
{
	return sprite_;
}

void SpriteComponent::OnUpdate(Engine& engine, float deltaTime)
{
}

void SpriteComponent::OnAdded(Engine& engine, GameObject& gameobject)
{
	gameobject_ = &gameobject;
}

void SpriteComponent::OnRemove(Engine& engine)
{
}

void SpriteComponent::OnDraw(Engine& engine, float subframe)
{
	sprite_->Draw(engine, *gameobject_, subframe);
}

GameObject& SpriteComponent::GetGameobject()
{
	return *gameobject_;
}