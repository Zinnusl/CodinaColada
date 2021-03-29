#include "Tower.h"

#include "../../../engine/Engine.h"
#include "../../../engine/SpriteComponent.h"
#include "../../../engine/RigidbodyComponent.h"
#include "../../../engine/opengl/OpenGLSprite.h"
#include "../../../engine/opengl/OpenGLRenderer.h"

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