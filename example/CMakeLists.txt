set(EXECUTABLE RendererExample)
add_executable(${EXECUTABLE} main.cpp)
target_compile_features(${EXECUTABLE} PRIVATE cxx_std_17)
target_include_directories(${EXECUTABLE} PRIVATE ../include)

target_link_libraries(${EXECUTABLE} PRIVATE RendererLib opengl32 glm::glm)





