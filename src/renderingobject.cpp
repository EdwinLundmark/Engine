#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include "renderingobject.hpp"
#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

RenderingObject::RenderingObject(std::vector<GLfloat> vertexBufferData, GLuint shaderID)
    : vertexBufferData(vertexBufferData), shaderID(shaderID), vbo(), vao()
{
    
	matrixUniform = glGetUniformLocation(shaderID, "MVP");

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexBufferData.size(), &vertexBufferData.front(), GL_STATIC_DRAW);
}

void RenderingObject::setPos(float x, float y, float z)
{
	translation = glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z));
	return;
}

void RenderingObject::setScale(float x, float y, float z)
{
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
	return;
}



void RenderingObject::setRot(float angle, Axis axis)
{
	glm::vec3 axisVec;
	switch (axis) 
	{
	case X:
		axisVec = glm::vec3(1, 0, 0);
		break;
	case Y:
		axisVec = glm::vec3(0, 1, 0);
		break;
	case Z:
		axisVec = glm::vec3(0, 0, 1);
		break;
	}

	rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axisVec);
	return;
}