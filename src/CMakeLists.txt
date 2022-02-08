set(LIBNAME RendererLib)
set(RENDERER_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
list(APPEND HPP_FILES
        ${RENDERER_INCLUDE_DIR}/SceneRenderer/renderer.hpp
        ${RENDERER_INCLUDE_DIR}/SceneRenderer/Shaders/shaderSources.hpp
		${RENDERER_INCLUDE_DIR}/SceneRenderer/Shapes/rect.hpp
        ${RENDERER_INCLUDE_DIR}/SceneRenderer/Shapes/sphere.hpp
        ${RENDERER_INCLUDE_DIR}/SceneRenderer/Shapes/triangle.hpp
		${RENDERER_INCLUDE_DIR}/SceneRenderer/Utility/OGLProgram.hpp
		
)
list(APPEND CPP_FILES 
		renderer.cpp
		Shapes/rect.cpp
        Shapes/sphere.cpp
        Shapes/triangle.cpp
		Utility/OGLProgram.cpp
)
add_library(${LIBNAME})
target_sources(${LIBNAME}
	PUBLIC 
    ${CPP_FILES}
    ${HPP_FILES} 
)

target_include_directories(${LIBNAME} PRIVATE ${RENDERER_INCLUDE_DIR})

target_link_libraries(${LIBNAME} PUBLIC glad::glad glfw opengl32 glm::glm)

source_group(TREE "${PROJECT_SOURCE_DIR}/src" FILES 
			${CPP_FILES} 
)

source_group(TREE ${RENDERER_INCLUDE_DIR} FILES 
			${HPP_FILES} 
)



