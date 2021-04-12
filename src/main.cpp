//
// Created by joseph on 11/04/2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <text_Renderer.h>

float WINDOW_WIDTH = 1920;
float WINDOW_HEIGHT = 1080;

int main() {

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow((int) WINDOW_WIDTH, (int) WINDOW_HEIGHT, "Hacker Symbols", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, [](GLFWwindow* callbackWindow, int width, int height){
        WINDOW_HEIGHT = (float)height;
        WINDOW_WIDTH = (float)width;
    });

    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR GLEW DIDN'T INIT" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    TextRenderer::setUpTextRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        TextRenderer::RenderRow((*TextRenderer::textShader), "This is a test", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1.0f, glm::vec3(1, 1, 1));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}