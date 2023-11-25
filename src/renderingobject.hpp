#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"


class RenderingObject
{
public:
	RenderingObject(std::vector<GLfloat> vertexBufferData);

	void drawObject(GLFWwindow* window, GLuint MatrixID, Camera& camera);

private:
	std::vector<GLfloat> m_vertexBufferData;
	GLuint m_vbo;
	GLuint m_vba;
};