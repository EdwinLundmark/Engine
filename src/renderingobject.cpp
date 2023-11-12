#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include "renderingobject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <typeinfo>
#include <iostream>

RenderingObject::RenderingObject(std::vector<GLfloat> vertexBufferData)
    : m_vertexBufferData(vertexBufferData), m_vbo(), m_vba() {
    
	glGenBuffers(1, &m_vbo);

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glGenVertexArrays(1, &m_vba);
	glBindVertexArray(m_vba);


    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertexBufferData.size(), &m_vertexBufferData.front(), GL_STATIC_DRAW);
}

void RenderingObject::drawObject(GLuint MatrixID, glm::mat4 Projection, double deltaTime, double xpos, double ypos) {

	float speed = 3.0f; // 3 units / second
	double mouseSpeed = 0.1;
	static glm::vec3 position = glm::vec3(0, 2, 5);
	// horizontal angle : toward -Z
	static double horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	static double verticalAngle = 0.0f;

	

	horizontalAngle += mouseSpeed * deltaTime * double(1024.0 / 2.0 - xpos);
	verticalAngle += mouseSpeed * deltaTime * double(768.0 / 2.0 - ypos);

	printf("%f, %f, %f, (%f, %f)\n", horizontalAngle, verticalAngle, deltaTime, xpos, ypos);

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);



	glm::mat4 View = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up
	);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);

	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around


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

}