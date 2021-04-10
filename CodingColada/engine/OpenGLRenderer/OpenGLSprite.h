#pragma once

#include "OpenGLShader.h"
#include "OpenGLTexture2D.h"

<<<<<<< HEAD:CodingColada/engine/opengl/OpenGLSprite.h
#include "../ISprite.h"
#include "../Color.h"
=======
#include "../IShape.h"
>>>>>>> origin:CodingColada/engine/OpenGLRenderer/OpenGLSprite.h

class OpenGLSprite : public IShape
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
<<<<<<< HEAD:CodingColada/engine/opengl/OpenGLSprite.h

    Color GetColor();
    void SetColor(Color color);
    void Draw(Engine& engine, GameObject& gameobject, float subframe, float deltaTime) override;
=======
    void OnClick(Vector2 clickPosition) override
    {}
    void RegisterClickHandler(handlerCallbackType callback)
    {}
    void Draw(IEngine& engine, GameObject& gameobject, float subframe) override;
>>>>>>> origin:CodingColada/engine/OpenGLRenderer/OpenGLSprite.h
};