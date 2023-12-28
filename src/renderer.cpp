#define GLEW_STATIC
#include <glew.h>
#include "renderer.hpp"
#include <GLFW/glfw3.h>
#include "renderingobject.hpp"
#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Renderer::renderObject(GLFWwindow* window, Camera& camera, RenderingObject& object)
{
	glUseProgram(object.shaderID);
	
	glm::mat4 vp = camera.getVPMatrix();

	glm::mat4 mvp = vp * object.translation * object.model; // Remember, matrix multiplication is the other way around

	glBindVertexArray(object.vao);
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


	glUniformMatrix4fv(object.matrixUniform, 1, GL_FALSE, &mvp[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, (int)(object.vertexBufferData.size() / 3)); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}