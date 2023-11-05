#include "engine.hpp"
#include <vector>

int main() {
	Engine engine{};

	if(!engine.init()) return 0;

	std::vector<float> triangle_data = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	engine.addRenderingObject(triangle_data);

	engine.startEngine();

	
	return 0;
}