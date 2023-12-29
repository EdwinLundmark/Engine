#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"

enum Axis
{
	X,
	Y,
	Z
};

class RenderingObject
{
public:
	RenderingObject(std::vector<GLfloat> vertexBufferData,GLuint shaderID);

	void setScale(float x, float y, float z);
	void setRot(float angle, Axis axis);
	void setPos(float x, float y, float z);
	
	std::vector<GLfloat> vertexBufferData;
	GLuint vbo;
	GLuint vao;
	GLuint shaderID;
	GLuint matrixUniform;

	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);

};