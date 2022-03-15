cmake_minimum_required(VERSION 3.11)

project(SimpleRenderer LANGUAGES CXX C)
include(cmake/StringifyShaderSources.cmake)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

list(APPEND HPP_FILES
        Renderer/Components/Lights/point_light.hpp
        Renderer/Components/Lights/directional_light.hpp
        Renderer/Components/Meshes/mesh.hpp
        Renderer/Components/Meshes/cube.hpp
        Renderer/Components/Meshes/rect.hpp
        Renderer/Components/Meshes/sphere.hpp
        Renderer/Components/Meshes/triangle.hpp
        Renderer/Components/Camera/camera.hpp
        Renderer/Components/Transform/transform.hpp
        Renderer/OpenGLUtils/opengl_program.hpp
        Renderer/OpenGLUtils/mesh_buffer.hpp
        Renderer/Shaders/shaders.hpp
        Renderer/Shaders/shader_sources.hpp
        
        Renderer/renderer.hpp
        
        #Renderer/shader.hpp
        Renderer/scene.hpp
        Renderer/scene_object.hpp
        Renderer/scene_object_components.hpp
        Renderer/component_array.hpp
        Renderer/config.hpp
        Renderer/typedef.hpp
        Renderer/entity_components_manager.hpp
)
list(APPEND CPP_FILES 
        
        Renderer/Components/Meshes/cube.cpp
		Renderer/Components/Meshes/rect.cpp
        Renderer/Components/Meshes/sphere.cpp
        Renderer/Components/Meshes/triangle.cpp
        Renderer/Components/Camera/camera.cpp
        Renderer/OpenGLUtils/opengl_program.cpp
        Renderer/OpenGLUtils/mesh_buffer.cpp
        Renderer/renderer.cpp
        #Renderer/shader.cpp
        Renderer/scene.cpp
        Renderer/scene_object.cpp
        main.cpp
)
list(APPEND H_FILES 
		glad/glad.h
		KHR/khrplatform.h
)
list(APPEND C_FILES 
		glad.c
)
list(APPEND GLSL_FILES
    Renderer/Shaders/vs_simple_shader.glsl
    Renderer/Shaders/fs_simple_shader.glsl
    Renderer/Shaders/vs_non_shading_shader.glsl
    Renderer/Shaders/fs_non_shading_shader.glsl
)
set(EXECUTABLE SimpleRenderer)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE}
	PUBLIC 
    ${CPP_FILES}
    ${HPP_FILES} 
	${C_FILES}
    ${H_FILES}
    ${GLSL_FILES}
)
set(VS_SIMPLE_SHADER_STRING "")
set(FS_SIMPLE_SHADER_STRING "")
set(VS_NON_SHADING_SHADER_STRING "")
set(FS_NON_SHADING_SHADER_STRING "")
read_into_string("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/vs_simple_shader.glsl" VS_SIMPLE_SHADER_STRING)
read_into_string("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/fs_simple_shader.glsl" FS_SIMPLE_SHADER_STRING)
read_into_string("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/vs_non_shading_shader.glsl" VS_NON_SHADING_SHADER_STRING)
read_into_string("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/fs_non_shading_shader.glsl" FS_NON_SHADING_SHADER_STRING)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/shader_sources.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/shader_sources.hpp" @ONLY)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${CPP_FILES} ${HPP_FILES} ${GLSL_FILES})
target_compile_features(${EXECUTABLE} PRIVATE cxx_std_17)
target_link_libraries(${EXECUTABLE} PUBLIC glfw opengl32 glm::glm)