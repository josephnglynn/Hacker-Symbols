cmake_minimum_required(VERSION 3.17)
project(LearnModernOpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(LearnModernOpenGL main.backup)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})


find_package(glfw3 3.3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

