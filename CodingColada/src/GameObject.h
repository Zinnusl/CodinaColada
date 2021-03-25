#pragma once

#include "Vector2.h"

#include "IComponent.h"

#include <vector>
#include <memory>

class Engine;
class RigidbodyComponent;
class GameObject
{
protected:
	Vector2 previousPosition_;
	Vector2 currentPosition_;
	Vector2 rotation_;

	std::vector<std::unique_ptr<IComponent>> components_;

public:
	GameObject();
	GameObject(Vector2 position);
	static Engine* engine_;
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(float subframe);
	virtual void OnCollision(RigidbodyComponent& other);
	virtual void OnDebugTreeNode();
	
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
