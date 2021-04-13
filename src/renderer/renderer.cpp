//
// Created by joseph on 12/04/2021.
//

#include "renderer.h"
#include <text_Renderer.h>


bool Renderer::binary;
std::vector<Row> Renderer::bufferOutput;
float Renderer::changeInYAxis;
glm::vec3 Renderer::color;
float Renderer::customSplit;

void Renderer::draw(float WINDOW_WIDTH, float WINDOW_HEIGHT, double deltaT) {
    bool gotLowest = false;
    float lowest = 0;
    for (unsigned int i = 0; i < bufferOutput.size(); i++) {
        bufferOutput[i].y += Renderer::changeInYAxis * deltaT;
        if (bufferOutput[i].y > WINDOW_HEIGHT) {
            if (!gotLowest) {
                gotLowest = true;
                for (unsigned int i = 0; i < bufferOutput.size(); i++) {
                    if (bufferOutput[i].y < lowest) {
                        lowest = bufferOutput[i].y;
                    }
                }
            }
            bufferOutput[i].y = lowest -(float) TextRenderer::characterHeight;
            lowest = bufferOutput[i].y;
            bufferOutput[i].data = generateNewSymbols(WINDOW_WIDTH);
        }
        TextRenderer::RenderRow((*TextRenderer::textShader), bufferOutput[i].data, 0, bufferOutput[i].y, 1, color);
    }
}


void Renderer::setUp(float WINDOW_WIDTH, float WINDOW_HEIGHT, bool BINARY, float ChangeInYAxis, glm::vec3 COLOR,
                     float CUSTOM_SPLIT, unsigned int FONT_HEIGHT) {
    TextRenderer::setUpTextRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, FONT_HEIGHT);
    binary = BINARY;
    changeInYAxis = ChangeInYAxis;
    color = COLOR;
    customSplit = RAND_MAX / CUSTOM_SPLIT;
    srand(time(NULL));
}

std::string Renderer::generateNewSymbols(unsigned int widthNeededToFill) {
    unsigned int filledWidth = 0;
    std::string extraCharacters;

    if (binary) {
        while (filledWidth < widthNeededToFill) {
            if (rand() < customSplit) {
                if (rand() % 2) {
                    filledWidth += TextRenderer::Characters['0'].Size.x;
                    extraCharacters += '0';
                } else {
                    filledWidth += TextRenderer::Characters['1'].Size.x;
                    extraCharacters += '1';
                }
            } else {
                filledWidth += TextRenderer::Characters[' '].Size.x;
                extraCharacters += ' ';
            }
        }
        return extraCharacters;
    }


    while (filledWidth < widthNeededToFill) {
        if (rand() < customSplit) {
            char newCharacter = (char) (rand() % 94 + 32);
            filledWidth += TextRenderer::Characters[newCharacter].Size.x;
            extraCharacters += newCharacter;
        } else {
            filledWidth += TextRenderer::Characters[' '].Size.x;
            extraCharacters += ' ';
        }
    }

    return extraCharacters;
}

void Renderer::reSize(float WINDOW_WIDTH, float WINDOW_HEIGHT) {
    //TODO DON'T JUST REGENERATE THE BUFFER
    if (bufferOutput.size() != (WINDOW_HEIGHT / TextRenderer::characterHeight) + 1) {
        bufferOutput.clear();
        for (int i = bufferOutput.size() * TextRenderer::characterHeight;
             i < WINDOW_HEIGHT + TextRenderer::characterHeight; i += TextRenderer::characterHeight) {
            bufferOutput.push_back(Row(WINDOW_WIDTH, i, Renderer::generateNewSymbols(WINDOW_WIDTH)));
        }
    }

    for (int i = 0; i < bufferOutput.size(); ++i) {
        if (bufferOutput[i].width < WINDOW_WIDTH) {
            bufferOutput[i].data += generateNewSymbols(WINDOW_WIDTH - bufferOutput[i].width);
        }
    }
}

Row::Row(unsigned int _width, float yPos, std::string _data) {
    width = _width;
    data = std::move(_data);
    y = yPos;
}
