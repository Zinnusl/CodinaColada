#pragma once

#include "IComponent.h"
#include "IShape.h"

class SpriteComponent :public IComponent
{
protected:
	//TODO this really shouldnt be a raw pointer
	GameObject* gameobject_;

<<<<<<< HEAD:CodingColada/engine/SpriteComponent.h
	std::shared_ptr<ISprite> sprite_;
=======
	std::shared_ptr<IShape> sprite_;

>>>>>>> origin:CodingColada/src/SpriteComponent.h
public:
	SpriteComponent(std::unique_ptr<IShape> sprite);

<<<<<<< HEAD:CodingColada/engine/SpriteComponent.h
	std::shared_ptr<ISprite> GetSprite();

	void OnUpdate(Engine& engine, float deltaTime) override;
	void OnAdded(Engine& engine, GameObject& gameobject) override;
	void OnRemove(Engine& engine) override;
	void OnDraw(Engine& engine, float subframe, float deltaTime) override;

=======
	void OnUpdate(IEngine& engine, float deltaTime) override;
	void OnAdded(IEngine& engine, GameObject& gameobject) override;
	void OnRemove(IEngine& engine) override;
	void OnDraw(IEngine& engine, float subframe) override;
>>>>>>> origin:CodingColada/src/SpriteComponent.h
	GameObject& GetGameobject() override;
};