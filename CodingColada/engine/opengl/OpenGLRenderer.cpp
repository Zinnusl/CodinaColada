//This has to be included before glad, glm etc
#include "imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "OpenGLRenderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../GameObject.h"
#include "OpenGLShader.h"
#include "OpenGLRectangleShape.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

std::unordered_map<std::string, OpenGLShader> OpenGLRenderer::shaders_;
std::unordered_map<std::string, OpenGLTexture2D> OpenGLRenderer::textures_;


OpenGLRenderer::OpenGLRenderer()
	: window_(nullptr), projection_(glm::mat4(1.0))
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

OpenGLRenderer::~OpenGLRenderer()
{
	if (window_) 
	{
		glfwDestroyWindow(window_);
	}
	glfwTerminate();
}

void OpenGLRenderer::LoadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath)
{
	OpenGLShader shader = OpenGLShader::CompileFromFile(vertexShaderPath.c_str(), fragmentShaderPath.c_str(), nullptr);
	shader.SetMatrix4("projection", projection_, true);
	shaders_.emplace(std::make_pair(name, shader));
}

void OpenGLRenderer::LoadTexture(std::string name, std::string file, bool alpha)
{
	textures_.emplace(std::make_pair(name, OpenGLTexture2D::LoadTextureFromFile(file.c_str(), alpha)));
}

void* OpenGLRenderer::CreateWindow(int x, int y)
{
	glfwWindowHint(GLFW_RESIZABLE, true);

	int xPos, yPos, width, height;
	auto primaryMonitor = glfwGetPrimaryMonitor();
	glfwGetMonitorWorkarea(primaryMonitor, &xPos, &yPos, &width, &height);
	//window_ = glfwCreateWindow(x, y, "GLFWWindow", nullptr, nullptr);
	//window_ = glfwCreateWindow(width, height, "GLFWWindow", glfwGetPrimaryMonitor(), nullptr);
	window_ = glfwCreateWindow(width, height, "GLFWWindow", primaryMonitor, nullptr);

	//window_ = glfwCreateWindow(width, height, "GLFWWindow", glfwGetPrimaryMonitor(), nullptr);
	//glfwSetWindowMonitor(window_, nullptr, 0, 0, width, height, GLFW_DONT_CARE);

	glfwMakeContextCurrent(window_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("FATAL ERROR: Failed to initialize GLAD\n");
	}

	glViewport(0, 0, x, y);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSwapInterval(0); //disable vsync

	//setup imgui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window_, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

	//TODO iterate shaders and set projection
	projection_ = glm::ortho(0.0f, static_cast<float>(x), 0.0f, static_cast<float>(y), -1.f, 1.f);

	OpenGLShader defaultShader = OpenGLShader::CompileFromFile("..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.vert", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.frag", nullptr);
	defaultShader.SetMatrix4("projection", projection_, true);
	shaders_.emplace(std::make_pair("colada_shader_default", defaultShader));

	OpenGLShader spriteShader = OpenGLShader::CompileFromFile("..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\sprite.vert", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\sprite.frag", nullptr);
	spriteShader.SetMatrix4("projection", projection_, true);
	shaders_.emplace(std::make_pair("colada_shader_sprite", spriteShader));

	OpenGLRectangleShape::InitRenderData();

	return window_;
}

void OpenGLRenderer::BeginFrame()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	int width;
	int height;
	glfwGetWindowSize(window_, &width, &height);
	
	for (auto& shader : shaders_)
	{
		shader.second.Use();
		shader.second.SetFloat("time", glfwGetTime());
		shader.second.SetVector2f("screenresolution", glm::vec2(width, height));
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::Draw(GameObject& gameobject, float subframe)
{
	gameobject.OnDraw(subframe);
}

void OpenGLRenderer::EndFrame()
{
	//imgui Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window_, &display_w, &display_h);
	//glViewport(0, 0, display_w, display_h);
	//glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	//glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window_);
}

CodinaColadaWindow OpenGLRenderer::GetWindow()
{
	int display_w, display_h;
	glfwGetFramebufferSize(window_, &display_w, &display_h);
	return CodinaColadaWindow(Vector2(display_w, display_h));
}