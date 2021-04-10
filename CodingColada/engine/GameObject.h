#pragma once

#include "Vector2.h"

#include "IComponent.h"
#include "IEngine.h"
#include "RigidbodyComponent.h"

#include <vector>
#include <memory>
#include <cstdint>

<<<<<<< HEAD:CodingColada/engine/GameObject.h
class Engine;
class RigidbodyComponent;

/**
* When overriding any of the functions you need to call GameObject::OverridenFunction in your override!
**/
class GameObject : std::enable_shared_from_this<GameObject>
{
	int64_t id_;
	Vector2 previousPosition_;

	static int64_t nextGameObjectId_;

protected:
	Vector2 currentPosition_;
=======
class GameObject
{
protected:
	IEngine& engine_;
	Vector2 position_;
>>>>>>> origin:CodingColada/src/GameObject.h
	Vector2 rotation_;

	std::vector<std::unique_ptr<IComponent>> components_;

public:
<<<<<<< HEAD:CodingColada/engine/GameObject.h
	GameObject();
	GameObject(Vector2 position);
	static Engine* engine_;
			
	int64_t GetId();
=======
	GameObject(IEngine& engine);
	GameObject(IEngine& engine, Vector2 position);

	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(float subframe);
	virtual void OnCollision(RigidbodyComponent& other); // WTF GameObject <> RigidbodyComponent sollten nicht interagieren... (besser zu collisiion subscriben)
	
>>>>>>> origin:CodingColada/src/GameObject.h
	Vector2 GetPreviousPosition();
	Vector2 GetPosition();
	Vector2 GetDrawPosition(float t);

	void SetPosition(Vector2 position);

	void AddComponent(std::unique_ptr <IComponent> component);
	void RemoveComponent(IComponent& component);
<<<<<<< HEAD:CodingColada/engine/GameObject.h

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


	// Callbacks

	//Called when gameobject is added to engine
	virtual void OnStart();

	//Runs on every physics step
	//Don't capture input here
	virtual void OnPhysicsUpdate(float deltaTime);

	//Draws all IComponent components of the gameobject 
	virtual void OnDraw(float subframe, float deltaTime);

	virtual void OnCollision(RigidbodyComponent& other);
	virtual void OnDebugTreeNode();
};
=======
};
>>>>>>> origin:CodingColada/src/GameObject.h
