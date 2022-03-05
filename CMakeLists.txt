cmake_minimum_required(VERSION 3.11)

project(SimpleRenderer LANGUAGES CXX C)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

list(APPEND HPP_FILES
        Renderer/Lights/point_light.hpp
        Renderer/OpenGLUtils/opengl_program.hpp
        Renderer/Shaders/shader_sources.hpp
        Renderer/Shapes/shape.hpp
        Renderer/Shapes/cube.hpp
		Renderer/Shapes/rect.hpp
        Renderer/Shapes/sphere.hpp
        Renderer/Shapes/triangle.hpp
        Renderer/renderer.hpp
		Renderer/camera.hpp
        Renderer/scene.hpp
)
list(APPEND CPP_FILES 
        Renderer/Lights/point_light.cpp
        Renderer/OpenGLUtils/opengl_program.cpp
        Renderer/Shapes/cube.cpp
		Renderer/Shapes/rect.cpp
        Renderer/Shapes/sphere.cpp
        Renderer/Shapes/triangle.cpp
        Renderer/camera.cpp
        Renderer/renderer.cpp
        Renderer/scene.cpp
        main.cpp
)
list(APPEND H_FILES 
		glad/glad.h
		KHR/khrplatform.h
)
list(APPEND C_FILES 
		glad.c
)
set(EXECUTABLE SimpleRenderer)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE}
	PUBLIC 
    ${CPP_FILES}
    ${HPP_FILES} 
	${C_FILES}
	${H_FILES}
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${CPP_FILES} ${HPP_FILES} )
target_compile_features(${EXECUTABLE} PRIVATE cxx_std_17)
target_link_libraries(${EXECUTABLE} PUBLIC glfw opengl32 glm::glm)