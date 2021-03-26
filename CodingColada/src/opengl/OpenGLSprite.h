#pragma once

#include "OpenGLShader.h"
#include "OpenGLTexture2D.h"

#include "../ISprite.h"

#include <string>


class OpenGLSprite : public ISprite
{
public:
    OpenGLSprite() = delete;
    OpenGLSprite(OpenGLShader& shader, OpenGLTexture2D& texture);
    ~OpenGLSprite();

private:
    OpenGLShader& shader_;
    OpenGLTexture2D& texture_;
    unsigned int quadVAO_;

    void initRenderData();

    void Draw(Engine& engine, GameObject& gameobject, float subframe) override;
};