#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW\glfw3.h"

class Camera
{
public:
	float mouseSpeed = 0.5f;
	float moveSpeed = 1.7f;

	Camera(float FOV, int width, int height, float near, float far);

	void move(const glm::vec3& position);
	void moveTo(const glm::vec3& position);
	void moveWASD(GLFWwindow* window, float deltaTime);
	void rotateFP(float deltaTime, float xpos, float ypos, float width, float height);
	glm::mat4 getVPMatrix();

private:
	glm::mat4 m_projection;
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_right;
	glm::vec3 m_up;

	float m_pitch = 0.0f;
	float m_yaw = 3.14f;

	glm::mat4 m_view;

	void updateViewMatrix();
};