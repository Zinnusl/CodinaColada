#include "AnimatedSpriteComponent.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(std::vector<std::shared_ptr<ISprite>> sprites, float msPerFrame)
	: sprites_(sprites), msPerFrame_(msPerFrame), animationIndex_(0), msSinceLastSpriteChange(0), gameobject_(nullptr)
{
}

void AnimatedSpriteComponent::OnAdded(Engine& engine, GameObject& gameobject)
{
	gameobject_ = &gameobject;
}

void AnimatedSpriteComponent::OnRemove(Engine& engine)
{
}

void AnimatedSpriteComponent::OnDraw(Engine& engine, float subframe, float deltaTime)
{
	msSinceLastSpriteChange += deltaTime;
	if (msSinceLastSpriteChange >= msPerFrame_)
	{
		animationIndex_ = (animationIndex_ + 1) % (sprites_.size());
		msSinceLastSpriteChange = 0;
	}
	sprites_[animationIndex_]->Draw(engine, *gameobject_, subframe, deltaTime);
}

GameObject& AnimatedSpriteComponent::GetGameobject()
{
	return *gameobject_;
}

void AnimatedSpriteComponent::OnUpdate(Engine& engine, float deltaTime)
{
}
