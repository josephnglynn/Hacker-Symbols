//
// Created by joseph on 12/04/2021.
//

#ifndef HACKER_SYMBOLS_RENDERER_H
#define HACKER_SYMBOLS_RENDERER_H

#include <vector>
#include <string>
#include <iostream>

class Row {
public:
    explicit Row(unsigned int, std::string);

    unsigned int WIDTH;
    std::string data;
};


class Renderer {
public:
    //void Draw(float WINDOW_WIDTH, float WINDOW_HEIGHT, bool Binary):
    static void setUp(float, float, bool);

    //void Draw(float WINDOW_WIDTH, float WINDOW_HEIGHT):
    static void draw(float, float);

    //void reSize(float WINDOW_WIDTH, float WINDOW_HEIGHT):
    static void reSize(float, float);

    static std::vector<Row> bufferOutput;
private:
    static std::string generateNewSymbols(unsigned int);
    static bool binary;
};


#endif //HACKER_SYMBOLS_RENDERER_H
