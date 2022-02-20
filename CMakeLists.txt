cmake_minimum_required(VERSION 3.11)

project(SimpleRenderer LANGUAGES CXX C)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

list(APPEND HPP_FILES
        Renderer/renderer.hpp
		Renderer/OGLProgram.hpp
        Renderer/Shaders/shaderSources.hpp
		Scene/camera.hpp
		Scene/scene.hpp
		Scene/Shapes/rect.hpp
        Scene/Shapes/sphere.hpp
        Scene/Shapes/triangle.hpp
)
list(APPEND CPP_FILES 
		main.cpp
		Renderer/renderer.cpp
		Renderer/OGLProgram.cpp
		Scene/camera.cpp
		Scene/scene.cpp
		Scene/Shapes/rect.cpp
        Scene/Shapes/sphere.cpp
        Scene/Shapes/triangle.cpp
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