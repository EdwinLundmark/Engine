#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "renderingobject.hpp"
#include <vector>

class Engine {
public:
	bool init();
	void startEngine();
	void addRenderingObject(std::vector<GLfloat> vertexBufferData);
private:
	GLFWwindow* m_window;
	std::vector<RenderingObject> m_renderingObjects;

	void windowLoop(GLuint shaderProgramID, GLuint MatrixID, glm::mat4 mvp);
};
