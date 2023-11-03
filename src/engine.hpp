#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Engine {
public:
	void startEngine();
private:
	GLFWwindow* window;

	bool initWindow();
	void windowLoop(GLuint programID, GLuint vertexbuffer, GLuint MatrixID, glm::mat4 mvp);
};
