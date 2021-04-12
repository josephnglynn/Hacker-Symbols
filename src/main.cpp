//
// Created by joseph on 11/04/2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <renderer.h>
#include <chrono>
#include <unistd.h>
#include <cstring>

float WINDOW_WIDTH = 1920;
float WINDOW_HEIGHT = 1080;

double frameRate = 1000 / 60;
bool binary = false;
float changeInYAxis = 0.01;

int main(int argc, char *argv[]) {

    for (int i = 0; i < argc; i++) {
        if (argv[i] == NULL) {
            break;
        }

        if (strcmp(argv[i], "-binary") == 0 || strcmp(argv[i], "-b") == 0) {
            binary = true;
        }

        if (strcmp(argv[i], "-change") == 0 || strcmp(argv[i], "-c") == 0) {
            i++;
            changeInYAxis = std::stof(argv[i]);
        }
    }

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow((int) WINDOW_WIDTH, (int) WINDOW_HEIGHT, "Hacker Symbols", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, [](GLFWwindow *callbackWindow, int width, int height) {
        WINDOW_HEIGHT = (float) height;
        WINDOW_WIDTH = (float) width;
        Renderer::reSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    });

    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR GLEW DIDN'T INIT" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    Renderer::setUp(WINDOW_WIDTH, WINDOW_HEIGHT, binary, changeInYAxis);

    double before;
    double deltaT;

    while (!glfwWindowShouldClose(window)) {
        before = glfwGetTime() * 1000;
        glClear(GL_COLOR_BUFFER_BIT);


        Renderer::draw(WINDOW_WIDTH, WINDOW_HEIGHT, deltaT);

        glfwSwapBuffers(window);
        glfwPollEvents();

        deltaT = glfwGetTime() * 1000 - before;
        if (frameRate - deltaT > 0) {
            usleep(frameRate - deltaT);
        }
    }

    glfwTerminate();
    return 0;
}