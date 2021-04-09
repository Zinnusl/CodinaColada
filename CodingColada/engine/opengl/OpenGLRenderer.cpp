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
	: window_(nullptr), projection_(glm::mat4(1.0)), cameraPosition_(glm::vec2(0.0f, 0.0f)), zoom_(1.f)
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

//Loads a shader from .vert and .frag file
void OpenGLRenderer::LoadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath, std::function<void(OpenGLShader&)> onUseCallback)
{
	OpenGLShader shader = OpenGLShader::CompileFromFile(vertexShaderPath.c_str(), fragmentShaderPath.c_str(), nullptr, onUseCallback);
	shader.SetMatrix4("projection", projection_, true);
	shaders_.emplace(std::make_pair(name, shader));
}

void OpenGLRenderer::LoadTexture(std::string name, std::string file, bool alpha)
{
	textures_.emplace(std::make_pair(name, OpenGLTexture2D::LoadTextureFromFile(file.c_str(), alpha)));
}

//Defines how large the window is in pixels and how many EngineUnits (EU) that is
void* OpenGLRenderer::CreateWindow(int xResolution, int yResolution, int xEngineUnits, int yEngineUnits, bool fullscreen)
{
	engineUnitsOnOneScreen_ = glm::vec2(xEngineUnits, yEngineUnits);

	//TODO disabled resize, because it causes issues..
	glfwWindowHint(GLFW_RESIZABLE, false);

	int xPos, yPos, width, height;
	auto primaryMonitor = glfwGetPrimaryMonitor();
	glfwGetMonitorWorkarea(primaryMonitor, &xPos, &yPos, &width, &height);

	if (fullscreen)
	{
		window_ = glfwCreateWindow(xResolution, yResolution, "GLFWWindow", primaryMonitor, nullptr);
	}
	else
	{
		window_ = glfwCreateWindow(xResolution, yResolution, "GLFWWindow", nullptr, nullptr);
	}
	//TODO load image and set icon
	//GLFWimage image;
	//glfwSetWindowIcon(window_, 1, )

	glfwMakeContextCurrent(window_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("FATAL ERROR: Failed to initialize GLAD\n");
	}

	glViewport(0, 0, xResolution, yResolution);
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

	//TODO. The question here is: do I want the same things to be visible at any resolution? (probably). Therefore I woul need to hardcode the number.
	// 	   Or do I want to higher resolution to see more:
	//		projection_ = glm::ortho(0.0f, static_cast<float>(xResolution), 0.0f, static_cast<float>(yResolution), -1.f, 1.f);
	//The projection is used to normalize coordinates to the [-1, 1] range that OpenGL uses. This means that at any 16:9 ratio square will look like a square
	projection_ = glm::ortho(0.0f, static_cast<float>(xEngineUnits), 0.0f, static_cast<float>(yEngineUnits), -1.f, 1.f);

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
	//Start ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glfwGetWindowSize(window_, &width_, &height_);

	glm::mat4 camera(1.0f);

	//TODO Problem. We actually want to move the camera in world space. It seems the movement here is in [-1, 1] space. INVESTIGATE.
	camera = glm::scale(camera, glm::vec3(zoom_, zoom_, 1.0f));
	camera = glm::translate(camera, glm::vec3(cameraPosition_, 0.f));

	auto time = glfwGetTime();

	//Set common uniforms for all shaders
	for (auto& shader : shaders_)
	{
		shader.second.Use();
		shader.second.SetFloat("time", time);
		shader.second.SetVector2f("screenresolution", glm::vec2(width_, height_));
		shader.second.SetMatrix4("camera", camera);
	}
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::Draw(GameObject& gameobject, float subframe, float deltaTime)
{
	gameobject.OnDraw(subframe, deltaTime);
}

void OpenGLRenderer::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window_);
}

Vector2 OpenGLRenderer::GetResolution()
{
	int display_w, display_h;
	glfwGetFramebufferSize(window_, &display_w, &display_h);
	return Vector2(display_w, display_h);
}

Vector2 OpenGLRenderer::GetEUResolution()
{
	return Vector2(engineUnitsOnOneScreen_.x, engineUnitsOnOneScreen_.y);
}

Vector2 OpenGLRenderer::EuToPixel(Vector2 position)
{
	auto euResolution = GetEUResolution();
	auto resolution = GetResolution();
	return Vector2((resolution.GetX() / euResolution.GetX()) * position.GetX(), (resolution.GetY() / euResolution.GetY()) * position.GetY());
}

void OpenGLRenderer::SetCameraPosition(Vector2 position)
{
	cameraPosition_ = glm::vec2(position.GetX(), position.GetY());
}

Vector2 OpenGLRenderer::GetCameraPosition()
{
	return Vector2(cameraPosition_.x, cameraPosition_.y);
}

float OpenGLRenderer::GetZoom()
{
	return zoom_;
}

void OpenGLRenderer::SetZoom(float zoom)
{
	zoom_ = zoom;
}

Vector2 OpenGLRenderer::WorldToScreen(Vector2 worldPosition)
{
	Vector2 windowResolution = GetResolution();
	Vector2 worldPosDelta = worldPosition + Vector2(cameraPosition_.x, cameraPosition_.y);
	glm::vec2 scaling = glm::vec2(windowResolution.GetX() / engineUnitsOnOneScreen_.x, windowResolution.GetY()/ engineUnitsOnOneScreen_.y);
	Vector2 screenPos = Vector2(worldPosDelta.GetX() * scaling.x * zoom_, worldPosDelta.GetY() * scaling.y * zoom_);
	return screenPos;
}

//Takes a position on the screen and converts it to a world postion. One example would be to locate the mousePosition in the world
//Chanes to this will have to be reflected in the vertex shader.
Vector2 OpenGLRenderer::ScreenToWorld(Vector2 screenPosition)
{
	Vector2 windowResolution = GetResolution();

	//Calculate how many pixels one EngineUnit (EU) is
	glm::vec2 scaling = glm::vec2(engineUnitsOnOneScreen_.x / windowResolution.GetX(), engineUnitsOnOneScreen_.y / windowResolution.GetY());
	
	//Convert the screen position to world position
	Vector2 worldPosition = Vector2(screenPosition.GetX() * scaling.x / zoom_, screenPosition.GetY() * scaling.y / zoom_);
	
	//Account for the posion of the camera
	Vector2 worldPosDelta = worldPosition - Vector2(cameraPosition_.x, cameraPosition_.y);
	return Vector2(worldPosDelta.GetX() , worldPosDelta.GetY());
}