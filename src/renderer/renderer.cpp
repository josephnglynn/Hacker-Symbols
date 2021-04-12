//
// Created by joseph on 12/04/2021.
//

#include "renderer.h"
#include <text_Renderer.h>
#include <utility>

bool Renderer::binary;
std::vector<Row> Renderer::bufferOutput;
float Renderer::changeInYAxis;

void Renderer::draw(float WINDOW_WIDTH, float WINDOW_HEIGHT, double deltaT) {
    for (unsigned int i = 0; i < bufferOutput.size(); i++) {
        bufferOutput[i].y += Renderer::changeInYAxis * deltaT;
        if (bufferOutput[i].y > WINDOW_HEIGHT) {
            bufferOutput[i].y = 0 - (float)TextRenderer::characterHeight;
            bufferOutput[i].data = generateNewSymbols(WINDOW_WIDTH);
        }
        TextRenderer::RenderRow((*TextRenderer::textShader), bufferOutput[i].data, 0, bufferOutput[i].y, 1, glm::vec3(1, 1, 1));
    }
}



void Renderer::setUp(float WINDOW_WIDTH, float WINDOW_HEIGHT, bool BINARY, float ChangeInYAxis) {
    TextRenderer::setUpTextRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
    binary = BINARY;
    changeInYAxis = ChangeInYAxis;
}

std::string Renderer::generateNewSymbols(unsigned int widthNeededToFill) {
    std::string extraCharacters;
    if (binary) {
        return extraCharacters;
    }

    unsigned int filledWidth = 0;
    while (filledWidth < widthNeededToFill) {
        if (rand() % 2) {
           char newCharacter =  static_cast<char>(rand() % 94 + 32);
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
    if (bufferOutput.size() < (WINDOW_HEIGHT / TextRenderer::characterHeight) + 1) {
        float lastHeight;
        if (bufferOutput.size() > 0) {
           lastHeight = bufferOutput[bufferOutput.size() -1].y;
        }
        for (int i = bufferOutput.size() * TextRenderer::characterHeight; i < WINDOW_HEIGHT + TextRenderer::characterHeight; i+=TextRenderer::characterHeight) {
            bufferOutput.push_back(Row(WINDOW_WIDTH, i + lastHeight, Renderer::generateNewSymbols(WINDOW_WIDTH)));
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
