//
// Created by joseph on 12/04/2021.
//

#ifndef HACKER_SYMBOLS_RENDERER_H
#define HACKER_SYMBOLS_RENDERER_H

#include <vector>
#include <string>
#include <iostream>
#include <vector>


class Row {
public:
    unsigned int width;
    std::string data;
    float y;
    explicit Row(unsigned int, float, std::string);
};


class Renderer {
public:
    //void Draw(float WINDOW_WIDTH, float WINDOW_HEIGHT, bool Binary, float changeInYAxis):
    static void setUp(float, float, bool, float);

    //void Draw(float WINDOW_WIDTH, float WINDOW_HEIGHT, double deltaT):
    static void draw(float, float, double);

    //void reSize(float WINDOW_WIDTH, float WINDOW_HEIGHT):
    static void reSize(float, float);


private:
    static std::string generateNewSymbols(unsigned int);
    static bool binary;
    static std::vector<Row> bufferOutput;
    static float changeInYAxis;
};


#endif //HACKER_SYMBOLS_RENDERER_H
