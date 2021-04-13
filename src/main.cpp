//
// Created by joseph on 11/04/2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <renderer.h>
#include <unistd.h>
#include <cstring>
#include <glm/glm.hpp>

//DEFAULT VALUES
float WINDOW_WIDTH = 1920;
float WINDOW_HEIGHT = 1080;

double frameRate = 1000 / 60;
bool binary = false;
float changeInYAxis = 0.1;
glm::vec3 color = glm::vec3(0, 1, 0); //GREEN
glm::vec3 bgColor = glm::vec3 (0, 0, 0);
float customSplit = 1;
unsigned int FONT_HEIGHT;


void usage() {
    printf("    -color : sets textColor based on three floats for rgb color following the flag. 0 <= values <= 1\n"
           "    -colorRGB : sets textColor based on three floats as rgb colors : 0 <= values <= 255\n"
           "    -bg : sets background color based on three floats for rgb color following the flag. 0 <= values <= 1\n"
           "    -bgRGB : sets background color based on three floats for rgb color following the flag. 0 <= values <= 255\n"
           "    -binary / -b : DISPLAYS ONLY BINARY CHARACTERS (0, 1)\n"
           "    -fontSize / -fs : Sets the height of the font\n"
            "    -change / -c : ALLOW YOU TO DEFINE THE SPEED OF CHARACTERS\n"
            "    -custom-split / -cs : ALLOWS YOU TO DEFINE SPREAD OF CHARACTERS - HIGHER = SPARSER\n"
            "    -help / help : DISPLAYS HELP\n"
    );
}



//MAIN DEFINITION
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

        if (strcmp(argv[i], "-color") == 0) {
            color = glm::vec3(std::stof(argv[i + 1]), std::stof(argv[i + 2]), std::stof(argv[i + 3]));
            i += 3;
        }

        if (strcmp(argv[i], "-colorRGB") == 0) {
            color = glm::vec3(std::stof(argv[i + 1]) / 255, std::stof(argv[i + 2]) / 255, std::stof(argv[i + 3]) / 255);
            i += 3;
        }

        if (strcmp(argv[i], "-bg") == 0) {
            bgColor = glm::vec3(std::stof(argv[i + 1]), std::stof(argv[i + 2]), std::stof(argv[i + 3]));
            i += 3;
        }

        if (strcmp(argv[i], "-bgRGB") == 0) {
            bgColor = glm::vec3(std::stof(argv[i + 1]) / 255, std::stof(argv[i + 2]) / 255, std::stof(argv[i + 3]) / 255);
            i += 3;
        }

        if (strcmp(argv[i], "-custom-split") == 0 || strcmp(argv[i], "-cs") == 0) {
            customSplit = std::stof(argv[i + 1]);
            i++;
        }

        if (strcmp(argv[i], "-fontSize") == 0 || strcmp(argv[i], "-fs") == 0) {
            FONT_HEIGHT = std::stoi(argv[i + 1]);
            i++;
        }


        if (strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "help") == 0 || strcmp(argv[i], "-h") == 0) {
            usage();
            return 0;
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

    Renderer::setUp(WINDOW_WIDTH, WINDOW_HEIGHT, binary, changeInYAxis, color, customSplit, FONT_HEIGHT);

    double before;
    double deltaT;

    while (!glfwWindowShouldClose(window)) {
        before = glfwGetTime() * 1000;

        glClearColor(bgColor.x, bgColor.y, bgColor.z, 1);
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