cmake_minimum_required(VERSION 3.17)
project(Hacker_Symbols)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

add_library(SHADER_UTILS shaders/shaderUtils.cpp)
include_directories(shaders)

configure_file(shaders/shader.frag ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(shaders/shader.vert ${CMAKE_BINARY_DIR} COPYONLY)

find_package(freetype CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        OpenGL::GL
        freetype
        GLEW::GLEW
        glm::glm
        glfw
        PUBLIC
        SHADER_UTILS
        )


