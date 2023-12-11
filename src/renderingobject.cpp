#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include "renderingobject.hpp"
#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <typeinfo>
#include <iostream>

RenderingObject::RenderingObject(std::vector<GLfloat> vertexBufferData)
    : m_vertexBufferData(vertexBufferData), m_vbo(), m_vba()
{
    
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vba);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertexBufferData.size(), &m_vertexBufferData.front(), GL_STATIC_DRAW);
}

void RenderingObject::drawObject(GLFWwindow* window, GLuint MatrixID, Camera& camera)
{

	// Model matrix : an identity matrix (model will be at the origin)

	glm::mat4 vp = camera.getVPMatrix();

	glm::mat4 mvp = vp * m_translation * m_model; // Remember, matrix multiplication is the other way around

	glBindVertexArray(m_vba);
    // Give our vertices to OpenGL.

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);


	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, (int)(m_vertexBufferData.size() / 3)); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void RenderingObject::setPos(glm::vec3 position) {
	m_translation = glm::translate(glm::mat4(1.0f), position);
	return;
}