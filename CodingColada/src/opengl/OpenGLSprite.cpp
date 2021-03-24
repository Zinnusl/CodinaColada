#include "OpenGLSprite.h"

#include "../GameObject.h"

#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

void OpenGLSprite::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO_);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenGLSprite::Draw(Engine& engine, GameObject& gameobject, float subframe)
{
    //TODO conversion between engine Vector2 and glm::vector annoying. Solution?
    //TODO pass values from sprite? Gameobject?
    glm::vec2 position = glm::vec2(gameobject.GetDrawPosition(subframe).GetX(), gameobject.GetDrawPosition(subframe).GetY());
    glm::vec2 size(64, 64);
    glm::vec4 color(1, 1, 1, 1);
    float rotate = 180;
    

    // prepare transformations
    this->shader_.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader_.SetMatrix4("model", model);
    this->shader_.SetVector4f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture_.Bind();

    glBindVertexArray(this->quadVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

OpenGLSprite::OpenGLSprite(OpenGLShader& shader, OpenGLTexture2D& texture)
    : shader_(shader), texture_(texture)
{
    this->initRenderData();
}

OpenGLSprite::~OpenGLSprite()
{
}