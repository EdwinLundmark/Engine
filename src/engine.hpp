#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "renderingobject.hpp"
#include "camera.hpp"
#include <vector>

class Engine
{
public:
	bool init();
	void startEngine();
	void addRenderingObject(std::vector<GLfloat> vertexBufferData);
private:
	GLFWwindow* m_window;
	std::vector<RenderingObject> m_renderingObjects;
	int m_width = 1024;
	int m_height = 768;

	Camera m_camera{ 45.0f, m_width, m_height, 0.1f, 100.0f };

	void windowLoop(GLuint shaderProgramID, GLuint MatrixID);
};
