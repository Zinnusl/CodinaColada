#pragma once

#include "OpenGLShader.h"
#include "OpenGLTexture2D.h"

#include "../IShape.h"

class OpenGLSprite : public IShape
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
    void OnClick(Vector2 clickPosition) override
    {}
    void RegisterClickHandler(handlerCallbackType callback)
    {}
    void Draw(IEngine& engine, GameObject& gameobject, float subframe) override;
};