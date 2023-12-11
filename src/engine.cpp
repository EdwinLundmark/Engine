#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include "load-shader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "renderingobject.hpp"
#include "engine.hpp"
#include <vector>

void Engine::startEngine()
{

	// Create and compile our GLSL program from the shaders
	GLuint shaderProgramID = LoadShaders("shaders/shader.vertexshader", "shaders/shader.fragmentshader");

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(shaderProgramID, "MVP");

	windowLoop(shaderProgramID, MatrixID);
	return;
}

void Engine::addRenderingObject(std::vector<float> vertexBufferData)
{
	RenderingObject object(vertexBufferData);
	m_renderingObjects.push_back(object);
}

void Engine::addRenderingObject(RenderingObject renderingObject)
{
	m_renderingObjects.push_back(renderingObject);
}

void GLAPIENTRY MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}


bool Engine::init()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Couldn't initialize GLFW.\n");
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	m_window = glfwCreateWindow(1024, 768, "Window title", NULL, NULL);
	if (m_window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	return true;
}

void Engine::windowLoop(GLuint shaderProgramID, GLuint MatrixID)
{
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	double lastTime = glfwGetTime();
	double deltaTime = 0;
	double xpos, ypos;

	do
	{
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgramID);

		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		glfwGetCursorPos(m_window, &xpos, &ypos);
		glfwSetCursorPos(m_window, m_width / 2, m_height / 2);

		m_camera.moveWASD(m_window, (float)deltaTime);
		m_camera.rotateFP((float)deltaTime, (float)xpos, (float)ypos);

		for (auto& object : m_renderingObjects)
		{
			object.drawObject(m_window, MatrixID, m_camera);
		}

		// Swap buffers
		glfwSwapBuffers(m_window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(m_window) == 0);

	return;
}