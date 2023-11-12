#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>


class RenderingObject {
public:
	RenderingObject(std::vector<GLfloat> vertexBufferData);

	void drawObject(GLuint MatrixID, glm::mat4 Projection, double deltaTime, double xpos, double ypos);

private:
	std::vector<GLfloat> m_vertexBufferData;
	GLuint m_vbo;
	GLuint m_vba;
};