cmake_minimum_required(VERSION 3.17)
project(Hacker_Symbols)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp)


configure_file(src/renderer/textRenderer/shaders/shader.frag ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/renderer/textRenderer/shaders/shader.vert ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/renderer/textRenderer/Roboto-Regular.ttf ${CMAKE_BINARY_DIR} COPYONLY)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(freetype CONFIG REQUIRED)



add_library(SHADER_UTILS STATIC src/renderer/textRenderer/shaders/shaderUtils.cpp src/renderer/textRenderer/shaders/shaderUtils.h)
target_include_directories(SHADER_UTILS PUBLIC src/renderer/textRenderer/shaders)

add_library(TEXT_RENDERER STATIC src/renderer/textRenderer/text_Renderer.cpp src/renderer/textRenderer/text_Renderer.h)
target_include_directories(TEXT_RENDERER PUBLIC src/renderer/textRenderer)
target_link_libraries(TEXT_RENDERER PRIVATE SHADER_UTILS freetype)

add_library(RENDERER STATIC src/renderer/renderer.cpp src/renderer/renderer.h)
target_include_directories(RENDERER PUBLIC src/renderer)
target_link_libraries(RENDERER PRIVATE TEXT_RENDERER)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        OpenGL::GL
        GLEW::GLEW
        glm::glm
        glfw
        RENDERER
        )