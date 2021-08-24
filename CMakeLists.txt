cmake_minimum_required(VERSION 3.17)
project(hackerSymbols)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp)


configure_file(src/shaders/shader.frag ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/shaders/shader.vert ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/textRenderer/Roboto-Regular.ttf ${CMAKE_BINARY_DIR} COPYONLY)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(freetype CONFIG REQUIRED)


add_library(SHADER_UTILS STATIC src/shaders/shaderUtils.cpp src/shaders/shaderUtils.h)
target_include_directories(SHADER_UTILS PUBLIC src/shaders)

add_library(TEXT_RENDERER STATIC src/textRenderer/text_Renderer.cpp src/textRenderer/text_Renderer.h)
target_include_directories(TEXT_RENDERER PUBLIC src/textRenderer)
target_link_libraries(TEXT_RENDERER PRIVATE SHADER_UTILS freetype)

add_library(RENDERER STATIC src/renderer/renderer.cpp src/renderer/renderer.h)
target_include_directories(RENDERER PUBLIC src/renderer)
target_link_libraries(RENDERER PRIVATE TEXT_RENDERER)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        OpenGL::GL
        GLEW::GLEW
        glm::glm
        glfw
        RENDERER
)

if(UNIX AND NOT APPLE AND TARGET hackerSymbols)

install(
        FILES
        "src/shaders/shader.frag"
        "src/shaders/shader.vert"
        "src/textRenderer/Roboto-Regular.ttf"
        DESTINATION
        "/usr/share/hackerSymbols"
)

install(
        TARGETS  hackerSymbols
        RUNTIME DESTINATION  "/usr/bin"
)

endif()