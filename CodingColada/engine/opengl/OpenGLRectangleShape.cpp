#include "OpenGLRectangleShape.h"

#include <iostream>
#include <string>

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLRenderer.h"
#include "OpenGLShader.h"
#include "../GameObject.h"
#include "../Engine.h"

unsigned int OpenGLRectangleShape::VAO;

OpenGLRectangleShape::OpenGLRectangleShape(Vector2 size, Color color)
	: RectangleShape(size, color), customShader_(nullptr)
{
}

OpenGLRectangleShape::OpenGLRectangleShape(Vector2 size, Color color, OpenGLShader* customShader)
	: RectangleShape(size, color), customShader_(customShader)
{
}

void OpenGLRectangleShape::Draw(Engine& engine, GameObject& gameobject, float subframe, float deltaTime)
{
	Vector2 drawPosition = gameobject.GetDrawPosition(subframe);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(gameobject.GetDrawPosition(subframe).GetX() + size_.GetX() / 2,
		gameobject.GetDrawPosition(subframe).GetY() + size_.GetY() / 2, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size_.GetX(), 0.5f * size_.GetY(), 0.0f));
	//model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size_.GetX(), -0.5f * size_.GetY(), 0.0f));
	model = glm::scale(model, glm::vec3(size_.GetX(), size_.GetY(), 1.0f));

	auto pixels = engine.GetRenderer().EuToPixel(size_);
	auto offset = engine.GetRenderer().EuToPixel(drawPosition);

	//TODO we throw away like 300fps with these 2 lines. Due to changing the shader for every object. Solving this requires redisign. 
	//We have to do batch rendering (first draw all using shader "rectangle", then all using "sprite" etc.)
	if (customShader_)
	{
		customShader_->Use();
		customShader_->SetVector4f("color", glm::vec4(color_.r_, color_.g_, color_.b_, color_.a_));
		customShader_->SetMatrix4("model", model);
		customShader_->SetVector2f("resolution", glm::vec2(pixels.GetX(), pixels.GetY()));
		customShader_->SetVector2f("offset", glm::vec2(offset.GetX(), offset.GetY()));
	}
	else
	{
		auto defaultShader = OpenGLRenderer::shaders_[std::string("colada_shader_default")];
		defaultShader.Use();

		defaultShader.SetVector4f("color", glm::vec4(color_.r_, color_.g_, color_.b_, color_.a_));
		defaultShader.SetMatrix4("model", model);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLRectangleShape::InitRenderData()
{	
	float vertices[] = {
		 -0.5f,  0.5f,  // top left  
		  0.5f,  0.5f,  // top right  
		-0.5f, -0.5f, // left  
		 0.5f, -0.5f, // right 
	};

	unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2,   // first triangle
	1, 3, 2    // second triangle
	};

	//vertex array object (also known as VAO) can be bound just like a vertex buffer object and any subsequent vertex attribute calls from that point on will be stored inside the VAO
	//so if we want to draw we just bind the vao
	//vertex buffer objects(VBO). Storex vertexs on GPU
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //tells opengl which buffer its working on
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copy data to bound buffer. TODO for moving objects GL_DYNAMIC_DRAW might be better..

	//Element Buffer Objects. Allows to specify which vertices are drawn (and reuse them). This way to draw a rectangel we only needs 4 verts instead of 6 (two triangles)
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Linking Vertex Attributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}