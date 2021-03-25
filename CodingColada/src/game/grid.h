#pragma once 

#include "../GameObject.h"

class Grid : public GameObject
{

public:
	Grid()
	{
	}

	Grid()
	{
	}

	void OnUpdate(float deltaTime) override
	{
	
	}

	void OnDebugTreeNode() override
	{
		ImGui::Text("Grid");
	}
};