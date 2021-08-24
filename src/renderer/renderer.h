//
// Created by joseph on 12/04/2021.
//

#pragma  once

#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class Row {
public:
    unsigned int width;
    std::string data;
    float y;
    explicit Row(unsigned int, float, std::string );
};


class Renderer {
public:
    //void Draw(float WINDOW_WIDTH, float WINDOW_HEIGHT, bool Binary, float changeInYAxis, unsigned int custom split, unsigned int FONT_HEIGHT, char * FONT_PATH):
    static void setUp(float, float, bool, float, glm::vec3, float, unsigned int, char *);

    //void Draw(float WINDOW_WIDTH, float WINDOW_HEIGHT, double deltaT):
    static void draw(float, float, double);

    //void reSize(float WINDOW_WIDTH, float WINDOW_HEIGHT):
    static void reSize(float, float);


private:
    static std::string generateNewSymbols(unsigned int);
    static bool binary;
    static std::vector<Row> bufferOutput;
    static float changeInYAxis;
    static glm::vec3 color;
    static float customSplit;
};

