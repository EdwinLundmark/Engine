#include "engine.hpp"
#include <vector>

void mainLoop(Engine& e) {
    e.camera.moveWASD(e.window, e.deltaTime);
    e.camera.rotateFP(e.deltaTime, e.xpos, e.ypos, e.width, e.height);

    for (auto& object : e.renderingObjects)
    {
        e.renderer.renderObject(e.window, e.camera, object);
    }

    return;
}

int main()
{
	Engine engine{};

	if(!engine.init()) return 1;

    GLuint shaderProgramID = LoadShaders("shaders/shader.vertexshader", "shaders/shader.fragmentshader");

    std::vector<float> cubeData = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    RenderingObject cube{ cubeData, shaderProgramID };
    RenderingObject cube2{ cubeData, shaderProgramID };

    cube.setPos(-1.0f, 0.0f, 0.0f);
    cube2.setPos(1.0f, 0.0f, 0.0f);

    cube.setRot(-45, X);

	engine.addRenderingObject(cube);
	engine.addRenderingObject(cube2);

	engine.startEngine(mainLoop);

	return 0;
}