#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <GLFW\glfw3.h>
#include "renderingobject.hpp"
#include "camera.hpp"

class Renderer 
{
public:
	void renderObject(GLFWwindow* window, Camera& camera, RenderingObject& object);
};