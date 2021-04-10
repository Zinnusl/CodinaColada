#pragma once

#include <string>
#include <functional>
#include <glm/glm.hpp>

class OpenGLShader
{
public:
    // state
    unsigned int ID;

    std::function<void(OpenGLShader&)> OnUseCallback_;
    // constructor
    OpenGLShader() { }
    // sets the current shader as active
    OpenGLShader& Use();
    // compiles the shader from given source code
    static OpenGLShader CompileFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::function<void(OpenGLShader&)> onUseCallback = {});
    void    Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); // note: geometry source code is optional 
    // utility functions
    void    SetFloat(const char* name, float value, bool useShader = false);
    void    SetInteger(const char* name, int value, bool useShader = false);
    void    SetVector2f(const char* name, float x, float y, bool useShader = false);
    void    SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);
    void    SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
    void    SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
    void    SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
    void    SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);
    void    SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);

private:
    // checks if compilation or linking failed and if so, print the error logs
    void    checkCompileErrors(unsigned int object, std::string type) const;
};