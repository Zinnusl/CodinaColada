#pragma once 

#include "PathTile.h"

PathTile::PathTile(Vector2 position)
	: GameObject(position)
{

}

void PathTile::OnDraw(float subframe, float deltaTime)
{
	GameObject::OnDraw(subframe, deltaTime);
}