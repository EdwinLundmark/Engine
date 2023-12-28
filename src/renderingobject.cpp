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

void RenderingObject::setPos(glm::vec3 position) 
{
	translation = glm::translate(glm::mat4(1.0f), position);
	return;
}