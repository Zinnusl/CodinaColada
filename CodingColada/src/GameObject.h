#pragma once

#include "Vector2.h"

#include "IComponent.h"
#include "IEngine.h"

#include <vector>
#include <memory>

class GameObject
{
protected:
	IEngine& engine_;
	Vector2 position_;
	Vector2 rotation_;

	std::vector<std::unique_ptr<IComponent>> components_;

public:
	GameObject(IEngine& engine);
	virtual void OnUpdate(IEngine& engine, float deltaTime);
	GameObject();
	GameObject(Vector2 position);
	static Engine* engine_;
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(float subframe);
	virtual void OnCollision(RigidbodyComponent& other);
	
	Vector2 GetPreviousPosition();
	Vector2 GetPosition();
	Vector2 GetDrawPosition(float t);

	void AddComponent(std::unique_ptr <IComponent> component);
	void RemoveComponent(IComponent& component);

	//templates have to be defined in header
	template<class T>
	T* GetFirstComponentOfType()
	{
		auto it = std::find_if(components_.begin(), components_.end(), [](auto& comp) {
			return dynamic_cast<T*>(comp.get());
		});
		if (it != components_.end()) {
			return static_cast<T*>(it->get());
		}
		else {
			return nullptr;
		}
	}
};
