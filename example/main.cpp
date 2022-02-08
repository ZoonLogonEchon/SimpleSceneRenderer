#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <chrono>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <SceneRenderer/renderer.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Renderer* renderer;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		renderer->updateCameraPos(glm::vec3(0.0f, 2.0f, 0.0f));
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		renderer->updateCameraPos(glm::vec3(0.0f, -2.0f, 0.0f));
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		renderer->updateCameraPos(glm::vec3(2.0f, 0.0f, 0.0f));
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		renderer->updateCameraPos(glm::vec3(-2.0f, 0.0f, 0.0f));
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		renderer->updateCameraPos(glm::vec3(0.0f, 0.0f, 2.0f));
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		renderer->updateCameraPos(glm::vec3(0.0f, 0.0f, -2.0f));
}
int main(int argc, char* argv[])
{

	// glfw window setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "SPH Simulation", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// glad init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	Renderer ren;
	ren.init();

	renderer = &ren;
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	double run_time;


	size_t t = 0;
	float simulation_time = 0.0f;
	const unsigned fps = 30;
	const float d_t = 1.0f / fps;
	float frame_time = 0.0;
	int test = 0;
	while (!glfwWindowShouldClose(window))
	{
		// processInput
		auto start = std::chrono::system_clock::now();
		if (frame_time >= d_t)
		{
			ren.render();
			frame_time = 0.0f;
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double, std::deci> timeDiffMs = end - start;
		frame_time += timeDiffMs.count();
	}
	glfwTerminate();
	return 0;
}

