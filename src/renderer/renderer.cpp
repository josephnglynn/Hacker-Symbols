//
// Created by joseph on 12/04/2021.
//

#include "renderer.h"
#include <text_Renderer.h>

std::vector<Row> Renderer::bufferOutput;
bool Renderer::binary;

void Renderer::reSize(float WINDOW_WIDTH, float WINDOW_HEIGHT) {
    auto length = (unsigned int)(WINDOW_WIDTH / (float)TextRenderer::characterWidth);
    for (unsigned int i = 0; i < bufferOutput.size(); i++) {
        if (bufferOutput[i].WIDTH > length) {
            bufferOutput[i].data.erase(length);
        } else {
            bufferOutput[i].data += Renderer::generateNewSymbols(length - bufferOutput[i].WIDTH);
        }
        bufferOutput[i].WIDTH = length;
    }
    std::cout << bufferOutput[0].data << ":" << length << ":" << WINDOW_WIDTH << std::endl;
}

void Renderer::draw(float WINDOW_WIDTH, float WINDOW_HEIGHT) {
    for (int i = 0; i < bufferOutput.size(); i++) {
        TextRenderer::RenderRow((*TextRenderer::textShader), bufferOutput[i].data , 0, i * TextRenderer::characterWidth, 1.0f, glm::vec3(1, 1, 1));
    }
}

void Renderer::setUp(float WINDOW_WIDTH, float WINDOW_HEIGHT, bool BINARY) {
    binary = BINARY;
    TextRenderer::setUpTextRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
    srand(time(NULL));
    auto length = (unsigned int)(WINDOW_WIDTH / (float)TextRenderer::characterWidth);
    for (unsigned int i = 0; i <= (int)WINDOW_HEIGHT; i+=TextRenderer::characterWidth * 2) {
        bufferOutput.emplace_back(length, Renderer::generateNewSymbols(length));
    }
}

std::string Renderer::generateNewSymbols(unsigned int numberOfCharacters) {
    std::string extraCharacters;
    if (binary) {
        return extraCharacters;
    }

    for (int i = 0; i < numberOfCharacters; i++) {
        if (rand() % 2) {
            extraCharacters += static_cast<char>(rand() % 94 + 32);
        } else {
            extraCharacters += "@";
        }
    }

    return extraCharacters;
}

Row::Row(unsigned int _width, std::string _data) {
    WIDTH = _width;
    data = _data;
}