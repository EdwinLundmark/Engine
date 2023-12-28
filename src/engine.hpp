#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "renderingobject.hpp"
#include "load-shader.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include <vector>
#include <functional>

class Engine
{
public:
	bool init();
	void startEngine(std::function<void(Engine)> mainLoop);
	void addRenderingObject(RenderingObject renderingObject);
	
	Renderer renderer{};

	std::vector<RenderingObject> renderingObjects;
	
	int width = 1024;
	int height = 768;
	Camera camera{ 45.0f, width, height, 0.1f, 100.0f };
private:
	GLFWwindow* m_window;


	void windowLoop(std::function<void(Engine)> mainLoop);
};
