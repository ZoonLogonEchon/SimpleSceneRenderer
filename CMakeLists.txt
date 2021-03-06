cmake_minimum_required(VERSION 3.11)

project(SimpleRenderer LANGUAGES CXX C)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include(cmake/StringifyShaderSources.cmake)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

list(APPEND HPP_FILES
        Renderer/Components/Lights/point_light.hpp
        Renderer/Components/Lights/directional_light.hpp
        Renderer/Components/Meshes/mesh.hpp
        Renderer/Components/Meshes/cube.hpp
        Renderer/Components/Meshes/rect.hpp
        Renderer/Components/Meshes/sphere.hpp
        Renderer/Components/Meshes/triangle.hpp
        Renderer/Components/Meshes/mesh_source.hpp
        Renderer/Components/Camera/camera.hpp
        Renderer/Components/Transform/transform.hpp
        Renderer/OpenGLUtils/opengl_program.hpp
        Renderer/phong_shader.hpp
        Renderer/debug_shader.hpp
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
        GUI/mainwindow.hpp
        GUI/rendererwidget.hpp
)
list(APPEND CPP_FILES 
        
        Renderer/Components/Meshes/cube.cpp
		Renderer/Components/Meshes/rect.cpp
        Renderer/Components/Meshes/sphere.cpp
        Renderer/Components/Meshes/triangle.cpp
        Renderer/Components/Camera/camera.cpp
        Renderer/OpenGLUtils/opengl_program.cpp
        Renderer/phong_shader.cpp
        Renderer/debug_shader.cpp
        Renderer/OpenGLUtils/mesh_buffer.cpp
        Renderer/renderer.cpp
        #Renderer/shader.cpp
        Renderer/scene.cpp
        Renderer/scene_object.cpp
        GUI/mainwindow.cpp
        GUI/rendererwidget.cpp
        main.cpp
)
list(APPEND UI_FILES 
        GUI/mainwindow.ui
)
list(APPEND H_FILES 
		glad/glad.h
		KHR/khrplatform.h
)
list(APPEND C_FILES 
		glad.c
)
list(APPEND GLSL_FILES
    Renderer/Shaders/glsl/vs_simple_shader.glsl
    Renderer/Shaders/glsl/fs_simple_shader.glsl
    Renderer/Shaders/glsl/vs_non_shading_shader.glsl
    Renderer/Shaders/glsl/fs_non_shading_shader.glsl
)
set(EXECUTABLE SimpleRenderer)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE}
	PUBLIC 
    ${CPP_FILES}
    ${HPP_FILES} 
    ${UI_FILES}
	${C_FILES}
    ${H_FILES}
    ${GLSL_FILES}
)
set(VS_SIMPLE_SHADER_STRING "")
set(FS_SIMPLE_SHADER_STRING "")
set(VS_NON_SHADING_SHADER_STRING "")
set(FS_NON_SHADING_SHADER_STRING "")
read_into_string("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/glsl/vs_simple_shader.glsl" VS_SIMPLE_SHADER_STRING)
read_into_string("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/glsl/fs_simple_shader.glsl" FS_SIMPLE_SHADER_STRING)
read_into_string("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/glsl/vs_non_shading_shader.glsl" VS_NON_SHADING_SHADER_STRING)
read_into_string("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/glsl/fs_non_shading_shader.glsl" FS_NON_SHADING_SHADER_STRING)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/shader_sources.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders/shader_sources.hpp" @ONLY)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${CPP_FILES} ${HPP_FILES} ${UI_FILES} ${GLSL_FILES})
target_compile_features(${EXECUTABLE} PRIVATE cxx_std_17)
target_link_libraries(${EXECUTABLE} PUBLIC glfw opengl32 glm::glm Qt5::Widgets)