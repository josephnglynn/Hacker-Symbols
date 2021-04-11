//
// Created by joseph on 11/04/2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main() {
    GLFWwindow *window;

    if (!glewInit()) {
        return -1;
    }

    window = glfwCreateWindow(500, 500, "Hacker Symbols", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    while (glfwWindowShouldClose(window)) {


        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
