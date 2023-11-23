#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW\glfw3.h"

// TODO: set default values, add pitch and yaw maybe
Camera::Camera(float FOV, int width, int height, float near, float far) {
	m_position = glm::vec3(0.0f,-2.0f,0.0f);
	m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	m_right = glm::vec3(1.0f, 0.0f, 0.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_view = glm::mat4(1.0f);
	
	m_projection = glm::perspective(glm::radians(FOV), (float)width / (float)height, near, far);
	updateViewMatrix();
}

void Camera::updateViewMatrix() {
	m_direction = glm::vec3(
		cos(m_pitch) * sin(m_yaw),
		sin(m_pitch),
		cos(m_pitch) * cos(m_yaw)
	);

	m_right = glm::vec3(
		sin(m_yaw - 3.14f / 2.0f),
		0,
		cos(m_yaw - 3.14f / 2.0f)
	);

	m_up = glm::cross(m_right, m_direction);


	m_view = glm::lookAt(
		m_position,           // Camera is here
		m_position + m_direction, // and looks here : at the same position, plus "direction"
		m_up
	);
}

void Camera::move(const glm::vec3& position) {
	m_position = position;
	updateViewMatrix();
	return;
}

void Camera::moveTo(const glm::vec3& position) {
	m_position += position;
	updateViewMatrix();
	return;
}

void Camera::rotateFP(float deltaTime, float xpos, float ypos) {
	m_pitch += mouseSpeed * deltaTime * (768.0f / 2.0f - ypos);
	m_yaw += mouseSpeed * deltaTime * (1024.0f / 2.0f - xpos);

	updateViewMatrix();

	return;
}

void Camera::moveWASD(GLFWwindow* window, float deltaTime) {
	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		m_position += m_direction * deltaTime * moveSpeed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		m_position -= m_direction * deltaTime * moveSpeed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		m_position += m_right * deltaTime * moveSpeed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		m_position -= m_right * deltaTime * moveSpeed;
	}

	updateViewMatrix();
	return;
}


glm::mat4 Camera::getVPMatrix() {
	return m_view;
}
