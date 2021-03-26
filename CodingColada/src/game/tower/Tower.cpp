#include "Tower.h"

#include "../../Engine.h"
#include "../../SpriteComponent.h"
#include "../../RigidbodyComponent.h"
#include "../../opengl/OpenGLSprite.h"
#include "../../opengl/OpenGLRenderer.h"

#include "imgui.h"

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
	ImGui::Text("Im a building in the Grid!");
}

void Tower::OnDraw(float subframe)
{
	GameObject::OnDraw(subframe);
}