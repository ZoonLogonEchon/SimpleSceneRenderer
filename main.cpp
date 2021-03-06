#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <chrono>


#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <QApplication>
#include "GUI/rendererwidget.hpp"
#include "GUI/mainwindow.hpp"
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
	auto camera = scene->getMainCamera();
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		camera->getComponent<Transform>()->translate(-1.0f * glm::vec3(0.0, 0.0f, 1.0f));
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		camera->getComponent<Transform>()->translate(1.0f * glm::vec3(0.0, 0.0f, 1.0f));
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		camera->getComponent<Transform>()->translate(1.0f * glm::vec3(1.0, 0.0f, 0.0f));
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		camera->getComponent<Transform>()->translate(-1.0f * glm::vec3(1.0, 0.0f, 0.0f));
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		camera->getComponent<Transform>()->translate(1.0f * glm::vec3(0.0, 1.0f, 0.0f));
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		camera->getComponent<Transform>()->translate(-1.0f * glm::vec3(0.0, 1.0f, 0.0f));
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		camera->getComponent<Transform>()->rotate(0.1f * glm::vec3(0.0f, 1.0f, 0.0f));
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		camera->getComponent<Transform>()->rotate(-0.1f * glm::vec3(0.0f, 1.0f, 0.0f));
	// create new cube
	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		auto cube = scene->addCube("new dynamic cube");
		auto cam_comp = camera->getComponent<Camera>();
		auto trsf = camera->getComponent<Transform>();
		auto look_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->lookDirection, 1.0f));
		//auto up_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->up, 1.0f));
		
		cube->getComponent<Transform>()->translate(50.0f * glm::vec3(look_dir) + trsf->position);
		cube->getComponent<Transform>()->scale(10.0f);

		renderer->initSceneObject(cube);
	}
	
	renderer->updateCameraStuff(*scene);
}

void fill_default_scene(std::shared_ptr<Scene> scene)
{
	std::string rc_name = "test_rect";
	std::string cu_name = "test_cube";
	std::string pl_name = "test_point_light";
	std::string pl2_name = "test_point_light2";
	auto cube = scene->addCube(cu_name);
	cube->getComponent<Transform>()->scale(30.0f);
	cube->getComponent<Transform>()->translate(glm::vec3(0.0f, 0.0f, 2.0f));
	scene->getMainCamera()->getComponent<Transform>()->translate(glm::vec3(0.0f, 0.0f, 101.0f));
}

int main(int argc, char* argv[])
{
	const int opengl_version_major = 4;
	const int opengl_version_minor = 5;

	QApplication app(argc, argv);
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(opengl_version_major, opengl_version_minor);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);
	//std::shared_ptr<Scene> sc = std::make_shared<Scene>("my scene");
	//fill_default_scene(sc);
	MainWindow main_window;
	main_window.show();
	return app.exec();
	/*
	// glfw window setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_version_minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	const int width = 800;
	const int height = 600;
	GLFWwindow* window = glfwCreateWindow(width, height, "SimpleRenderer", NULL, NULL);
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
	std::string rc_name = "test_rect";
	std::string cu_name = "test_cube";
	std::string pl_name = "test_point_light";
	std::string pl2_name = "test_point_light2";
	Scene sc("my scene");
	auto cube = sc.addCube(cu_name);
	//auto pl1 = sc.addPointLight(pl_name);
	//auto pl2 = sc.addPointLight(pl2_name);
	cube->getComponent<Transform>()->scale(30.0f);
	cube->getComponent<Transform>()->translate(glm::vec3(0.0f, 0.0f, 2.0f));
	//pl1->getComponent<Transform>()->scale(10.0f);
	//pl2->getComponent<Transform>()->scale(10.0f);
	//pl1->getComponent<Transform>()->translate(glm::vec3(-20.0f, 0.0f, 20.0f));
	//pl2->getComponent<Transform>()->translate(glm::vec3(0.0f, 20.0f, 20.0f));
	sc.getMainCamera()->getComponent<Transform>()->translate(glm::vec3(0.0f, 0.0f, 101.0f));
	// TODO if camera has a mesh it should not be rendered
	sc.getMainCamera()->addComponent<Mesh>();
	*(sc.getMainCamera()->getComponent<Mesh>()) = Mesh(std::make_shared<Cube>());
	//sc.rotateShape(cu_name, glm::vec3(glm::radians(45.0f), 0.0f, 0.0f));
	Renderer ren;
	ren.init(sc, width, height);

	renderer = &ren;
	scene = &sc;
	glViewport(0, 0, width, height);
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
			ren.render(sc, width, height);
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
	*/
}

