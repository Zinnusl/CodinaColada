#include "Tower.h"



Tower::Tower(Vector2 position)
	: GameObject(position)
{

}

void Tower::OnPhysicsUpdate(float deltaTime)
{
	GameObject::OnPhysicsUpdate(deltaTime);
}

void Tower::OnDebugTreeNode()
{
}