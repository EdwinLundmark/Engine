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

	void setPos(glm::vec3 position);

private:
	std::vector<GLfloat> m_vertexBufferData;
	GLuint m_vbo;
	GLuint m_vba;
	glm::mat4 m_model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 m_translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
};