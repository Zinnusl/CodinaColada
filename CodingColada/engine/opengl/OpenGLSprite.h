#pragma once

#include "OpenGLShader.h"
#include "OpenGLTexture2D.h"

#include "../ISprite.h"
#include "../Color.h"

#include <string>


class OpenGLSprite : public ISprite
{
public:
    OpenGLSprite() = delete;
    OpenGLSprite(glm::vec2 size, OpenGLShader& shader, OpenGLTexture2D& texture, Color color = Color(1, 1, 1, 1));
    ~OpenGLSprite();

private:
    OpenGLShader& shader_;
    OpenGLTexture2D& texture_;
    glm::vec2 size_;
    Color color_;
    unsigned int quadVAO_;

    void initRenderData();

    Color GetColor();
    void SetColor(Color color);
    void Draw(Engine& engine, GameObject& gameobject, float subframe, float deltaTime) override;
};