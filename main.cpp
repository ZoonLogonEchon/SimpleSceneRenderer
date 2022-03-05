#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <chrono>


#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Renderer/renderer.hpp"
#include "Renderer/scene.hpp"
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Renderer* renderer;
Scene* scene;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		scene->getMainCamera().moveViewDir(1.0f);
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		scene->getMainCamera().moveViewDir(-1.0f);
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		scene->getMainCamera().moveHorizontal(1.0f);
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		scene->getMainCamera().moveHorizontal(-1.0f);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		scene->getMainCamera().moveVertical(1.0f);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		scene->getMainCamera().moveVertical(-1.0f);
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		scene->getMainCamera().lookAroundHorizontal(1.0f);
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		scene->getMainCamera().lookAroundHorizontal(-1.0f);
}
int main(int argc, char* argv[])
{

	// glfw window setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

	// build Scene 
	std::string tr_name = "test_triangle";
	std::string rc_name = "test_rect";
	std::string cu_name = "test_cube";
	Scene sc("my scene");
	//sc.addTriangle(tr_name);
	//sc.addRect(rc_name);
	sc.addCube(cu_name);
	//sc.scaleTriangle(tr_name, glm::vec3(30.0f, 30.0f, 1.0f));
	//sc.rotateTriangle(tr_name, glm::vec3(0.0f, 0.0f, glm::radians(45.0f)));
	//sc.translateTriangle(tr_name, glm::vec3(0.0f, -10.0f, 0.0f));
	sc.scaleShape(cu_name, glm::vec3(30.0f, 30.0f, 30.0f));
	//sc.rotateShape(cu_name, glm::vec3(glm::radians(45.0f), 0.0f, 0.0f));
	//sc.rotateRect(rc_name, glm::vec3(0.0f, 0.0f, glm::radians(45.0f)));
	//sc.translateRect(rc_name, glm::vec3(0.0f, -10.0f, 0.0f));
	Renderer ren;
	ren.init(sc);

	renderer = &ren;
	scene = &sc;
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	const unsigned fps = 30;
	const float d_t = 1.0f / fps;
	float frame_time = 0.0;
	while (!glfwWindowShouldClose(window))
	{
		auto start = std::chrono::system_clock::now();
		if (frame_time >= d_t)
		{
			ren.render(sc);
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

