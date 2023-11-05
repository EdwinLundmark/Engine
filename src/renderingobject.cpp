#define GLEW_STATIC
#include <glew.h>
#include "renderingobject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <typeinfo>
#include <iostream>

RenderingObject::RenderingObject(std::vector<GLfloat> vertexBufferData)
    : m_vertexBufferData(vertexBufferData), m_vertexbuffer() {
    
	std::cout << typeid(m_vertexBufferData).name() << std::endl;

	glGenBuffers(1, &m_vertexbuffer);
	printf("glGenBuffers %d\n", glGetError());

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	printf("glBindBuffer %d\n", glGetError());

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertexBufferData.size(), &m_vertexBufferData.front(), GL_STATIC_DRAW);
	printf("glBufferData %d\n", glGetError());
}

void RenderingObject::drawObject(GLuint MatrixID, glm::mat4 mvp) {
	// 1st attribute buffer : vertices
	printf("start\n");
	glEnableVertexAttribArray(0);
	printf("%d\n", glGetError());
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	printf("%d\n", glGetError());
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	printf("%d\n", glGetError());

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	printf("%d\n", glGetError());

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, (int)(m_vertexBufferData.size() / 3)); // Starting from vertex 0; 3 vertices total -> 1 triangle
	printf("%d\n", glGetError());

	glDisableVertexAttribArray(0);
	printf("%d\n", glGetError());

}