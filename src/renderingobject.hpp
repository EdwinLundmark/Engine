#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"


class RenderingObject
{
public:
	RenderingObject(std::vector<GLfloat> vertexBufferData,GLuint shaderID);

	void setPos(glm::vec3 position);
	
	std::vector<GLfloat> vertexBufferData;
	GLuint vbo;
	GLuint vao;
	GLuint shaderID;
	GLuint matrixUniform;

	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

};